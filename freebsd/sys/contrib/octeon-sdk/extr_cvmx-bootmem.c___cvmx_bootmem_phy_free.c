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
typedef  int /*<<< orphan*/  ULL ;

/* Variables and functions */
 scalar_t__ CVMX_BOOTMEM_DESC_GET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_BOOTMEM_DESC_SET_FIELD (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ __cvmx_bootmem_check_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_bootmem_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_bootmem_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_bootmem_phy_get_next (scalar_t__) ; 
 scalar_t__ cvmx_bootmem_phy_get_size (scalar_t__) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_next (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_size (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head_addr ; 

int __cvmx_bootmem_phy_free(uint64_t phy_addr, uint64_t size, uint32_t flags)
{
    uint64_t cur_addr;
    uint64_t prev_addr = 0;  /* zero is invalid */
    int retval = 0;

#ifdef DEBUG
    cvmx_dprintf("__cvmx_bootmem_phy_free addr: 0x%llx, size: 0x%llx\n", (ULL)phy_addr, (ULL)size);
#endif
    if (__cvmx_bootmem_check_version(0))
        return(0);

    /* 0 is not a valid size for this allocator */
    if (!size)
        return(0);


    __cvmx_bootmem_lock(flags);
    cur_addr = CVMX_BOOTMEM_DESC_GET_FIELD(head_addr);
    if (cur_addr == 0 || phy_addr < cur_addr)
    {
        /* add at front of list - special case with changing head ptr */
        if (cur_addr && phy_addr + size > cur_addr)
            goto bootmem_free_done; /* error, overlapping section */
        else if (phy_addr + size == cur_addr)
        {
            /* Add to front of existing first block */
            cvmx_bootmem_phy_set_next(phy_addr, cvmx_bootmem_phy_get_next(cur_addr));
            cvmx_bootmem_phy_set_size(phy_addr, cvmx_bootmem_phy_get_size(cur_addr) + size);
            CVMX_BOOTMEM_DESC_SET_FIELD(head_addr, phy_addr);

        }
        else
        {
            /* New block before first block */
            cvmx_bootmem_phy_set_next(phy_addr, cur_addr);  /* OK if cur_addr is 0 */
            cvmx_bootmem_phy_set_size(phy_addr, size);
            CVMX_BOOTMEM_DESC_SET_FIELD(head_addr, phy_addr);
        }
        retval = 1;
        goto bootmem_free_done;
    }

    /* Find place in list to add block */
    while (cur_addr && phy_addr > cur_addr)
    {
        prev_addr = cur_addr;
        cur_addr = cvmx_bootmem_phy_get_next(cur_addr);
    }

    if (!cur_addr)
    {
        /* We have reached the end of the list, add on to end, checking
        ** to see if we need to combine with last block
        **/
        if (prev_addr +  cvmx_bootmem_phy_get_size(prev_addr) == phy_addr)
        {
            cvmx_bootmem_phy_set_size(prev_addr, cvmx_bootmem_phy_get_size(prev_addr) + size);
        }
        else
        {
            cvmx_bootmem_phy_set_next(prev_addr, phy_addr);
            cvmx_bootmem_phy_set_size(phy_addr, size);
            cvmx_bootmem_phy_set_next(phy_addr, 0);
        }
        retval = 1;
        goto bootmem_free_done;
    }
    else
    {
        /* insert between prev and cur nodes, checking for merge with either/both */

        if (prev_addr +  cvmx_bootmem_phy_get_size(prev_addr) == phy_addr)
        {
            /* Merge with previous */
            cvmx_bootmem_phy_set_size(prev_addr, cvmx_bootmem_phy_get_size(prev_addr) + size);
            if (phy_addr + size == cur_addr)
            {
                /* Also merge with current */
                cvmx_bootmem_phy_set_size(prev_addr, cvmx_bootmem_phy_get_size(cur_addr) + cvmx_bootmem_phy_get_size(prev_addr));
                cvmx_bootmem_phy_set_next(prev_addr, cvmx_bootmem_phy_get_next(cur_addr));
            }
            retval = 1;
            goto bootmem_free_done;
        }
        else if (phy_addr + size == cur_addr)
        {
            /* Merge with current */
            cvmx_bootmem_phy_set_size(phy_addr, cvmx_bootmem_phy_get_size(cur_addr) + size);
            cvmx_bootmem_phy_set_next(phy_addr, cvmx_bootmem_phy_get_next(cur_addr));
            cvmx_bootmem_phy_set_next(prev_addr, phy_addr);
            retval = 1;
            goto bootmem_free_done;
        }

        /* It is a standalone block, add in between prev and cur */
        cvmx_bootmem_phy_set_size(phy_addr, size);
        cvmx_bootmem_phy_set_next(phy_addr, cur_addr);
        cvmx_bootmem_phy_set_next(prev_addr, phy_addr);


    }
    retval = 1;

bootmem_free_done:
    __cvmx_bootmem_unlock(flags);
    return(retval);

}