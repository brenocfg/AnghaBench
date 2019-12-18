#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfe_dmamap_arg {int /*<<< orphan*/  nfe_busaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
nfe_dma_map_segs(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct nfe_dmamap_arg *ctx;

	if (error != 0)
		return;

	KASSERT(nseg == 1, ("too many DMA segments, %d should be 1", nseg));

	ctx = (struct nfe_dmamap_arg *)arg;
	ctx->nfe_busaddr = segs[0].ds_addr;
}