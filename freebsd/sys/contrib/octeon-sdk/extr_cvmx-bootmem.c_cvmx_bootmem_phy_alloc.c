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
 int ALIGN_ADDR_UP (int /*<<< orphan*/ ,int) ; 
 int CVMX_BOOTMEM_ALIGNMENT_SIZE ; 
 int CVMX_BOOTMEM_DESC_GET_FIELD (int) ; 
 int /*<<< orphan*/  CVMX_BOOTMEM_DESC_SET_FIELD (int,int) ; 
 int CVMX_BOOTMEM_FLAG_END_ALLOC ; 
 int /*<<< orphan*/  MAX (int,int) ; 
 int MIN (int,int) ; 
 scalar_t__ __cvmx_bootmem_check_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_bootmem_lock (int) ; 
 int /*<<< orphan*/  __cvmx_bootmem_unlock (int) ; 
 int cvmx_bootmem_phy_get_next (int) ; 
 int cvmx_bootmem_phy_get_size (int) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_next (int,int) ; 
 int /*<<< orphan*/  cvmx_bootmem_phy_set_size (int,int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

int64_t cvmx_bootmem_phy_alloc(uint64_t req_size, uint64_t address_min, uint64_t address_max, uint64_t alignment, uint32_t flags)
{

    uint64_t head_addr;
    uint64_t ent_addr;
    uint64_t prev_addr = 0;  /* points to previous list entry, NULL current entry is head of list */
    uint64_t new_ent_addr = 0;
    uint64_t desired_min_addr;
    uint64_t alignment_mask = ~(alignment - 1);

#ifdef DEBUG
    cvmx_dprintf("cvmx_bootmem_phy_alloc: req_size: 0x%llx, min_addr: 0x%llx, max_addr: 0x%llx, align: 0x%llx\n",
           (ULL)req_size, (ULL)address_min, (ULL)address_max, (ULL)alignment);
#endif

    if (__cvmx_bootmem_check_version(0))
        goto error_out;

    /* Do a variety of checks to validate the arguments.  The allocator code will later assume
    ** that these checks have been made.  We validate that the requested constraints are not
    ** self-contradictory before we look through the list of available memory
    */

    /* 0 is not a valid req_size for this allocator */
    if (!req_size)
        goto error_out;

    /* Round req_size up to mult of minimum alignment bytes */
    req_size = (req_size + (CVMX_BOOTMEM_ALIGNMENT_SIZE - 1)) & ~(CVMX_BOOTMEM_ALIGNMENT_SIZE - 1);

    
    /* Enforce minimum alignment (this also keeps the minimum free block
    ** req_size the same as the alignment req_size */
    if (alignment < CVMX_BOOTMEM_ALIGNMENT_SIZE)
    {
        alignment = CVMX_BOOTMEM_ALIGNMENT_SIZE;
    }
    alignment_mask = ~(alignment - 1);

    /* Adjust address minimum based on requested alignment (round up to meet alignment).  Do this here so we can
    ** reject impossible requests up front. (NOP for address_min == 0) */
    if (alignment)
        address_min = (address_min + (alignment - 1)) & ~(alignment - 1);

    /* Convert !0 address_min and 0 address_max to special case of range that specifies an exact
     ** memory block to allocate.  Do this before other checks and adjustments so that this tranformation will be validated */
    if (address_min && !address_max)
        address_max = address_min + req_size;
    else if (!address_min && !address_max)
        address_max = ~0ull;   /* If no limits given, use max limits */

    /* Reject inconsistent args.  We have adjusted these, so this may fail due to our internal changes
    ** even if this check would pass for the values the user supplied. */
    if (req_size > address_max - address_min)
        goto error_out;

    /* Walk through the list entries - first fit found is returned */

    __cvmx_bootmem_lock(flags);
    head_addr = CVMX_BOOTMEM_DESC_GET_FIELD(head_addr);
    ent_addr = head_addr;
    while (ent_addr)
    {
        uint64_t usable_base, usable_max;
        uint64_t ent_size = cvmx_bootmem_phy_get_size(ent_addr);

        if (cvmx_bootmem_phy_get_next(ent_addr) && ent_addr > cvmx_bootmem_phy_get_next(ent_addr))
        {
            cvmx_dprintf("Internal bootmem_alloc() error: ent: 0x%llx, next: 0x%llx\n",
                   (ULL)ent_addr, (ULL)cvmx_bootmem_phy_get_next(ent_addr));
            goto error_out;
        }

        /* Determine if this is an entry that can satisify the request */
        /* Check to make sure entry is large enough to satisfy request */
        usable_base = ALIGN_ADDR_UP(MAX(address_min, ent_addr), alignment_mask);
        usable_max = MIN(address_max, ent_addr + ent_size);
        /* We should be able to allocate block at address usable_base */

        desired_min_addr = usable_base;

        /* Determine if request can be satisfied from the current entry */
        if ((((ent_addr + ent_size) > usable_base && ent_addr < address_max))
            && req_size <= usable_max - usable_base)
        {
            /* We have found an entry that has room to satisfy the request, so allocate it from this entry */

            /* If end CVMX_BOOTMEM_FLAG_END_ALLOC set, then allocate from the end of this block
            ** rather than the beginning */
            if (flags & CVMX_BOOTMEM_FLAG_END_ALLOC)
            {
                desired_min_addr = usable_max - req_size;
                /* Align desired address down to required alignment */
                desired_min_addr &= alignment_mask;
            }

            /* Match at start of entry */
            if (desired_min_addr == ent_addr)
            {
                if (req_size < ent_size)
                {
                    /* big enough to create a new block from top portion of block */
                    new_ent_addr = ent_addr + req_size;
                    cvmx_bootmem_phy_set_next(new_ent_addr, cvmx_bootmem_phy_get_next(ent_addr));
                    cvmx_bootmem_phy_set_size(new_ent_addr, ent_size - req_size);

                    /* Adjust next pointer as following code uses this */
                    cvmx_bootmem_phy_set_next(ent_addr, new_ent_addr);
                }

                /* adjust prev ptr or head to remove this entry from list */
                if (prev_addr)
                {
                    cvmx_bootmem_phy_set_next(prev_addr, cvmx_bootmem_phy_get_next(ent_addr));
                }
                else
                {
                    /* head of list being returned, so update head ptr */
                    CVMX_BOOTMEM_DESC_SET_FIELD(head_addr, cvmx_bootmem_phy_get_next(ent_addr));
                }
                __cvmx_bootmem_unlock(flags);
                return(desired_min_addr);
            }


            /* block returned doesn't start at beginning of entry, so we know
            ** that we will be splitting a block off the front of this one.  Create a new block
            ** from the beginning, add to list, and go to top of loop again.
            **
            ** create new block from high portion of block, so that top block
            ** starts at desired addr
            **/
            new_ent_addr = desired_min_addr;
            cvmx_bootmem_phy_set_next(new_ent_addr, cvmx_bootmem_phy_get_next(ent_addr));
            cvmx_bootmem_phy_set_size(new_ent_addr, cvmx_bootmem_phy_get_size(ent_addr) - (desired_min_addr - ent_addr));
            cvmx_bootmem_phy_set_size(ent_addr, desired_min_addr - ent_addr);
            cvmx_bootmem_phy_set_next(ent_addr, new_ent_addr);
            /* Loop again to handle actual alloc from new block */
        }

        prev_addr = ent_addr;
        ent_addr = cvmx_bootmem_phy_get_next(ent_addr);
    }
error_out:
    /* We didn't find anything, so return error */
    __cvmx_bootmem_unlock(flags);
    return(-1);
}