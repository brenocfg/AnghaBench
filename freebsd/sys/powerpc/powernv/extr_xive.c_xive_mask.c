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
typedef  scalar_t__ u_int ;
struct xive_irq {int flags; scalar_t__ eoi_page; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ MAX_XIVE_IRQS ; 
 int OPAL_XIVE_IRQ_LSI ; 
 scalar_t__ XIVE_IRQ_PQ_01 ; 
 int /*<<< orphan*/  xive_read_mmap8 (scalar_t__) ; 

__attribute__((used)) static void
xive_mask(device_t dev, u_int irq, void *priv)
{
	struct xive_irq *rirq;

	/* Never mask IPIs */
	if (irq == MAX_XIVE_IRQS)
		return;

	rirq = priv;

	if (!(rirq->flags & OPAL_XIVE_IRQ_LSI))
		return;
	xive_read_mmap8(rirq->eoi_page + XIVE_IRQ_PQ_01);
}