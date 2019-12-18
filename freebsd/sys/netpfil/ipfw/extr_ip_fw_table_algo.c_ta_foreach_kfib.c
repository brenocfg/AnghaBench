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
typedef  int /*<<< orphan*/  walktree_f_t ;
typedef  int /*<<< orphan*/  ta_foreach_f ;
struct table_info {int /*<<< orphan*/  data; } ;
struct rib_head {int (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  RIB_RLOCK (struct rib_head*) ; 
 int /*<<< orphan*/  RIB_RLOCK_TRACKER ; 
 int /*<<< orphan*/  RIB_RUNLOCK (struct rib_head*) ; 
 struct rib_head* rt_tables_get_rnh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
ta_foreach_kfib(void *ta_state, struct table_info *ti, ta_foreach_f *f,
    void *arg)
{
	RIB_RLOCK_TRACKER;
	struct rib_head *rh;
	int error;

	rh = rt_tables_get_rnh(ti->data, AF_INET);
	if (rh != NULL) {
		RIB_RLOCK(rh); 
		error = rh->rnh_walktree(&rh->head, (walktree_f_t *)f, arg);
		RIB_RUNLOCK(rh);
	}

	rh = rt_tables_get_rnh(ti->data, AF_INET6);
	if (rh != NULL) {
		RIB_RLOCK(rh); 
		error = rh->rnh_walktree(&rh->head, (walktree_f_t *)f, arg);
		RIB_RUNLOCK(rh); 
	}
}