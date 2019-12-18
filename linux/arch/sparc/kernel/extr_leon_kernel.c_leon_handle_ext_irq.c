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
struct irq_desc {int dummy; } ;
struct irq_bucket {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  generic_handle_irq (scalar_t__) ; 
 struct irq_bucket** irq_map ; 
 unsigned int leon_eirq_get (int) ; 
 int sparc_leon3_cpuid () ; 

__attribute__((used)) static void leon_handle_ext_irq(struct irq_desc *desc)
{
	unsigned int eirq;
	struct irq_bucket *p;
	int cpu = sparc_leon3_cpuid();

	eirq = leon_eirq_get(cpu);
	p = irq_map[eirq];
	if ((eirq & 0x10) && p && p->irq) /* bit4 tells if IRQ happened */
		generic_handle_irq(p->irq);
}