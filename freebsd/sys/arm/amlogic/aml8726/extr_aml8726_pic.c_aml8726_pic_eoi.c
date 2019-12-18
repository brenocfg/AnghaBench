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

/* Variables and functions */
 int /*<<< orphan*/  AML_PIC_BIT (uintptr_t) ; 
 uintptr_t AML_PIC_NIRQS ; 
 int /*<<< orphan*/  AML_PIC_STAT_CLR_REG (uintptr_t) ; 
 int /*<<< orphan*/  CSR_BARRIER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_pic_sc ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (uintptr_t) ; 

__attribute__((used)) static void
aml8726_pic_eoi(void *arg)
{
	uintptr_t nb = (uintptr_t) arg;

	if (nb >= AML_PIC_NIRQS)
		return;

	arm_irq_memory_barrier(nb);

	CSR_WRITE_4(aml8726_pic_sc, AML_PIC_STAT_CLR_REG(nb), AML_PIC_BIT(nb));

	CSR_BARRIER(aml8726_pic_sc, AML_PIC_STAT_CLR_REG(nb));
}