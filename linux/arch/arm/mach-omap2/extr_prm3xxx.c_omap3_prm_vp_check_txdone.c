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
typedef  size_t u8 ;
typedef  int u32 ;
struct omap3_vp {int tranxdone_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCP_MOD ; 
 int /*<<< orphan*/  OMAP3_PRM_IRQSTATUS_MPU_OFFSET ; 
 int omap2_prm_read_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap3_vp* omap3_vp ; 

__attribute__((used)) static u32 omap3_prm_vp_check_txdone(u8 vp_id)
{
	struct omap3_vp *vp = &omap3_vp[vp_id];
	u32 irqstatus;

	irqstatus = omap2_prm_read_mod_reg(OCP_MOD,
					   OMAP3_PRM_IRQSTATUS_MPU_OFFSET);
	return irqstatus & vp->tranxdone_status;
}