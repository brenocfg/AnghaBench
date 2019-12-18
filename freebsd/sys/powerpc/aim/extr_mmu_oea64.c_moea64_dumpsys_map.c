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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */

void
moea64_dumpsys_map(mmu_t mmu, vm_paddr_t pa, size_t sz, void **va)
{

	*va = (void *)(uintptr_t)pa;
}