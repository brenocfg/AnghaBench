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
struct tool_mw {scalar_t__ size; scalar_t__ mm_base; scalar_t__ dma_map; scalar_t__ dma_tag; scalar_t__ dma_base; scalar_t__ virt_addr; } ;
struct tool_ctx {int /*<<< orphan*/  dev; TYPE_1__* peers; } ;
struct TYPE_2__ {struct tool_mw* inmws; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamem_free (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ntb_mw_clear_trans (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tool_free_mw(struct tool_ctx *tc, int pidx, int widx)
{
	struct tool_mw *inmw = &tc->peers[pidx].inmws[widx];

	if (inmw->dma_base)
		ntb_mw_clear_trans(tc->dev, widx);

	if (inmw->virt_addr && inmw->dma_tag) {
		bus_dmamap_unload(inmw->dma_tag, inmw->dma_map);
		bus_dmamem_free(inmw->dma_tag, inmw->virt_addr, inmw->dma_map);
		bus_dma_tag_destroy(inmw->dma_tag);
	}

	inmw->virt_addr = 0;
	inmw->dma_base = 0;
	inmw->dma_tag = 0;
	inmw->dma_map = 0;
	inmw->mm_base = 0;
	inmw->size = 0;
}