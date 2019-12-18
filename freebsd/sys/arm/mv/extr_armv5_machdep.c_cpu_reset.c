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
 int /*<<< orphan*/  RSTOUTn_MASK ; 
 int /*<<< orphan*/  SOFT_RST_OUT_EN ; 
 int /*<<< orphan*/  SYSTEM_SOFT_RESET ; 
 int /*<<< orphan*/  SYS_SOFT_RST ; 
 int /*<<< orphan*/  write_cpu_ctrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cpu_reset(void)
{

	write_cpu_ctrl(RSTOUTn_MASK, SOFT_RST_OUT_EN);
	write_cpu_ctrl(SYSTEM_SOFT_RESET, SYS_SOFT_RST);
	while(1);
}