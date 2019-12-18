#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned long csr; } ;
struct TYPE_9__ {unsigned long csr; } ;
struct TYPE_8__ {unsigned long csr; } ;
struct TYPE_7__ {unsigned long csr; } ;
struct TYPE_11__ {TYPE_4__ dim3; TYPE_3__ dim2; TYPE_2__ dim1; TYPE_1__ dim0; } ;
typedef  TYPE_5__ tsunami_cchip ;

/* Variables and functions */
 TYPE_5__* TSUNAMI_cchip ; 
 int boot_cpuid ; 
 unsigned long* cpu_irq_affinity ; 
 int /*<<< orphan*/  cpu_possible (int) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void
tsunami_update_irq_hw(unsigned long mask)
{
	register tsunami_cchip *cchip = TSUNAMI_cchip;
	unsigned long isa_enable = 1UL << 55;
	register int bcpu = boot_cpuid;

#ifdef CONFIG_SMP
	volatile unsigned long *dim0, *dim1, *dim2, *dim3;
	unsigned long mask0, mask1, mask2, mask3, dummy;

	mask &= ~isa_enable;
	mask0 = mask & cpu_irq_affinity[0];
	mask1 = mask & cpu_irq_affinity[1];
	mask2 = mask & cpu_irq_affinity[2];
	mask3 = mask & cpu_irq_affinity[3];

	if (bcpu == 0) mask0 |= isa_enable;
	else if (bcpu == 1) mask1 |= isa_enable;
	else if (bcpu == 2) mask2 |= isa_enable;
	else mask3 |= isa_enable;

	dim0 = &cchip->dim0.csr;
	dim1 = &cchip->dim1.csr;
	dim2 = &cchip->dim2.csr;
	dim3 = &cchip->dim3.csr;
	if (!cpu_possible(0)) dim0 = &dummy;
	if (!cpu_possible(1)) dim1 = &dummy;
	if (!cpu_possible(2)) dim2 = &dummy;
	if (!cpu_possible(3)) dim3 = &dummy;

	*dim0 = mask0;
	*dim1 = mask1;
	*dim2 = mask2;
	*dim3 = mask3;
	mb();
	*dim0;
	*dim1;
	*dim2;
	*dim3;
#else
	volatile unsigned long *dimB;
	if (bcpu == 0) dimB = &cchip->dim0.csr;
	else if (bcpu == 1) dimB = &cchip->dim1.csr;
	else if (bcpu == 2) dimB = &cchip->dim2.csr;
	else dimB = &cchip->dim3.csr;

	*dimB = mask | isa_enable;
	mb();
	*dimB;
#endif
}