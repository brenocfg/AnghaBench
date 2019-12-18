#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct irq_data {int dummy; } ;
struct iic {size_t eoi_ptr; int /*<<< orphan*/ * eoi_stack; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  cpu_iic ; 
 int /*<<< orphan*/  out_be64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iic* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iic_eoi(struct irq_data *d)
{
	struct iic *iic = this_cpu_ptr(&cpu_iic);
	out_be64(&iic->regs->prio, iic->eoi_stack[--iic->eoi_ptr]);
	BUG_ON(iic->eoi_ptr < 0);
}