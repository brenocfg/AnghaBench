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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static int
ps3_iommu_unmap(device_t dev, bus_dma_segment_t *segs, int nsegs, void *cookie)
{

	return (0);
}