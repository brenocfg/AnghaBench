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
struct ntb_transport_mw {int /*<<< orphan*/ * virt_addr; scalar_t__ buff_size; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; } ;
struct ntb_transport_ctx {int /*<<< orphan*/  dev; struct ntb_transport_mw* mw_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_mw_clear_trans (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ntb_free_mw(struct ntb_transport_ctx *nt, int num_mw)
{
	struct ntb_transport_mw *mw = &nt->mw_vec[num_mw];

	if (mw->virt_addr == NULL)
		return;

	ntb_mw_clear_trans(nt->dev, num_mw);
	bus_dmamap_unload(mw->dma_tag, mw->dma_map);
	bus_dmamem_free(mw->dma_tag, mw->virt_addr, mw->dma_map);
	bus_dma_tag_destroy(mw->dma_tag);
	mw->buff_size = 0;
	mw->virt_addr = NULL;
}