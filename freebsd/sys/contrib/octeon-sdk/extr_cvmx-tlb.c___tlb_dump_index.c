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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_ENTRY_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  CVMX_MF_ENTRY_LO_0 (int) ; 
 int /*<<< orphan*/  CVMX_MF_ENTRY_LO_1 (int) ; 
 int /*<<< orphan*/  CVMX_MF_PAGEMASK (int) ; 
 int PAGE_MASK ; 
 scalar_t__ __tlb_entry_is_free (scalar_t__) ; 
 int /*<<< orphan*/  __tlb_read_index (scalar_t__) ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,...) ; 

__attribute__((used)) static inline void __tlb_dump_index(uint32_t tlbi)
{
    if (tlbi < (uint32_t)cvmx_core_get_tlb_entries()) {

        if (__tlb_entry_is_free(tlbi)) {
#ifdef DEBUG
            cvmx_dprintf("Index: %3d Free \n", tlbi);
#endif
        } else {
            uint64_t lo0, lo1, pgmask;
            uint32_t hi;
#ifdef DEBUG
            uint32_t c0, c1;
            int width = 13;
#endif

            __tlb_read_index(tlbi);

            CVMX_MF_ENTRY_HIGH(hi);
            CVMX_MF_ENTRY_LO_0(lo0);
            CVMX_MF_ENTRY_LO_1(lo1);
            CVMX_MF_PAGEMASK(pgmask);

#ifdef DEBUG
            c0 = ( lo0 >> 3 ) & 7;
            c1 = ( lo1 >> 3 ) & 7;

            cvmx_dprintf("va=%0*lx asid=%02x\n",
                               width, (hi & ~0x1fffUL), hi & 0xff);

            cvmx_dprintf("\t[pa=%0*lx c=%d d=%d v=%d g=%d] ",
                               width,
                               (lo0 << 6) & PAGE_MASK, c0,
                               (lo0 & 4) ? 1 : 0,
                               (lo0 & 2) ? 1 : 0,
                               (lo0 & 1) ? 1 : 0);
            cvmx_dprintf("[pa=%0*lx c=%d d=%d v=%d g=%d]\n",
                               width,
                               (lo1 << 6) & PAGE_MASK, c1,
                               (lo1 & 4) ? 1 : 0,
                               (lo1 & 2) ? 1 : 0,
                               (lo1 & 1) ? 1 : 0);

#endif
        }
    }
}