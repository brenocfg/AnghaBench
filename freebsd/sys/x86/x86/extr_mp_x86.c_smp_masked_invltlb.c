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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_INVLTLB ; 
 int /*<<< orphan*/  ipi_global ; 
 scalar_t__ smp_started ; 
 int /*<<< orphan*/  smp_targeted_tlb_shootdown (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
smp_masked_invltlb(cpuset_t mask, pmap_t pmap)
{

	if (smp_started) {
		smp_targeted_tlb_shootdown(mask, IPI_INVLTLB, pmap, 0, 0);
#ifdef COUNT_XINVLTLB_HITS
		ipi_global++;
#endif
	}
}