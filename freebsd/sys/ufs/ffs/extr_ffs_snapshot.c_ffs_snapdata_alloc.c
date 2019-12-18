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
struct snapdata {int /*<<< orphan*/  sn_lock; int /*<<< orphan*/  sn_head; } ;

/* Variables and functions */
 struct snapdata* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct snapdata*,int /*<<< orphan*/ ) ; 
 int LK_CANRECURSE ; 
 int LK_NOSHARE ; 
 int /*<<< orphan*/  M_UFSMNT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLKTIMEOUT ; 
 int /*<<< orphan*/  lockinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct snapdata* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sn_link ; 
 int /*<<< orphan*/  snapfree ; 
 int /*<<< orphan*/  snapfree_lock ; 

__attribute__((used)) static struct snapdata *
ffs_snapdata_alloc(void)
{
	struct snapdata *sn;

	/*
	 * Fetch a snapdata from the free list if there is one available.
	 */
	mtx_lock(&snapfree_lock);
	sn = LIST_FIRST(&snapfree);
	if (sn != NULL)
		LIST_REMOVE(sn, sn_link);
	mtx_unlock(&snapfree_lock);
	if (sn != NULL)
		return (sn);
	/*
 	 * If there were no free snapdatas allocate one.
	 */
	sn = malloc(sizeof *sn, M_UFSMNT, M_WAITOK | M_ZERO);
	TAILQ_INIT(&sn->sn_head);
	lockinit(&sn->sn_lock, PVFS, "snaplk", VLKTIMEOUT,
	    LK_CANRECURSE | LK_NOSHARE);
	return (sn);
}