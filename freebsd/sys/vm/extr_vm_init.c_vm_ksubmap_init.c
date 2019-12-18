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
typedef  long vm_size_t ;
typedef  int vm_paddr_t ;
typedef  char* vm_offset_t ;
struct kva_md_info {char* clean_sva; char* clean_eva; char* buffer_sva; char* buffer_eva; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ ARG_MAX ; 
 long BKVASIZE ; 
 int /*<<< orphan*/  FALSE ; 
 long MAXPHYS ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 scalar_t__ PATH_MAX ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ bio_transient_maxcnt ; 
 int /*<<< orphan*/  btoc (scalar_t__) ; 
 int /*<<< orphan*/  buffer_arena ; 
 void* exec_map ; 
 int exec_map_entries ; 
 int exec_map_entry_size ; 
 scalar_t__ kern_vfs_bio_buffer_alloc (scalar_t__,long) ; 
 int /*<<< orphan*/  kernel_map ; 
 char* kmem_alloc_attr (long,int,int,int,int /*<<< orphan*/ ) ; 
 char* kmem_malloc (long,int) ; 
 void* kmem_suballoc (int /*<<< orphan*/ ,char**,char**,int,int /*<<< orphan*/ ) ; 
 char* kva_alloc (long) ; 
 long lmin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int maxpipekva ; 
 int mp_ncpus ; 
 scalar_t__ nbuf ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  physmem ; 
 void* pipe_map ; 
 int round_page (scalar_t__) ; 
 int /*<<< orphan*/  transient_arena ; 
 scalar_t__ vm_map_max (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_init (int /*<<< orphan*/ ,char*,char*,long,int,long,int /*<<< orphan*/ ) ; 

void
vm_ksubmap_init(struct kva_md_info *kmi)
{
	vm_offset_t firstaddr;
	caddr_t v;
	vm_size_t size = 0;
	long physmem_est;
	vm_offset_t minaddr;
	vm_offset_t maxaddr;

	/*
	 * Allocate space for system data structures.
	 * The first available kernel virtual address is in "v".
	 * As pages of kernel virtual memory are allocated, "v" is incremented.
	 * As pages of memory are allocated and cleared,
	 * "firstaddr" is incremented.
	 */

	/*
	 * Make two passes.  The first pass calculates how much memory is
	 * needed and allocates it.  The second pass assigns virtual
	 * addresses to the various data structures.
	 */
	firstaddr = 0;
again:
	v = (caddr_t)firstaddr;

	/*
	 * Discount the physical memory larger than the size of kernel_map
	 * to avoid eating up all of KVA space.
	 */
	physmem_est = lmin(physmem, btoc(vm_map_max(kernel_map) -
	    vm_map_min(kernel_map)));

	v = kern_vfs_bio_buffer_alloc(v, physmem_est);

	/*
	 * End of first pass, size has been calculated so allocate memory
	 */
	if (firstaddr == 0) {
		size = (vm_size_t)v;
#ifdef VM_FREELIST_DMA32
		/*
		 * Try to protect 32-bit DMAable memory from the largest
		 * early alloc of wired mem.
		 */
		firstaddr = kmem_alloc_attr(size, M_ZERO | M_NOWAIT,
		    (vm_paddr_t)1 << 32, ~(vm_paddr_t)0, VM_MEMATTR_DEFAULT);
		if (firstaddr == 0)
#endif
			firstaddr = kmem_malloc(size, M_ZERO | M_WAITOK);
		if (firstaddr == 0)
			panic("startup: no room for tables");
		goto again;
	}

	/*
	 * End of second pass, addresses have been assigned
	 */
	if ((vm_size_t)((char *)v - firstaddr) != size)
		panic("startup: table size inconsistency");

	/*
	 * Allocate the clean map to hold all of I/O virtual memory.
	 */
	size = (long)nbuf * BKVASIZE + (long)bio_transient_maxcnt * MAXPHYS;
	kmi->clean_sva = firstaddr = kva_alloc(size);
	kmi->clean_eva = firstaddr + size;

	/*
	 * Allocate the buffer arena.
	 *
	 * Enable the quantum cache if we have more than 4 cpus.  This
	 * avoids lock contention at the expense of some fragmentation.
	 */
	size = (long)nbuf * BKVASIZE;
	kmi->buffer_sva = firstaddr;
	kmi->buffer_eva = kmi->buffer_sva + size;
	vmem_init(buffer_arena, "buffer arena", kmi->buffer_sva, size,
	    PAGE_SIZE, (mp_ncpus > 4) ? BKVASIZE * 8 : 0, 0);
	firstaddr += size;

	/*
	 * And optionally transient bio space.
	 */
	if (bio_transient_maxcnt != 0) {
		size = (long)bio_transient_maxcnt * MAXPHYS;
		vmem_init(transient_arena, "transient arena",
		    firstaddr, size, PAGE_SIZE, 0, 0);
		firstaddr += size;
	}
	if (firstaddr != kmi->clean_eva)
		panic("Clean map calculation incorrect");

	/*
	 * Allocate the pageable submaps.  We may cache an exec map entry per
	 * CPU, so we therefore need to reserve space for at least ncpu+1
	 * entries to avoid deadlock.  The exec map is also used by some image
	 * activators, so we leave a fixed number of pages for their use.
	 */
#ifdef __LP64__
	exec_map_entries = 8 * mp_ncpus;
#else
	exec_map_entries = 2 * mp_ncpus + 4;
#endif
	exec_map_entry_size = round_page(PATH_MAX + ARG_MAX);
	exec_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr,
	    exec_map_entries * exec_map_entry_size + 64 * PAGE_SIZE, FALSE);
	pipe_map = kmem_suballoc(kernel_map, &minaddr, &maxaddr, maxpipekva,
	    FALSE);
}