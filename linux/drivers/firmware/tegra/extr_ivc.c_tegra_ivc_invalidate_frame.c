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
struct tegra_ivc {unsigned int num_frames; int /*<<< orphan*/  peer; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ tegra_ivc_frame_phys (struct tegra_ivc*,scalar_t__,unsigned int) ; 

__attribute__((used)) static inline void tegra_ivc_invalidate_frame(struct tegra_ivc *ivc,
					      dma_addr_t phys,
					      unsigned int frame,
					      unsigned int offset,
					      size_t size)
{
	if (!ivc->peer || WARN_ON(frame >= ivc->num_frames))
		return;

	phys = tegra_ivc_frame_phys(ivc, phys, frame) + offset;

	dma_sync_single_for_cpu(ivc->peer, phys, size, DMA_FROM_DEVICE);
}