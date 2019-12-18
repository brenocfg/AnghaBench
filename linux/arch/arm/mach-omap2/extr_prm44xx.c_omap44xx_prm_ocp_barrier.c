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

/* Variables and functions */
 int /*<<< orphan*/  OMAP4430_PRM_OCP_SOCKET_INST ; 
 int /*<<< orphan*/  OMAP4_REVISION_PRM_OFFSET ; 
 int /*<<< orphan*/  omap4_prm_read_inst_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap44xx_prm_ocp_barrier(void)
{
	omap4_prm_read_inst_reg(OMAP4430_PRM_OCP_SOCKET_INST,
				OMAP4_REVISION_PRM_OFFSET);
}