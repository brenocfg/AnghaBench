#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* chip; } ;
struct irq_desc {TYPE_2__ irq_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_ack ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  LPD270_INT_STATUS ; 
 unsigned int LPD270_IRQ (int /*<<< orphan*/ ) ; 
 unsigned int __ffs (unsigned long) ; 
 unsigned long __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ likely (unsigned long) ; 
 unsigned long lpd270_irq_enabled ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void lpd270_irq_handler(struct irq_desc *desc)
{
	unsigned int irq;
	unsigned long pending;

	pending = __raw_readw(LPD270_INT_STATUS) & lpd270_irq_enabled;
	do {
		/* clear useless edge notification */
		desc->irq_data.chip->irq_ack(&desc->irq_data);
		if (likely(pending)) {
			irq = LPD270_IRQ(0) + __ffs(pending);
			generic_handle_irq(irq);

			pending = __raw_readw(LPD270_INT_STATUS) &
						lpd270_irq_enabled;
		}
	} while (pending);
}