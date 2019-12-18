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
struct cvmx_shmem_dscptr {int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 int /*<<< orphan*/  cvmx_tlb_free_runtime_entry (int) ; 
 int cvmx_tlb_lookup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
__cvmx_shmem_unmap_standalone(struct cvmx_shmem_dscptr *dscptr)
{
    int index;

    index = cvmx_tlb_lookup(CAST64(dscptr->vaddr));

#ifdef DEBUG
    cvmx_dprintf("cmvx-shmem-dbg:"
             "shmem_unmap TLB %d \n", index);
#endif
    cvmx_tlb_free_runtime_entry(index);
}