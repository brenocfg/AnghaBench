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
struct bus_dmamap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/ * busdma_bufalloc_alloc_uncacheable ; 
 void* busdma_bufalloc_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * busdma_bufalloc_free_uncacheable ; 
 void* coherent_allocator ; 
 int /*<<< orphan*/  dmamap_ctor ; 
 int /*<<< orphan*/  dmamap_dtor ; 
 int /*<<< orphan*/  dmamap_zone ; 
 int /*<<< orphan*/  mips_dcache_max_linesize ; 
 void* standard_allocator ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
busdma_init(void *dummy)
{

	/* Create a cache of maps for bus_dmamap_create(). */
	dmamap_zone = uma_zcreate("dma maps", sizeof(struct bus_dmamap),
	    dmamap_ctor, dmamap_dtor, NULL, NULL, UMA_ALIGN_PTR, 0);

	/* Create a cache of buffers in standard (cacheable) memory. */
	standard_allocator = busdma_bufalloc_create("buffer",
	    mips_dcache_max_linesize,	/* minimum_alignment */
	    NULL,			/* uma_alloc func */
	    NULL,			/* uma_free func */
	    0);				/* uma_zcreate_flags */

	/*
	 * Create a cache of buffers in uncacheable memory, to implement the
	 * BUS_DMA_COHERENT flag.
	 */
	coherent_allocator = busdma_bufalloc_create("coherent",
	    mips_dcache_max_linesize,	/* minimum_alignment */
	    busdma_bufalloc_alloc_uncacheable,
	    busdma_bufalloc_free_uncacheable,
	    0);				/* uma_zcreate_flags */
}