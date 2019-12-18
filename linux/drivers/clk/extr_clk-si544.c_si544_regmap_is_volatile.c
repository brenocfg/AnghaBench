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
#define  SI544_REG_CONTROL 129 
#define  SI544_REG_FCAL_OVR 128 

__attribute__((used)) static bool si544_regmap_is_volatile(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case SI544_REG_CONTROL:
	case SI544_REG_FCAL_OVR:
		return true;
	default:
		return false;
	}
}