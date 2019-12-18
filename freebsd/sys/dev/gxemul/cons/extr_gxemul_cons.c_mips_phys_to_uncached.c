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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIPS_PHYS_TO_DIRECT_UNCACHED (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline vm_offset_t
mips_phys_to_uncached(vm_paddr_t phys)            
{

	return (MIPS_PHYS_TO_DIRECT_UNCACHED(phys));
}