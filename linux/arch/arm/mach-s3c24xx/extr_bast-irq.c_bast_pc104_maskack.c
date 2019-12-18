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
struct irq_data {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* irq_ack ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int BAST_IRQ_ISA ; 
 int /*<<< orphan*/  bast_pc104_mask (struct irq_data*) ; 
 struct irq_desc* irq_desc ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
bast_pc104_maskack(struct irq_data *data)
{
	struct irq_desc *desc = irq_desc + BAST_IRQ_ISA;

	bast_pc104_mask(data);
	desc->irq_data.chip->irq_ack(&desc->irq_data);
}