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
struct device {int dummy; } ;

/* Variables and functions */
#define  SI5351_DEVICE_STATUS 130 
#define  SI5351_INTERRUPT_STATUS 129 
#define  SI5351_PLL_RESET 128 

__attribute__((used)) static bool si5351_regmap_is_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SI5351_DEVICE_STATUS:
	case SI5351_INTERRUPT_STATUS:
	case SI5351_PLL_RESET:
		return true;
	}
	return false;
}