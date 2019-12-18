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

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_interrupt_ciu2_mask_unmask_irq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __cvmx_interrupt_ciu2_unmask_irq(int irq_number)
{
    __cvmx_interrupt_ciu2_mask_unmask_irq(irq_number, 0);
}