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
struct multicall_space {struct mmu_update* args; TYPE_1__* mc; } ;
struct mmu_update {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  MULTI_mmu_update (TYPE_1__*,struct mmu_update*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HYPERVISOR_mmu_update ; 
 struct multicall_space __xen_mc_entry (int) ; 
 struct multicall_space xen_mc_extend_args (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xen_extend_mmu_update(const struct mmu_update *update)
{
	struct multicall_space mcs;
	struct mmu_update *u;

	mcs = xen_mc_extend_args(__HYPERVISOR_mmu_update, sizeof(*u));

	if (mcs.mc != NULL) {
		mcs.mc->args[1]++;
	} else {
		mcs = __xen_mc_entry(sizeof(*u));
		MULTI_mmu_update(mcs.mc, mcs.args, 1, NULL, DOMID_SELF);
	}

	u = mcs.args;
	*u = *update;
}