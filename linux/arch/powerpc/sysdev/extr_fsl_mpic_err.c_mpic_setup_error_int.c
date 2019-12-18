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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct mpic {int /*<<< orphan*/ * err_int_vecs; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; TYPE_1__ hc_err; int /*<<< orphan*/  err_regs; scalar_t__ paddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MPIC_ERR_INT_BASE ; 
 int /*<<< orphan*/  MPIC_FSL_HAS_EIMR ; 
 int MPIC_MAX_ERR ; 
 TYPE_1__ fsl_mpic_err_chip ; 
 int /*<<< orphan*/  ioremap (scalar_t__,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

int mpic_setup_error_int(struct mpic *mpic, int intvec)
{
	int i;

	mpic->err_regs = ioremap(mpic->paddr + MPIC_ERR_INT_BASE, 0x1000);
	if (!mpic->err_regs) {
		pr_err("could not map mpic error registers\n");
		return -ENOMEM;
	}
	mpic->hc_err = fsl_mpic_err_chip;
	mpic->hc_err.name = mpic->name;
	mpic->flags |= MPIC_FSL_HAS_EIMR;
	/* allocate interrupt vectors for error interrupts */
	for (i = MPIC_MAX_ERR - 1; i >= 0; i--)
		mpic->err_int_vecs[i] = intvec--;

	return 0;
}