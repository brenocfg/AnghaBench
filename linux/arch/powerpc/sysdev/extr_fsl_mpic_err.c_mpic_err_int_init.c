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
struct mpic {int /*<<< orphan*/  err_regs; int /*<<< orphan*/  irqhost; } ;
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_NO_THREAD ; 
 int /*<<< orphan*/  fsl_error_int_handler ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpic_fsl_err_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int request_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mpic*) ; 

void mpic_err_int_init(struct mpic *mpic, irq_hw_number_t irqnum)
{
	unsigned int virq;
	int ret;

	virq = irq_create_mapping(mpic->irqhost, irqnum);
	if (!virq) {
		pr_err("Error interrupt setup failed\n");
		return;
	}

	/* Mask all error interrupts */
	mpic_fsl_err_write(mpic->err_regs, ~0);

	ret = request_irq(virq, fsl_error_int_handler, IRQF_NO_THREAD,
		    "mpic-error-int", mpic);
	if (ret)
		pr_err("Failed to register error interrupt handler\n");
}