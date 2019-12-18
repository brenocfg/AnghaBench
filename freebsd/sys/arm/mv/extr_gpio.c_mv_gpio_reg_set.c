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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mv_gpio_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mv_gpio_reg_set(device_t dev, uint32_t reg, uint32_t pin)
{
	uint32_t reg_val;

	reg_val = mv_gpio_reg_read(dev, reg);
	reg_val |= GPIO(pin);
	mv_gpio_reg_write(dev, reg, reg_val);
}