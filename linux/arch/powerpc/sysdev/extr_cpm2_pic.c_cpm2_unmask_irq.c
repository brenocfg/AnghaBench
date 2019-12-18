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
struct TYPE_2__ {int /*<<< orphan*/  ic_simrh; } ;

/* Variables and functions */
 TYPE_1__* cpm2_intctl ; 
 int* irq_to_siubit ; 
 int* irq_to_siureg ; 
 unsigned int irqd_to_hwirq (struct irq_data*) ; 
 int /*<<< orphan*/  out_be32 (int /*<<< orphan*/ *,int) ; 
 int* ppc_cached_irq_mask ; 

__attribute__((used)) static void cpm2_unmask_irq(struct irq_data *d)
{
	int	bit, word;
	unsigned int irq_nr = irqd_to_hwirq(d);

	bit = irq_to_siubit[irq_nr];
	word = irq_to_siureg[irq_nr];

	ppc_cached_irq_mask[word] |= 1 << bit;
	out_be32(&cpm2_intctl->ic_simrh + word, ppc_cached_irq_mask[word]);
}