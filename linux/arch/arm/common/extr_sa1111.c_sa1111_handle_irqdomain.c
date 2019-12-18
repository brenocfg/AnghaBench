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
struct irq_domain {int dummy; } ;
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq_desc (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_linear_revmap (struct irq_domain*,int) ; 
 struct irq_desc* irq_to_desc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sa1111_handle_irqdomain(struct irq_domain *irqdomain, int irq)
{
	struct irq_desc *d = irq_to_desc(irq_linear_revmap(irqdomain, irq));

	if (d)
		generic_handle_irq_desc(d);
}