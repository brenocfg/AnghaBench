#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  phys; } ;
struct tegra_ivc {int num_frames; int frame_size; TYPE_2__ tx; scalar_t__ peer; TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_single (scalar_t__,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 size_t tegra_ivc_total_queue_size (int) ; 

void tegra_ivc_cleanup(struct tegra_ivc *ivc)
{
	if (ivc->peer) {
		size_t size = tegra_ivc_total_queue_size(ivc->num_frames *
							 ivc->frame_size);

		dma_unmap_single(ivc->peer, ivc->rx.phys, size,
				 DMA_BIDIRECTIONAL);
		dma_unmap_single(ivc->peer, ivc->tx.phys, size,
				 DMA_BIDIRECTIONAL);
	}
}