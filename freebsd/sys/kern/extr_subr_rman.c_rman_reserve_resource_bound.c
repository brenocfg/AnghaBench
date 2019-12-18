#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
struct rman {int /*<<< orphan*/  rm_mtx; int /*<<< orphan*/  rm_list; int /*<<< orphan*/  rm_descr; } ;
struct resource {int dummy; } ;
struct resource_i {int r_end; int r_start; int r_flags; struct resource r_r; int /*<<< orphan*/ * r_sharehead; struct rman* r_rm; int /*<<< orphan*/ * r_dev; } ;
typedef  int rman_res_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct resource_i*,int /*<<< orphan*/ ) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_RMAN ; 
 int M_ZERO ; 
 unsigned long long RF_ALIGNMENT (int) ; 
 int RF_ALLOCATED ; 
 int RF_FIRSTSHARE ; 
 int RF_SHAREABLE ; 
 int RM_MAX_END ; 
 scalar_t__ SHARE_TYPE (int) ; 
 struct resource_i* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (int /*<<< orphan*/ *,struct resource_i*,struct resource_i*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct resource_i*,struct resource_i*,int /*<<< orphan*/ ) ; 
 struct resource_i* TAILQ_NEXT (struct resource_i*,int /*<<< orphan*/ ) ; 
 char* device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct resource_i*,int /*<<< orphan*/ ) ; 
 struct resource_i* int_alloc_resource (int) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_link ; 
 int /*<<< orphan*/  r_sharelink ; 
 int ummax (int,int) ; 
 int ummin (int,int) ; 

