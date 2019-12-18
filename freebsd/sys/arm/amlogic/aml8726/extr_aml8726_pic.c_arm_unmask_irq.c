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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_PIC_BIT (uintptr_t) ; 
 int /*<<< orphan*/  AML_PIC_MASK_REG (uintptr_t) ; 
 uintptr_t AML_PIC_NIRQS ; 
 int /*<<< orphan*/  CSR_BARRIER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_READ_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aml8726_pic_sc ; 
 int /*<<< orphan*/  arm_irq_memory_barrier (uintptr_t) ; 

void
arm_unmask_irq(uintptr_t nb)
{
	uint32_t mask;

	if (nb >= AML_PIC_NIRQS)
		return;

	arm_irq_memory_barrier(nb);

	mask = CSR_READ_4(aml8726_pic_sc, AML_PIC_MASK_REG(nb));
	mask |= AML_PIC_BIT(nb);
	CSR_WRITE_4(aml8726_pic_sc, AML_PIC_MASK_REG(nb), mask);

	CSR_BARRIER(aml8726_pic_sc, AML_PIC_MASK_REG(nb));
}