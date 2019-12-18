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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ CVMX_BOOTMEM_FLAG_NO_LOCKING ; 
 scalar_t__ CVMX_BOOTMEM_NAMED_GET_FIELD (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_addr ; 
 scalar_t__ cvmx_bootmem_phy_named_block_alloc (scalar_t__,scalar_t__,scalar_t__,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_bootmem_phy_named_block_find (char*,int /*<<< orphan*/ ) ; 
 void* cvmx_phys_to_ptr (scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 

void *cvmx_bootmem_alloc_named_range_once(uint64_t size, uint64_t min_addr,
					  uint64_t max_addr, uint64_t align,
					  char *name,
					  void (*init) (void *))
{
	int64_t addr;
	void *ptr;
	uint64_t named_block_desc_addr;

	named_block_desc_addr = (uint64_t)
		cvmx_bootmem_phy_named_block_find(name,
						  (uint32_t)CVMX_BOOTMEM_FLAG_NO_LOCKING);

	if (named_block_desc_addr) {
		addr = CVMX_BOOTMEM_NAMED_GET_FIELD(named_block_desc_addr,
						    base_addr);
		return cvmx_phys_to_ptr(addr);
	}

	addr = cvmx_bootmem_phy_named_block_alloc(size, min_addr, max_addr,
						  align, name,
						  (uint32_t)CVMX_BOOTMEM_FLAG_NO_LOCKING);

	if (addr < 0)
		return NULL;
	ptr = cvmx_phys_to_ptr(addr);

	if (init)
		init(ptr);
	else
		memset(ptr, 0, size);

	return ptr;
}