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
struct platform_device {int dummy; } ;
struct altera_gpio_chip {int /*<<< orphan*/  mmchip; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_mm_gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct altera_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int altera_gpio_remove(struct platform_device *pdev)
{
	struct altera_gpio_chip *altera_gc = platform_get_drvdata(pdev);

	of_mm_gpiochip_remove(&altera_gc->mmchip);

	return 0;
}