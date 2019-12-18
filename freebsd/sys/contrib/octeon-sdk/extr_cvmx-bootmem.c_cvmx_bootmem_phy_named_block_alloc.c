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
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  ULL ;

/* Variables and functions */
 int CVMX_BOOTMEM_ALIGNMENT_SIZE ; 
 int /*<<< orphan*/  CVMX_BOOTMEM_DESC_GET_FIELD (int /*<<< orphan*/ ) ; 
 int CVMX_BOOTMEM_FLAG_NO_LOCKING ; 
 int /*<<< orphan*/  CVMX_BOOTMEM_NAMED_SET_FIELD (int,int,int) ; 
 int /*<<< orphan*/  CVMX_BOOTMEM_NAMED_SET_NAME (int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ __cvmx_bootmem_check_version (int) ; 
 int /*<<< orphan*/  __cvmx_bootmem_lock (int) ; 
 int /*<<< orphan*/  __cvmx_bootmem_unlock (int) ; 
 int base_addr ; 
 int cvmx_bootmem_phy_alloc (int,int,int,int,int) ; 
 int cvmx_bootmem_phy_named_block_find (char const*,int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  named_block_name_len ; 

int64_t cvmx_bootmem_phy_named_block_alloc(uint64_t size, uint64_t min_addr, uint64_t max_addr, uint64_t alignment, const char *name, uint32_t flags)
{
    int64_t addr_allocated;
    uint64_t named_block_desc_addr;

#ifdef DEBUG
    cvmx_dprintf("cvmx_bootmem_phy_named_block_alloc: size: 0x%llx, min: 0x%llx, max: 0x%llx, align: 0x%llx, name: %s\n",
                 (ULL)size,
                 (ULL)min_addr,
                 (ULL)max_addr,
                 (ULL)alignment,
                 name);
#endif

    if (__cvmx_bootmem_check_version(3))
        return(-1);

    /* Take lock here, as name lookup/block alloc/name add need to be atomic */

    __cvmx_bootmem_lock(flags);

    named_block_desc_addr = cvmx_bootmem_phy_named_block_find(name, flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);
    if (named_block_desc_addr)
    {
        __cvmx_bootmem_unlock(flags);
        return(-1);
    }

    /* Get pointer to first available named block descriptor */
    named_block_desc_addr = cvmx_bootmem_phy_named_block_find(NULL, flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);
    if (!named_block_desc_addr)
    {
        __cvmx_bootmem_unlock(flags);
        return(-1);
    }

    /* Round size up to mult of minimum alignment bytes
    ** We need the actual size allocated to allow for blocks to be coallesced
    ** when they are freed.  The alloc routine does the same rounding up
    ** on all allocations. */
    size = (size + (CVMX_BOOTMEM_ALIGNMENT_SIZE - 1)) & ~(CVMX_BOOTMEM_ALIGNMENT_SIZE - 1);

    addr_allocated = cvmx_bootmem_phy_alloc(size, min_addr, max_addr, alignment, flags | CVMX_BOOTMEM_FLAG_NO_LOCKING);
    if (addr_allocated >= 0)
    {
        CVMX_BOOTMEM_NAMED_SET_FIELD(named_block_desc_addr, base_addr, addr_allocated);
        CVMX_BOOTMEM_NAMED_SET_FIELD(named_block_desc_addr, size, size);
        CVMX_BOOTMEM_NAMED_SET_NAME(named_block_desc_addr, name, CVMX_BOOTMEM_DESC_GET_FIELD(named_block_name_len));
    }

    __cvmx_bootmem_unlock(flags);
    return(addr_allocated);
}