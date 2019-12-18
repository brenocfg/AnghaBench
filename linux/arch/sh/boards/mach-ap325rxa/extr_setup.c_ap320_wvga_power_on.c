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
 int /*<<< orphan*/  FPGA_LCDREG ; 
 int /*<<< orphan*/  FPGA_LCDREG_VAL ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void ap320_wvga_power_on(void)
{
	msleep(100);

	/* ASD AP-320/325 LCD ON */
	__raw_writew(FPGA_LCDREG_VAL, FPGA_LCDREG);
}