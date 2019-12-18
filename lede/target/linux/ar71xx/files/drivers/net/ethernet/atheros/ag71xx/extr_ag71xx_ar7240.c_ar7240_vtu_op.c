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
typedef  int u32 ;
struct mii_bus {int dummy; } ;
struct ar7240sw {struct mii_bus* mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR7240_REG_VTU ; 
 int /*<<< orphan*/  AR7240_REG_VTU_DATA ; 
 int AR7240_VTUDATA_MEMBER ; 
 int AR7240_VTUDATA_VALID ; 
 int AR7240_VTU_ACTIVE ; 
 int AR7240_VTU_OP ; 
 int AR7240_VTU_OP_LOAD ; 
 scalar_t__ ar7240sw_reg_wait (struct mii_bus*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar7240sw_reg_write (struct mii_bus*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar7240_vtu_op(struct ar7240sw *as, u32 op, u32 val)
{
	struct mii_bus *mii = as->mii_bus;

	if (ar7240sw_reg_wait(mii, AR7240_REG_VTU, AR7240_VTU_ACTIVE, 0, 5))
		return;

	if ((op & AR7240_VTU_OP) == AR7240_VTU_OP_LOAD) {
		val &= AR7240_VTUDATA_MEMBER;
		val |= AR7240_VTUDATA_VALID;
		ar7240sw_reg_write(mii, AR7240_REG_VTU_DATA, val);
	}
	op |= AR7240_VTU_ACTIVE;
	ar7240sw_reg_write(mii, AR7240_REG_VTU, op);
}