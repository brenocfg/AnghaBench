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
struct pt_regs {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int check_stack_overflow () ; 
 int /*<<< orphan*/  execute_on_irq_stack (int,struct irq_desc*) ; 
 int /*<<< orphan*/  generic_handle_irq_desc (struct irq_desc*) ; 
 int /*<<< orphan*/  print_stack_overflow () ; 
 scalar_t__ unlikely (int) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void handle_irq(struct irq_desc *desc, struct pt_regs *regs)
{
	int overflow = check_stack_overflow();

	if (user_mode(regs) || !execute_on_irq_stack(overflow, desc)) {
		if (unlikely(overflow))
			print_stack_overflow();
		generic_handle_irq_desc(desc);
	}
}