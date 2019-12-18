#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tool_mw {size_t phys_size; scalar_t__ dma_map; scalar_t__ dma_tag; scalar_t__ dma_base; scalar_t__ virt_addr; void* size; int /*<<< orphan*/  addr_limit; int /*<<< orphan*/  xlat_align; int /*<<< orphan*/  xlat_align_size; } ;
struct tool_ctx {int /*<<< orphan*/  dev; TYPE_1__* peers; } ;
struct ntb_tool_load_cb_args {scalar_t__ addr; scalar_t__ error; } ;
struct TYPE_2__ {struct tool_mw* inmws; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int ENOMEM ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 scalar_t__ bus_dmamap_load (scalar_t__,scalar_t__,scalar_t__,void*,int /*<<< orphan*/ ,struct ntb_tool_load_cb_args*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,scalar_t__) ; 
 scalar_t__ bus_dmamem_alloc (scalar_t__,void**,int,scalar_t__*) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,size_t,size_t,...) ; 
 int ntb_mw_set_trans (int /*<<< orphan*/ ,unsigned int,scalar_t__,void*) ; 
 int /*<<< orphan*/  ntb_tool_load_cb ; 
 void* roundup (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tool_setup_mw(struct tool_ctx *tc, unsigned int pidx, unsigned int widx,
    size_t req_size)
{
	struct tool_mw *inmw = &tc->peers[pidx].inmws[widx];
	struct ntb_tool_load_cb_args cba;
	int rc;

	if (req_size == 0)
		inmw->size = roundup(inmw->phys_size, inmw->xlat_align_size);
	else
		inmw->size = roundup(req_size, inmw->xlat_align_size);

	device_printf(tc->dev, "mw_size %zi req_size %zi buff %zi\n",
	    inmw->phys_size, req_size, inmw->size);

	if (bus_dma_tag_create(bus_get_dma_tag(tc->dev), inmw->xlat_align, 0,
	    inmw->addr_limit, BUS_SPACE_MAXADDR, NULL, NULL, inmw->size, 1,
	    inmw->size, 0, NULL, NULL, &inmw->dma_tag)) {
		device_printf(tc->dev, "Unable to create MW tag of size "
		    "%zu/%zu\n", inmw->phys_size, inmw->size);
		rc = ENOMEM;
		goto err_free_dma_var;
	}

	if (bus_dmamem_alloc(inmw->dma_tag, (void **)&inmw->virt_addr,
	    BUS_DMA_WAITOK | BUS_DMA_ZERO, &inmw->dma_map)) {
		device_printf(tc->dev, "Unable to allocate MW buffer of size "
		    "%zu/%zu\n", inmw->phys_size, inmw->size);
		rc = ENOMEM;
		goto err_free_tag_rem;
	}

	if (bus_dmamap_load(inmw->dma_tag, inmw->dma_map, inmw->virt_addr,
	    inmw->size, ntb_tool_load_cb, &cba, BUS_DMA_NOWAIT) || cba.error) {
		device_printf(tc->dev, "Unable to load MW buffer of size "
		    "%zu/%zu\n", inmw->phys_size, inmw->size);
		rc = ENOMEM;
		goto err_free_dma;
	}
	inmw->dma_base = cba.addr;

	rc = ntb_mw_set_trans(tc->dev, widx, inmw->dma_base, inmw->size);
	if (rc)
		goto err_free_mw;

	return (0);

err_free_mw:
	bus_dmamap_unload(inmw->dma_tag, inmw->dma_map);

err_free_dma:
	bus_dmamem_free(inmw->dma_tag, inmw->virt_addr, inmw->dma_map);

err_free_tag_rem:
	bus_dma_tag_destroy(inmw->dma_tag);

err_free_dma_var:
	inmw->size = 0;
	inmw->virt_addr = 0;
	inmw->dma_base = 0;
	inmw->dma_tag = 0;
	inmw->dma_map = 0;

	return (rc);
}