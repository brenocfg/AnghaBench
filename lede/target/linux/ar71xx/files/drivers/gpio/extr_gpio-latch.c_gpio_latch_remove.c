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
struct gpio_latch_chip {int /*<<< orphan*/  gc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiochip_remove (int /*<<< orphan*/ *) ; 
 struct gpio_latch_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int gpio_latch_remove(struct platform_device *pdev)
{
	struct gpio_latch_chip *glc = platform_get_drvdata(pdev);

	gpiochip_remove(&glc->gc);
	return 0;
}