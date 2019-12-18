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
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QCA953X_RESET_REG_RESET_MODULE ; 

__attribute__((used)) static void
qca953x_chip_device_start(uint32_t mask)
{
	uint32_t reg;

	reg = ATH_READ_REG(QCA953X_RESET_REG_RESET_MODULE);
	ATH_WRITE_REG(QCA953X_RESET_REG_RESET_MODULE, reg & ~mask);
}