struct resource *
rman_reserve_resource_bound(struct rman *rm, rman_res_t start, rman_res_t end,
			    rman_res_t count, rman_res_t bound, u_int flags,
			    device_t dev)
{
	u_int new_rflags;
	struct resource_i *r, *s, *rv;
	rman_res_t rstart, rend, amask, bmask;

	rv = NULL;

	DPRINTF(("rman_reserve_resource_bound: <%s> request: [%#jx, %#jx], "
	       "length %#jx, flags %x, device %s\n", rm->rm_descr, start, end,
	       count, flags,
	       dev == NULL ? "<null>" : device_get_nameunit(dev)));
	KASSERT((flags & RF_FIRSTSHARE) == 0,
	    ("invalid flags %#x", flags));
	new_rflags = (flags & ~RF_FIRSTSHARE) | RF_ALLOCATED;

	mtx_lock(rm->rm_mtx);

	r = TAILQ_FIRST(&rm->rm_list);
	if (r == NULL) {
	    DPRINTF(("NULL list head\n"));
	} else {
	    DPRINTF(("rman_reserve_resource_bound: trying %#jx <%#jx,%#jx>\n",
		    r->r_end, start, count-1));
	}
	for (r = TAILQ_FIRST(&rm->rm_list);
	     r && r->r_end < start + count - 1;
	     r = TAILQ_NEXT(r, r_link)) {
		;
		DPRINTF(("rman_reserve_resource_bound: tried %#jx <%#jx,%#jx>\n",
			r->r_end, start, count-1));
	}

	if (r == NULL) {
		DPRINTF(("could not find a region\n"));
		goto out;
	}

	amask = (1ull << RF_ALIGNMENT(flags)) - 1;
	KASSERT(start <= RM_MAX_END - amask,
	    ("start (%#jx) + amask (%#jx) would wrap around", start, amask));

	/* If bound is 0, bmask will also be 0 */
	bmask = ~(bound - 1);
	/*
	 * First try to find an acceptable totally-unshared region.
	 */
	for (s = r; s; s = TAILQ_NEXT(s, r_link)) {
		DPRINTF(("considering [%#jx, %#jx]\n", s->r_start, s->r_end));
		/*
		 * The resource list is sorted, so there is no point in
		 * searching further once r_start is too large.
		 */
		if (s->r_start > end - (count - 1)) {
			DPRINTF(("s->r_start (%#jx) + count - 1> end (%#jx)\n",
			    s->r_start, end));
			break;
		}
		if (s->r_start > RM_MAX_END - amask) {
			DPRINTF(("s->r_start (%#jx) + amask (%#jx) too large\n",
			    s->r_start, amask));
			break;
		}
		if (s->r_flags & RF_ALLOCATED) {
			DPRINTF(("region is allocated\n"));
			continue;
		}
		rstart = ummax(s->r_start, start);
		/*
		 * Try to find a region by adjusting to boundary and alignment
		 * until both conditions are satisfied. This is not an optimal
		 * algorithm, but in most cases it isn't really bad, either.
		 */
		do {
			rstart = (rstart + amask) & ~amask;
			if (((rstart ^ (rstart + count - 1)) & bmask) != 0)
				rstart += bound - (rstart & ~bmask);
		} while ((rstart & amask) != 0 && rstart < end &&
		    rstart < s->r_end);
		rend = ummin(s->r_end, ummax(rstart + count - 1, end));
		if (rstart > rend) {
			DPRINTF(("adjusted start exceeds end\n"));
			continue;
		}
		DPRINTF(("truncated region: [%#jx, %#jx]; size %#jx (requested %#jx)\n",
		       rstart, rend, (rend - rstart + 1), count));

		if ((rend - rstart + 1) >= count) {
			DPRINTF(("candidate region: [%#jx, %#jx], size %#jx\n",
			       rstart, rend, (rend - rstart + 1)));
			if ((s->r_end - s->r_start + 1) == count) {
				DPRINTF(("candidate region is entire chunk\n"));
				rv = s;
				rv->r_flags = new_rflags;
				rv->r_dev = dev;
				goto out;
			}

			/*
			 * If s->r_start < rstart and
			 *    s->r_end > rstart + count - 1, then
			 * we need to split the region into three pieces
			 * (the middle one will get returned to the user).
			 * Otherwise, we are allocating at either the
			 * beginning or the end of s, so we only need to
			 * split it in two.  The first case requires
			 * two new allocations; the second requires but one.
			 */
			rv = int_alloc_resource(M_NOWAIT);
			if (rv == NULL)
				goto out;
			rv->r_start = rstart;
			rv->r_end = rstart + count - 1;
			rv->r_flags = new_rflags;
			rv->r_dev = dev;
			rv->r_rm = rm;

			if (s->r_start < rv->r_start && s->r_end > rv->r_end) {
				DPRINTF(("splitting region in three parts: "
				       "[%#jx, %#jx]; [%#jx, %#jx]; [%#jx, %#jx]\n",
				       s->r_start, rv->r_start - 1,
				       rv->r_start, rv->r_end,
				       rv->r_end + 1, s->r_end));
				/*
				 * We are allocating in the middle.
				 */
				r = int_alloc_resource(M_NOWAIT);
				if (r == NULL) {
					free(rv, M_RMAN);
					rv = NULL;
					goto out;
				}
				r->r_start = rv->r_end + 1;
				r->r_end = s->r_end;
				r->r_flags = s->r_flags;
				r->r_rm = rm;
				s->r_end = rv->r_start - 1;
				TAILQ_INSERT_AFTER(&rm->rm_list, s, rv,
						     r_link);
				TAILQ_INSERT_AFTER(&rm->rm_list, rv, r,
						     r_link);
			} else if (s->r_start == rv->r_start) {
				DPRINTF(("allocating from the beginning\n"));
				/*
				 * We are allocating at the beginning.
				 */
				s->r_start = rv->r_end + 1;
				TAILQ_INSERT_BEFORE(s, rv, r_link);
			} else {
				DPRINTF(("allocating at the end\n"));
				/*
				 * We are allocating at the end.
				 */
				s->r_end = rv->r_start - 1;
				TAILQ_INSERT_AFTER(&rm->rm_list, s, rv,
						     r_link);
			}
			goto out;
		}
	}

	/*
	 * Now find an acceptable shared region, if the client's requirements
	 * allow sharing.  By our implementation restriction, a candidate
	 * region must match exactly by both size and sharing type in order
	 * to be considered compatible with the client's request.  (The
	 * former restriction could probably be lifted without too much
	 * additional work, but this does not seem warranted.)
	 */
	DPRINTF(("no unshared regions found\n"));
	if ((flags & RF_SHAREABLE) == 0)
		goto out;

	for (s = r; s && s->r_end <= end; s = TAILQ_NEXT(s, r_link)) {
		if (SHARE_TYPE(s->r_flags) == SHARE_TYPE(flags) &&
		    s->r_start >= start &&
		    (s->r_end - s->r_start + 1) == count &&
		    (s->r_start & amask) == 0 &&
		    ((s->r_start ^ s->r_end) & bmask) == 0) {
			rv = int_alloc_resource(M_NOWAIT);
			if (rv == NULL)
				goto out;
			rv->r_start = s->r_start;
			rv->r_end = s->r_end;
			rv->r_flags = new_rflags;
			rv->r_dev = dev;
			rv->r_rm = rm;
			if (s->r_sharehead == NULL) {
				s->r_sharehead = malloc(sizeof *s->r_sharehead,
						M_RMAN, M_NOWAIT | M_ZERO);
				if (s->r_sharehead == NULL) {
					free(rv, M_RMAN);
					rv = NULL;
					goto out;
				}
				LIST_INIT(s->r_sharehead);
				LIST_INSERT_HEAD(s->r_sharehead, s,
						 r_sharelink);
				s->r_flags |= RF_FIRSTSHARE;
			}
			rv->r_sharehead = s->r_sharehead;
			LIST_INSERT_HEAD(s->r_sharehead, rv, r_sharelink);
			goto out;
		}
	}
	/*
	 * We couldn't find anything.
	 */

out:
	mtx_unlock(rm->rm_mtx);
	return (rv == NULL ? NULL : &rv->r_r);
}