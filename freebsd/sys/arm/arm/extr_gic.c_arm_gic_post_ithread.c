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
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  arm_gic_enable_intr (int /*<<< orphan*/ ,struct intr_irqsrc*) ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_gic_post_ithread(device_t dev, struct intr_irqsrc *isrc)
{

	arm_irq_memory_barrier(0);
	arm_gic_enable_intr(dev, isrc);
}