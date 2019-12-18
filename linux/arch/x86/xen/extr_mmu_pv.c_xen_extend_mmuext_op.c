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
struct multicall_space {struct mmuext_op* args; TYPE_1__* mc; } ;
struct mmuext_op {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * args; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMID_SELF ; 
 int /*<<< orphan*/  MULTI_mmuext_op (TYPE_1__*,struct mmuext_op*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __HYPERVISOR_mmuext_op ; 
 struct multicall_space __xen_mc_entry (int) ; 
 struct multicall_space xen_mc_extend_args (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xen_extend_mmuext_op(const struct mmuext_op *op)
{
	struct multicall_space mcs;
	struct mmuext_op *u;

	mcs = xen_mc_extend_args(__HYPERVISOR_mmuext_op, sizeof(*u));

	if (mcs.mc != NULL) {
		mcs.mc->args[1]++;
	} else {
		mcs = __xen_mc_entry(sizeof(*u));
		MULTI_mmuext_op(mcs.mc, mcs.args, 1, NULL, DOMID_SELF);
	}

	u = mcs.args;
	*u = *op;
}