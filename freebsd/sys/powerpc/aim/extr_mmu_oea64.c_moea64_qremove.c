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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  moea64_kremove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
moea64_qremove(mmu_t mmu, vm_offset_t va, int count)
{
	while (count-- > 0) {
		moea64_kremove(mmu, va);
		va += PAGE_SIZE;
	}
}