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
struct cpt_vf {int /*<<< orphan*/ * affinity_mask; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void cptvf_free_irq_affinity(struct cpt_vf *cptvf, int vec)
{
	irq_set_affinity_hint(pci_irq_vector(cptvf->pdev, vec), NULL);
	free_cpumask_var(cptvf->affinity_mask[vec]);
}