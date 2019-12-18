#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SHARPSL_SUSPENDED ; 
 int /*<<< orphan*/  SPITZ_GPIO_CHRG_ON ; 
 int /*<<< orphan*/  SPITZ_GPIO_JK_B ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sharpsl_pm ; 

__attribute__((used)) static void spitz_charge(int on)
{
	if (on) {
		if (sharpsl_pm.flags & SHARPSL_SUSPENDED) {
			gpio_set_value(SPITZ_GPIO_JK_B, 1);
			gpio_set_value(SPITZ_GPIO_CHRG_ON, 0);
		} else {
			gpio_set_value(SPITZ_GPIO_JK_B, 0);
			gpio_set_value(SPITZ_GPIO_CHRG_ON, 0);
		}
	} else {
		gpio_set_value(SPITZ_GPIO_JK_B, 0);
		gpio_set_value(SPITZ_GPIO_CHRG_ON, 1);
	}
}