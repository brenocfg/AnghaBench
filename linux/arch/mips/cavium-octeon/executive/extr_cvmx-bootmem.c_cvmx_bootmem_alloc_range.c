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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ cvmx_bootmem_phy_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cvmx_phys_to_ptr (scalar_t__) ; 

__attribute__((used)) static void *cvmx_bootmem_alloc_range(uint64_t size, uint64_t alignment,
				      uint64_t min_addr, uint64_t max_addr)
{
	int64_t address;
	address =
	    cvmx_bootmem_phy_alloc(size, min_addr, max_addr, alignment, 0);

	if (address > 0)
		return cvmx_phys_to_ptr(address);
	else
		return NULL;
}