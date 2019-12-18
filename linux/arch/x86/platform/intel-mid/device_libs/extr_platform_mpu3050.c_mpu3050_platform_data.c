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
struct i2c_board_info {scalar_t__ irq; } ;

/* Variables and functions */
 scalar_t__ INTEL_MID_IRQ_OFFSET ; 
 int get_gpio_by_name (char*) ; 

__attribute__((used)) static void *mpu3050_platform_data(void *info)
{
	struct i2c_board_info *i2c_info = info;
	int intr = get_gpio_by_name("mpu3050_int");

	if (intr < 0)
		return NULL;

	i2c_info->irq = intr + INTEL_MID_IRQ_OFFSET;
	return NULL;
}