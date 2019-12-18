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
typedef  int /*<<< orphan*/  uint32_t ;
struct xdma_sglist {int src_width; int dst_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_DST_BURST_SIZE_1 ; 
 int /*<<< orphan*/  CCR_DST_BURST_SIZE_2 ; 
 int /*<<< orphan*/  CCR_DST_BURST_SIZE_4 ; 
 int /*<<< orphan*/  CCR_SRC_BURST_SIZE_1 ; 
 int /*<<< orphan*/  CCR_SRC_BURST_SIZE_2 ; 
 int /*<<< orphan*/  CCR_SRC_BURST_SIZE_4 ; 

__attribute__((used)) static int
pl330_ccr_port_width(struct xdma_sglist *sg, uint32_t *addr)
{
	uint32_t reg;

	reg = 0;

	switch (sg->src_width) {
	case 1:
		reg |= CCR_SRC_BURST_SIZE_1;
		break;
	case 2:
		reg |= CCR_SRC_BURST_SIZE_2;
		break;
	case 4:
		reg |= CCR_SRC_BURST_SIZE_4;
		break;
	default:
		return (-1);
	}

	switch (sg->dst_width) {
	case 1:
		reg |= CCR_DST_BURST_SIZE_1;
		break;
	case 2:
		reg |= CCR_DST_BURST_SIZE_2;
		break;
	case 4:
		reg |= CCR_DST_BURST_SIZE_4;
		break;
	default:
		return (-1);
	}

	*addr |= reg;

	return (0);
}