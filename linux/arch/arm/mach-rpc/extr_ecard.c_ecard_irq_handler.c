#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* chip; } ;
struct irq_desc {TYPE_4__ irq_data; } ;
struct TYPE_12__ {int slot_no; int /*<<< orphan*/  irq; TYPE_1__* ops; int /*<<< orphan*/  claimed; struct TYPE_12__* next; } ;
typedef  TYPE_3__ ecard_t ;
struct TYPE_14__ {int (* irqpending ) (TYPE_3__*) ;} ;
struct TYPE_11__ {int /*<<< orphan*/  (* irq_unmask ) (TYPE_4__*) ;int /*<<< orphan*/  (* irq_mask ) (TYPE_4__*) ;} ;
struct TYPE_10__ {int (* irqpending ) (TYPE_3__*) ;} ;

/* Variables and functions */
 TYPE_3__* cards ; 
 int /*<<< orphan*/  ecard_check_lockup (struct irq_desc*) ; 
 TYPE_8__ ecard_default_ops ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int stub2 (TYPE_3__*) ; 
 int stub3 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

__attribute__((used)) static void ecard_irq_handler(struct irq_desc *desc)
{
	ecard_t *ec;
	int called = 0;

	desc->irq_data.chip->irq_mask(&desc->irq_data);
	for (ec = cards; ec; ec = ec->next) {
		int pending;

		if (!ec->claimed || !ec->irq || ec->slot_no == 8)
			continue;

		if (ec->ops && ec->ops->irqpending)
			pending = ec->ops->irqpending(ec);
		else
			pending = ecard_default_ops.irqpending(ec);

		if (pending) {
			generic_handle_irq(ec->irq);
			called ++;
		}
	}
	desc->irq_data.chip->irq_unmask(&desc->irq_data);

	if (called == 0)
		ecard_check_lockup(desc);
}