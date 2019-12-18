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
 int /*<<< orphan*/  __ffs (unsigned long) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 unsigned int viper_bit_to_irq (int /*<<< orphan*/ ) ; 
 unsigned long viper_irq_pending () ; 

__attribute__((used)) static void viper_irq_handler(struct irq_desc *desc)
{
	unsigned int irq;
	unsigned long pending;

	pending = viper_irq_pending();
	do {
		/* we're in a chained irq handler,
		 * so ack the interrupt by hand */
		desc->irq_data.chip->irq_ack(&desc->irq_data);

		if (likely(pending)) {
			irq = viper_bit_to_irq(__ffs(pending));
			generic_handle_irq(irq);
		}
		pending = viper_irq_pending();
	} while (pending);
}