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
 int GRF_GPIO0B_PULL ; 
 int /*<<< orphan*/  grf_write_4 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rk30_grf_sc ; 

void
rk30_grf_gpio_pud(uint32_t bank, uint32_t pin, uint32_t state)
{
	uint32_t offset;

	offset = GRF_GPIO0B_PULL - 4 + (bank * 16) + ((pin / 8) * 4);
	pin = (7 - (pin % 8)) * 2;
	grf_write_4(rk30_grf_sc, offset, (0x3 << (16 + pin)) | (state << pin));
}