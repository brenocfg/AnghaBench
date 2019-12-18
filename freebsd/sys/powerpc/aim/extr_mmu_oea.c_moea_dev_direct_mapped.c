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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  mmu_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 scalar_t__ moea_bat_mapped (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

boolean_t
moea_dev_direct_mapped(mmu_t mmu, vm_paddr_t pa, vm_size_t size)
{
	int i;

	/*
	 * This currently does not work for entries that
	 * overlap 256M BAT segments.
	 */

	for(i = 0; i < 16; i++)
		if (moea_bat_mapped(i, pa, size) == 0)
			return (0);

	return (EFAULT);
}