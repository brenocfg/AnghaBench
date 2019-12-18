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
 uintptr_t ERR_IRQ ; 
 scalar_t__ MPIC_CPU (int) ; 
 int /*<<< orphan*/  MPIC_CPU_WRITE (int /*<<< orphan*/ ,scalar_t__,uintptr_t) ; 
 int /*<<< orphan*/  MPIC_ICE ; 
 uintptr_t MPIC_INT_LOCAL ; 
 scalar_t__ MPIC_ISM ; 
 int /*<<< orphan*/  MPIC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t) ; 
 uintptr_t MSI_IRQ ; 
 int mp_ncpus ; 
 scalar_t__ mpic_irq_is_percpu (uintptr_t) ; 
 int /*<<< orphan*/  mpic_mask_irq_err (uintptr_t) ; 
 int /*<<< orphan*/  mv_mpic_sc ; 

__attribute__((used)) static void
mpic_mask_irq(uintptr_t nb)
{

#ifdef SMP
	int cpu;

	if (nb == MPIC_INT_LOCAL) {
		for (cpu = 0; cpu < mp_ncpus; cpu++)
			MPIC_CPU_WRITE(mv_mpic_sc,
			    MPIC_CPU(cpu) + MPIC_ISM, nb);
		return;
	}
#endif
	if (mpic_irq_is_percpu(nb))
		MPIC_CPU_WRITE(mv_mpic_sc, MPIC_ISM, nb);
	else if (nb < ERR_IRQ)
		MPIC_WRITE(mv_mpic_sc, MPIC_ICE, nb);
	else if (nb < MSI_IRQ)
		mpic_mask_irq_err(nb);
}