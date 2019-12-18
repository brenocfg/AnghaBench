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
typedef  int /*<<< orphan*/  u_int ;
struct xive_irq {scalar_t__ eoi_page; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ XIVE_IRQ_PQ_00 ; 
 int /*<<< orphan*/  xive_read_mmap8 (scalar_t__) ; 

__attribute__((used)) static void
xive_unmask(device_t dev, u_int irq, void *priv)
{
	struct xive_irq *rirq;

	rirq = priv;

	xive_read_mmap8(rirq->eoi_page + XIVE_IRQ_PQ_00);
}