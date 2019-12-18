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
 int /*<<< orphan*/  intel_ntb_interrupt (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ndev_irq_isr(void *arg)
{
	/* If we couldn't set up MSI-X, we only have the one vector. */
	intel_ntb_interrupt(arg, 0);
}