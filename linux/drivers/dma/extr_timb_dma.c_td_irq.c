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
typedef  scalar_t__ u32 ;
struct timb_dma {int /*<<< orphan*/  tasklet; scalar_t__ membase; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TIMBDMA_IER ; 
 scalar_t__ TIMBDMA_IPR ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t td_irq(int irq, void *devid)
{
	struct timb_dma *td = devid;
	u32 ipr = ioread32(td->membase + TIMBDMA_IPR);

	if (ipr) {
		/* disable interrupts, will be re-enabled in tasklet */
		iowrite32(0, td->membase + TIMBDMA_IER);

		tasklet_schedule(&td->tasklet);

		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}