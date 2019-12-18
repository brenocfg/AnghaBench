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
struct irq_desc {int dummy; } ;
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 unsigned int INT_NUM_IM_OFFSET ; 
 scalar_t__ LTQ_EBU_PCC_ISTAT ; 
 scalar_t__ LTQ_ICU_EBU_IRQ ; 
 int /*<<< orphan*/  LTQ_ICU_IOSR ; 
 scalar_t__ MIPS_CPU_IRQ_CASCADE ; 
 scalar_t__ __fls (scalar_t__) ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 int irq_desc_get_irq (struct irq_desc*) ; 
 int /*<<< orphan*/  irq_linear_revmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ltq_domain ; 
 int ltq_ebu_r32 (scalar_t__) ; 
 int /*<<< orphan*/  ltq_ebu_w32 (int,scalar_t__) ; 
 scalar_t__ ltq_icu_r32 (int,unsigned int,int /*<<< orphan*/ ) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void ltq_hw_irq_handler(struct irq_desc *desc)
{
	unsigned int module = irq_desc_get_irq(desc) - 2;
	u32 irq;
	irq_hw_number_t hwirq;
	int vpe = smp_processor_id();

	irq = ltq_icu_r32(vpe, module, LTQ_ICU_IOSR);
	if (irq == 0)
		return;

	/*
	 * silicon bug causes only the msb set to 1 to be valid. all
	 * other bits might be bogus
	 */
	irq = __fls(irq);
	hwirq = irq + MIPS_CPU_IRQ_CASCADE + (INT_NUM_IM_OFFSET * module);
	generic_handle_irq(irq_linear_revmap(ltq_domain, hwirq));

	/* if this is a EBU irq, we need to ack it or get a deadlock */
	if ((irq == LTQ_ICU_EBU_IRQ) && (module == 0) && LTQ_EBU_PCC_ISTAT)
		ltq_ebu_w32(ltq_ebu_r32(LTQ_EBU_PCC_ISTAT) | 0x10,
			LTQ_EBU_PCC_ISTAT);
}