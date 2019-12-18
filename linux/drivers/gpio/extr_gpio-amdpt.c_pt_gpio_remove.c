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
struct pt_gpio_chip {int /*<<< orphan*/  gc; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct pt_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pt_gpio_remove(struct platform_device *pdev)
{
	struct pt_gpio_chip *pt_gpio = platform_get_drvdata(pdev);

	gpiochip_remove(&pt_gpio->gc);

	return 0;
}