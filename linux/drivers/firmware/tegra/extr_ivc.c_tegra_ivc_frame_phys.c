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
struct tegra_ivc_header {int dummy; } ;
struct tegra_ivc {unsigned int frame_size; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */

__attribute__((used)) static inline dma_addr_t tegra_ivc_frame_phys(struct tegra_ivc *ivc,
					      dma_addr_t phys,
					      unsigned int frame)
{
	unsigned long offset;

	offset = sizeof(struct tegra_ivc_header) + ivc->frame_size * frame;

	return phys + offset;
}