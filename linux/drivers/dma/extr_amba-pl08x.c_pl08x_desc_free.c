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
struct TYPE_3__ {int /*<<< orphan*/  chan; } ;
struct virt_dma_desc {TYPE_1__ tx; } ;
struct pl08x_txd {int /*<<< orphan*/  done; } ;
struct pl08x_dma_chan {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_descriptor_unmap (TYPE_1__*) ; 
 int /*<<< orphan*/  pl08x_free_txd (int /*<<< orphan*/ ,struct pl08x_txd*) ; 
 int /*<<< orphan*/  pl08x_release_mux (struct pl08x_dma_chan*) ; 
 struct pl08x_dma_chan* to_pl08x_chan (int /*<<< orphan*/ ) ; 
 struct pl08x_txd* to_pl08x_txd (TYPE_1__*) ; 

__attribute__((used)) static void pl08x_desc_free(struct virt_dma_desc *vd)
{
	struct pl08x_txd *txd = to_pl08x_txd(&vd->tx);
	struct pl08x_dma_chan *plchan = to_pl08x_chan(vd->tx.chan);

	dma_descriptor_unmap(&vd->tx);
	if (!txd->done)
		pl08x_release_mux(plchan);

	pl08x_free_txd(plchan->host, txd);
}