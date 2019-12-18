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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR933X_RESET_REG_RESET_MODULE ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar933x_chip_device_stopped(uint32_t mask)
{
	uint32_t reg;

	reg = ATH_READ_REG(AR933X_RESET_REG_RESET_MODULE);
	return ((reg & mask) == mask);
}