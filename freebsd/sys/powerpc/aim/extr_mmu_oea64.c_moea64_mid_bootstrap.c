#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct pvo_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_9__ {int /*<<< orphan*/  pmap_pvo; int /*<<< orphan*/  pm_active; struct TYPE_9__* pmap_phys; scalar_t__* pm_sr; } ;
struct TYPE_7__ {TYPE_1__* slb; } ;
struct TYPE_8__ {TYPE_2__ pc_aim; } ;
struct TYPE_6__ {scalar_t__ slbe; scalar_t__ slbv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FILL (int /*<<< orphan*/ *) ; 
 scalar_t__ EMPTY_SEGMENT ; 
 int KERNEL_VSIDBITS ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int NVSIDS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (uintptr_t) ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_4__*) ; 
 int PV_LOCK_COUNT ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int VSID_NBPW ; 
 scalar_t__ hw_direct_map ; 
 TYPE_4__* kernel_pmap ; 
 scalar_t__ moea64_bootstrap_alloc (int,int /*<<< orphan*/ ) ; 
 struct pvo_entry* moea64_bpvo_pool ; 
 scalar_t__ moea64_bpvo_pool_index ; 
 int moea64_bpvo_pool_size ; 
 scalar_t__ moea64_pteg_count ; 
 scalar_t__ moea64_pteg_mask ; 
 int /*<<< orphan*/  moea64_setup_direct_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_slb_mutex ; 
 int* moea64_vsid_bitmap ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* pcpup ; 
 int /*<<< orphan*/ * pv_lock ; 

void
moea64_mid_bootstrap(mmu_t mmup, vm_offset_t kernelstart, vm_offset_t kernelend)
{
	int		i;

	/*
	 * Set PTEG mask
	 */
	moea64_pteg_mask = moea64_pteg_count - 1;

	/*
	 * Initialize SLB table lock and page locks
	 */
	mtx_init(&moea64_slb_mutex, "SLB table", NULL, MTX_DEF);
	for (i = 0; i < PV_LOCK_COUNT; i++)
		mtx_init(&pv_lock[i], "page pv", NULL, MTX_DEF);

	/*
	 * Initialise the bootstrap pvo pool.
	 */
	moea64_bpvo_pool = (struct pvo_entry *)moea64_bootstrap_alloc(
		moea64_bpvo_pool_size*sizeof(struct pvo_entry), PAGE_SIZE);
	moea64_bpvo_pool_index = 0;

	/* Place at address usable through the direct map */
	if (hw_direct_map)
		moea64_bpvo_pool = (struct pvo_entry *)
		    PHYS_TO_DMAP((uintptr_t)moea64_bpvo_pool);

	/*
	 * Make sure kernel vsid is allocated as well as VSID 0.
	 */
	#ifndef __powerpc64__
	moea64_vsid_bitmap[(KERNEL_VSIDBITS & (NVSIDS - 1)) / VSID_NBPW]
		|= 1 << (KERNEL_VSIDBITS % VSID_NBPW);
	moea64_vsid_bitmap[0] |= 1;
	#endif

	/*
	 * Initialize the kernel pmap (which is statically allocated).
	 */
	#ifdef __powerpc64__
	for (i = 0; i < 64; i++) {
		pcpup->pc_aim.slb[i].slbv = 0;
		pcpup->pc_aim.slb[i].slbe = 0;
	}
	#else
	for (i = 0; i < 16; i++) 
		kernel_pmap->pm_sr[i] = EMPTY_SEGMENT + i;
	#endif

	kernel_pmap->pmap_phys = kernel_pmap;
	CPU_FILL(&kernel_pmap->pm_active);
	RB_INIT(&kernel_pmap->pmap_pvo);

	PMAP_LOCK_INIT(kernel_pmap);

	/*
	 * Now map in all the other buffers we allocated earlier
	 */

	moea64_setup_direct_map(mmup, kernelstart, kernelend);
}