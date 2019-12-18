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
typedef  int uint32_t ;
struct nat64lsn_pgchunk {struct nat64lsn_pg** pgptr; } ;
struct nat64lsn_pg {int dummy; } ;
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 scalar_t__ FREEMASK_BITCOUNT (struct nat64lsn_pg*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISSET32 (int,int) ; 
 int NAT64LSN_TRY_PGCNT ; 
 int /*<<< orphan*/  ck_pr_cas_32 (int*,int,int) ; 
 int /*<<< orphan*/  ck_pr_cas_ptr (struct nat64lsn_pg**,struct nat64lsn_pg*,struct nat64lsn_pg*) ; 
 int /*<<< orphan*/  ck_pr_fence_load () ; 
 int ck_pr_load_32 (int*) ; 
 struct nat64lsn_pg* ck_pr_load_ptr (struct nat64lsn_pg**) ; 

__attribute__((used)) static struct nat64lsn_pg*
nat64lsn_get_pg(uint32_t *chunkmask, uint32_t *pgmask,
    struct nat64lsn_pgchunk **chunks, struct nat64lsn_pg **pgptr,
    uint32_t *pgidx, in_addr_t faddr)
{
	struct nat64lsn_pg *pg, *oldpg;
	uint32_t idx, oldidx;
	int cnt;

	cnt = 0;
	/* First try last used PG */
	oldpg = pg = ck_pr_load_ptr(pgptr);
	idx = oldidx = ck_pr_load_32(pgidx);
	/* If pgidx is out of range, reset it to the first pgchunk */
	if (!ISSET32(*chunkmask, idx / 32))
		idx = 0;
	do {
		ck_pr_fence_load();
		if (pg != NULL && FREEMASK_BITCOUNT(pg, faddr) > 0) {
			/*
			 * If last used PG has not free states,
			 * try to update pointer.
			 * NOTE: it can be already updated by jobs handler,
			 *	 thus we use CAS operation.
			 */
			if (cnt > 0)
				ck_pr_cas_ptr(pgptr, oldpg, pg);
			return (pg);
		}
		/* Stop if idx is out of range */
		if (!ISSET32(*chunkmask, idx / 32))
			break;

		if (ISSET32(pgmask[idx / 32], idx % 32))
			pg = ck_pr_load_ptr(
			    &chunks[idx / 32]->pgptr[idx % 32]);
		else
			pg = NULL;

		idx++;
	} while (++cnt < NAT64LSN_TRY_PGCNT);

	/* If pgidx is out of range, reset it to the first pgchunk */
	if (!ISSET32(*chunkmask, idx / 32))
		idx = 0;
	ck_pr_cas_32(pgidx, oldidx, idx);
	return (NULL);
}