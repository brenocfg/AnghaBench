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
struct inpcblbgroup {int /*<<< orphan*/  il_epoch_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_LIST_REMOVE (struct inpcblbgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoch_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_list ; 
 int /*<<< orphan*/  in_pcblbgroup_free_deferred ; 
 int /*<<< orphan*/  net_epoch_preempt ; 

__attribute__((used)) static void
in_pcblbgroup_free(struct inpcblbgroup *grp)
{

	CK_LIST_REMOVE(grp, il_list);
	epoch_call(net_epoch_preempt, &grp->il_epoch_ctx,
	    in_pcblbgroup_free_deferred);
}