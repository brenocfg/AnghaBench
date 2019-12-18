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
typedef  int u32 ;
struct mpic {unsigned int* err_int_vecs; int /*<<< orphan*/  err_regs; } ;
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPIC_ERR_INT_EIMR ; 
 struct mpic* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int mpic_fsl_err_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpic_fsl_err_write (int /*<<< orphan*/ ,int) ; 
 unsigned int virq_to_hw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsl_mpic_unmask_err(struct irq_data *d)
{
	u32 eimr;
	struct mpic *mpic = irq_data_get_irq_chip_data(d);
	unsigned int src = virq_to_hw(d->irq) - mpic->err_int_vecs[0];

	eimr = mpic_fsl_err_read(mpic->err_regs, MPIC_ERR_INT_EIMR);
	eimr &= ~(1 << (31 - src));
	mpic_fsl_err_write(mpic->err_regs, eimr);
}