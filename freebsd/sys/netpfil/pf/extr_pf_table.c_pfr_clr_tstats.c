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
struct pfr_table {int dummy; } ;
struct pfr_ktableworkq {int dummy; } ;
struct pfr_ktable {int /*<<< orphan*/  pfrkt_t; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT_FLAGS (int,int) ; 
 int EINVAL ; 
 int PFR_FLAG_ADDRSTOO ; 
 int PFR_FLAG_DUMMY ; 
 struct pfr_ktable* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pfr_ktable*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct pfr_ktableworkq*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct pfr_ktableworkq*,struct pfr_ktable*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_pfr_ktables ; 
 int /*<<< orphan*/  bcopy (struct pfr_table*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pfr_clstats_ktables (struct pfr_ktableworkq*,long,int) ; 
 int /*<<< orphan*/  pfr_ktablehead ; 
 scalar_t__ pfr_validate_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfrkt_workq ; 
 long time_second ; 

int
pfr_clr_tstats(struct pfr_table *tbl, int size, int *nzero, int flags)
{
	struct pfr_ktableworkq	 workq;
	struct pfr_ktable	*p, key;
	int			 i, xzero = 0;
	long			 tzero = time_second;

	ACCEPT_FLAGS(flags, PFR_FLAG_DUMMY | PFR_FLAG_ADDRSTOO);
	SLIST_INIT(&workq);
	for (i = 0; i < size; i++) {
		bcopy(tbl + i, &key.pfrkt_t, sizeof(key.pfrkt_t));
		if (pfr_validate_table(&key.pfrkt_t, 0, 0))
			return (EINVAL);
		p = RB_FIND(pfr_ktablehead, &V_pfr_ktables, &key);
		if (p != NULL) {
			SLIST_INSERT_HEAD(&workq, p, pfrkt_workq);
			xzero++;
		}
	}
	if (!(flags & PFR_FLAG_DUMMY))
		pfr_clstats_ktables(&workq, tzero, flags & PFR_FLAG_ADDRSTOO);
	if (nzero != NULL)
		*nzero = xzero;
	return (0);
}