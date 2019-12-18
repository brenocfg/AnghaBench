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
struct xive_irq_data {int flags; int /*<<< orphan*/  trig_mmio; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int XIVE_IRQ_FLAG_LSI ; 
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool xive_irq_trigger(struct xive_irq_data *xd)
{
	/* This should be only for MSIs */
	if (WARN_ON(xd->flags & XIVE_IRQ_FLAG_LSI))
		return false;

	/* Those interrupts should always have a trigger page */
	if (WARN_ON(!xd->trig_mmio))
		return false;

	out_be64(xd->trig_mmio, 0);

	return true;
}