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

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int,void*) ; 
 int platform_get_irq (struct platform_device*,int) ; 

__attribute__((used)) static void sa11x0_dma_free_irq(struct platform_device *pdev, int nr,
	void *data)
{
	int irq = platform_get_irq(pdev, nr);
	if (irq > 0)
		free_irq(irq, data);
}