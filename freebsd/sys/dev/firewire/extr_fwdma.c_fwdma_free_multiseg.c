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
struct fwdma_seg {int /*<<< orphan*/  v_addr; int /*<<< orphan*/  dma_map; } ;
struct fwdma_alloc_multi {int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  ssize; int /*<<< orphan*/  nseg; struct fwdma_seg* seg; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_FW ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fwdma_alloc_multi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwdma_free_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fwdma_free_multiseg(struct fwdma_alloc_multi *am)
{
	struct fwdma_seg *seg;

	for (seg = &am->seg[0]; am->nseg--; seg++) {
		fwdma_free_size(am->dma_tag, seg->dma_map,
			seg->v_addr, am->ssize);
	}
	bus_dma_tag_destroy(am->dma_tag);
	free(am, M_FW);
}