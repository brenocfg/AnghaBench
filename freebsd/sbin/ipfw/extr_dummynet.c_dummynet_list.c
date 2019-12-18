#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u_int ;
struct dn_sch {int dummy; } ;
struct dn_id {int id; int len; int /*<<< orphan*/  subtype; } ;
struct dn_fs {int dummy; } ;
struct dn_flow {int dummy; } ;
struct TYPE_2__ {int do_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  DN_API_VERSION ; 
 int /*<<< orphan*/  DN_CMD_GET ; 
 int /*<<< orphan*/  DN_FS ; 
 int /*<<< orphan*/  DN_LINK ; 
 int /*<<< orphan*/  DN_SCH ; 
 int /*<<< orphan*/  IP_DUMMYNET3 ; 
 int /*<<< orphan*/  O_NEXT (struct dn_id*,int) ; 
 int /*<<< orphan*/  bcopy (struct dn_id*,struct dn_id*,int) ; 
 TYPE_1__ co ; 
 int do_cmd (int /*<<< orphan*/ ,struct dn_id*,uintptr_t) ; 
 int /*<<< orphan*/  free (struct dn_id*) ; 
 int /*<<< orphan*/  list_pipes (struct dn_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_fill (struct dn_id*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int parse_range (int,char**,int /*<<< orphan*/ *,int) ; 
 struct dn_id* safe_calloc (int,int) ; 
 struct dn_id* safe_realloc (struct dn_id*,int) ; 

void
dummynet_list(int ac, char *av[], int show_counters)
{
	struct dn_id *oid, *x = NULL;
	int ret, i;
	int n; 		/* # of ranges */
	u_int buflen, l;
	u_int max_size;	/* largest obj passed up */

	(void)show_counters;	// XXX unused, but we should use it.
	ac--;
	av++; 		/* skip 'list' | 'show' word */

	n = parse_range(ac, av, NULL, 0);	/* Count # of ranges. */

	/* Allocate space to store ranges */
	l = sizeof(*oid) + sizeof(uint32_t) * n * 2;
	oid = safe_calloc(1, l);
	oid_fill(oid, l, DN_CMD_GET, DN_API_VERSION);

	if (n > 0)	/* store ranges in idx */
		parse_range(ac, av, (uint32_t *)(oid + 1), n*2);
	/*
	 * Compute the size of the largest object returned. If the
	 * response leaves at least this much spare space in the
	 * buffer, then surely the response is complete; otherwise
	 * there might be a risk of truncation and we will need to
	 * retry with a larger buffer.
	 * XXX don't bother with smaller structs.
	 */
	max_size = sizeof(struct dn_fs);
	if (max_size < sizeof(struct dn_sch))
		max_size = sizeof(struct dn_sch);
	if (max_size < sizeof(struct dn_flow))
		max_size = sizeof(struct dn_flow);

	switch (co.do_pipe) {
	case 1:
		oid->subtype = DN_LINK;	/* list pipe */
		break;
	case 2:
		oid->subtype = DN_FS;	/* list queue */
		break;
	case 3:
		oid->subtype = DN_SCH;	/* list sched */
		break;
	}

	/*
	 * Ask the kernel an estimate of the required space (result
	 * in oid.id), unless we are requesting a subset of objects,
	 * in which case the kernel does not give an exact answer.
	 * In any case, space might grow in the meantime due to the
	 * creation of new queues, so we must be prepared to retry.
	 */
	if (n > 0) {
		buflen = 4*1024;
	} else {
		ret = do_cmd(-IP_DUMMYNET3, oid, (uintptr_t)&l);
		if (ret != 0 || oid->id <= sizeof(*oid))
			goto done;
		buflen = oid->id + max_size;
		oid->len = sizeof(*oid); /* restore */
	}
	/* Try a few times, until the buffer fits */
	for (i = 0; i < 20; i++) {
		l = buflen;
		x = safe_realloc(x, l);
		bcopy(oid, x, oid->len);
		ret = do_cmd(-IP_DUMMYNET3, x, (uintptr_t)&l);
		if (ret != 0 || x->id <= sizeof(*oid))
			goto done; /* no response */
		if (l + max_size <= buflen)
			break; /* ok */
		buflen *= 2;	 /* double for next attempt */
	}
	list_pipes(x, O_NEXT(x, l));
done:
	if (x)
		free(x);
	free(oid);
}