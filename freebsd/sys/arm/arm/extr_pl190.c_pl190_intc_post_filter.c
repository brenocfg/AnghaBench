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
struct pl190_intc_irqsrc {int /*<<< orphan*/  irq; } ;
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pl190_intc_post_filter(device_t dev, struct intr_irqsrc *isrc)
{
	struct pl190_intc_irqsrc *src;

	src = (struct pl190_intc_irqsrc *)isrc;
	arm_irq_memory_barrier(src->irq);
}