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
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ C_DDR_CMD_REG ; 
 int /*<<< orphan*/  ddr_poll_until_not_busy () ; 

__attribute__((used)) static void ddr_issue_command(int commmand)
{
	*(volatile UINT *) C_DDR_CMD_REG = commmand;
	ddr_poll_until_not_busy();
}