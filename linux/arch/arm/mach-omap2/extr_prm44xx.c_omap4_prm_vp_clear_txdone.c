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
struct omap4_vp {int /*<<< orphan*/  irqstatus_mpu; int /*<<< orphan*/  tranxdone_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_PRM_OCP_SOCKET_INST ; 
 int /*<<< orphan*/  OMAP4430_PRM_PARTITION ; 
 int /*<<< orphan*/  omap4_prminst_write_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap4_vp* omap4_vp ; 

__attribute__((used)) static void omap4_prm_vp_clear_txdone(u8 vp_id)
{
	struct omap4_vp *vp = &omap4_vp[vp_id];

	omap4_prminst_write_inst_reg(vp->tranxdone_status,
				     OMAP4430_PRM_PARTITION,
				     OMAP4430_PRM_OCP_SOCKET_INST,
				     vp->irqstatus_mpu);
}