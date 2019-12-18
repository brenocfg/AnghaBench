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
struct table_info {scalar_t__ xstate; scalar_t__ state; } ;
struct radix_node_head {int /*<<< orphan*/  rh; int /*<<< orphan*/  (* rnh_walktree ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
ta_foreach_radix(void *ta_state, struct table_info *ti, ta_foreach_f *f,
    void *arg)
{
	struct radix_node_head *rnh;

	rnh = (struct radix_node_head *)(ti->state);
	rnh->rnh_walktree(&rnh->rh, (walktree_f_t *)f, arg);

	rnh = (struct radix_node_head *)(ti->xstate);
	rnh->rnh_walktree(&rnh->rh, (walktree_f_t *)f, arg);
}