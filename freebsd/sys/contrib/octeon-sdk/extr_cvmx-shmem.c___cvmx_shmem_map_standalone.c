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
struct cvmx_shmem_dscptr {void* vaddr; int /*<<< orphan*/  size; int /*<<< orphan*/  paddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST64 (void*) ; 
 int TLB_DIRTY ; 
 int TLB_GLOBAL ; 
 int TLB_VALID ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int cvmx_tlb_allocate_runtime_entry () ; 
 int /*<<< orphan*/  cvmx_tlb_write_runtime_entry (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void *__cvmx_shmem_map_standalone(struct cvmx_shmem_dscptr *dscptr, int pflag)
{
    int free_index;

    /* Find a free tlb entry */
    free_index = cvmx_tlb_allocate_runtime_entry();

    if (free_index < 0 )
    {
        cvmx_dprintf("cvmx-shmem: shmem_map failed, out TLB entries \n");
        return NULL;
    }

#ifdef DEBUG
    cvmx_dprintf("cmvx-shmem-dbg:"
         "shmem_map TLB %d: vaddr %p paddr %lx, size %x \n",
         free_index, dscptr->vaddr, dscptr->paddr, dscptr->size );
#endif

    cvmx_tlb_write_runtime_entry(free_index, CAST64(dscptr->vaddr),
            dscptr->paddr, dscptr->size,
            TLB_DIRTY | TLB_VALID | TLB_GLOBAL);

    return dscptr -> vaddr;
}