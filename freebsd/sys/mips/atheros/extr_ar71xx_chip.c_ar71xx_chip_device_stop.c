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
 int /*<<< orphan*/  AR71XX_RST_RESET ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar71xx_chip_device_stop(uint32_t mask)
{
	uint32_t reg;

	reg = ATH_READ_REG(AR71XX_RST_RESET);
	ATH_WRITE_REG(AR71XX_RST_RESET, reg | mask);
}