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
 int /*<<< orphan*/  MCFGR_AXIPIPE_MASK ; 
 int MCFGR_AXIPIPE_SHIFT ; 
 int /*<<< orphan*/  clrsetbits_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ of_machine_is_compatible (char*) ; 

__attribute__((used)) static void handle_imx6_err005766(u32 *mcr)
{
	if (of_machine_is_compatible("fsl,imx6q") ||
	    of_machine_is_compatible("fsl,imx6dl") ||
	    of_machine_is_compatible("fsl,imx6qp"))
		clrsetbits_32(mcr, MCFGR_AXIPIPE_MASK,
			      1 << MCFGR_AXIPIPE_SHIFT);
}