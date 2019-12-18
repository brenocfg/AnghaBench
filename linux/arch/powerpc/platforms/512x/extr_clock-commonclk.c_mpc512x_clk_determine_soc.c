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
 int /*<<< orphan*/  MPC512x_SOC_MPC5121 ; 
 int /*<<< orphan*/  MPC512x_SOC_MPC5123 ; 
 int /*<<< orphan*/  MPC512x_SOC_MPC5125 ; 
 scalar_t__ of_machine_is_compatible (char*) ; 
 int /*<<< orphan*/  soc ; 

__attribute__((used)) static void mpc512x_clk_determine_soc(void)
{
	if (of_machine_is_compatible("fsl,mpc5121")) {
		soc = MPC512x_SOC_MPC5121;
		return;
	}
	if (of_machine_is_compatible("fsl,mpc5123")) {
		soc = MPC512x_SOC_MPC5123;
		return;
	}
	if (of_machine_is_compatible("fsl,mpc5125")) {
		soc = MPC512x_SOC_MPC5125;
		return;
	}
}