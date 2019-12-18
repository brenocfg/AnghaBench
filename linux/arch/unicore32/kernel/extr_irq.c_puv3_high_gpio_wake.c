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
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_PWER ; 
 int PM_PWER_GPIOHIGH ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int puv3_high_gpio_wake(struct irq_data *d, unsigned int on)
{
	if (on)
		writel(readl(PM_PWER) | PM_PWER_GPIOHIGH, PM_PWER);
	else
		writel(readl(PM_PWER) & ~PM_PWER_GPIOHIGH, PM_PWER);
	return 0;
}