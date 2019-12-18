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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOMUX_TO_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MX31_PIN_GPIO3_1 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  gpio_free_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mx31_3ds_sdhc1_gpios ; 

__attribute__((used)) static void mx31_3ds_sdhc1_exit(struct device *dev, void *data)
{
	free_irq(gpio_to_irq(IOMUX_TO_GPIO(MX31_PIN_GPIO3_1)), data);
	gpio_free_array(mx31_3ds_sdhc1_gpios,
			 ARRAY_SIZE(mx31_3ds_sdhc1_gpios));
}