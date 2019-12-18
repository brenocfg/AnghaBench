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
struct ntb_transport_mw {size_t buff_size; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  addr_limit; int /*<<< orphan*/  xlat_align; int /*<<< orphan*/  xlat_align_size; } ;
struct ntb_transport_ctx {int /*<<< orphan*/  dev; struct ntb_transport_mw* mw_vec; } ;
struct ntb_load_cb_args {int /*<<< orphan*/  addr; scalar_t__ error; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,struct ntb_load_cb_args*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_free_mw (struct ntb_transport_ctx*,int) ; 
 int /*<<< orphan*/  ntb_load_cb ; 
 int /*<<< orphan*/  ntb_printf (int /*<<< orphan*/ ,char*,size_t) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ntb_set_mw(struct ntb_transport_ctx *nt, int num_mw, size_t size)
{
	struct ntb_transport_mw *mw = &nt->mw_vec[num_mw];
	struct ntb_load_cb_args cba;
	size_t buff_size;

	if (size == 0)
		return (EINVAL);

	buff_size = roundup(size, mw->xlat_align_size);

	/* No need to re-setup */
	if (mw->buff_size == buff_size)
		return (0);

	if (mw->buff_size != 0)
		ntb_free_mw(nt, num_mw);

	/* Alloc memory for receiving data.  Must be aligned */
	mw->buff_size = buff_size;

	if (bus_dma_tag_create(bus_get_dma_tag(nt->dev), mw->xlat_align, 0,
	    mw->addr_limit, BUS_SPACE_MAXADDR,
	    NULL, NULL, mw->buff_size, 1, mw->buff_size,
	    0, NULL, NULL, &mw->dma_tag)) {
		ntb_printf(0, "Unable to create MW tag of size %zu\n",
		    mw->buff_size);
		mw->buff_size = 0;
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(mw->dma_tag, (void **)&mw->virt_addr,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO, &mw->dma_map)) {
		bus_dma_tag_destroy(mw->dma_tag);
		ntb_printf(0, "Unable to allocate MW buffer of size %zu\n",
		    mw->buff_size);
		mw->buff_size = 0;
		return (ENOMEM);
	}
	if (bus_dmamap_load(mw->dma_tag, mw->dma_map, mw->virt_addr,
	    mw->buff_size, ntb_load_cb, &cba, BUS_DMA_NOWAIT) || cba.error) {
		bus_dmamem_free(mw->dma_tag, mw->virt_addr, mw->dma_map);
		bus_dma_tag_destroy(mw->dma_tag);
		ntb_printf(0, "Unable to load MW buffer of size %zu\n",
		    mw->buff_size);
		mw->buff_size = 0;
		return (ENOMEM);
	}
	mw->dma_addr = cba.addr;

	return (0);
}