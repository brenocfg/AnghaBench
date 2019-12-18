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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  OCP_MOD ; 
 int /*<<< orphan*/  OMAP3_PRM_IRQENABLE_MPU_OFFSET ; 
 int /*<<< orphan*/  omap2_prm_write_mod_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap3xxx_prm_restore_irqen(u32 *saved_mask)
{
	omap2_prm_write_mod_reg(saved_mask[0], OCP_MOD,
				OMAP3_PRM_IRQENABLE_MPU_OFFSET);
}