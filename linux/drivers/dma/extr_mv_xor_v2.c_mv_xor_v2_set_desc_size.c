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
struct mv_xor_v2_device {scalar_t__ dma_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_XOR_V2_DMA_DESQ_CTRL_128B ; 
 scalar_t__ MV_XOR_V2_DMA_DESQ_CTRL_OFF ; 
 int MV_XOR_V2_EXT_DESC_SIZE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mv_xor_v2_set_desc_size(struct mv_xor_v2_device *xor_dev)
{
	writel(MV_XOR_V2_DMA_DESQ_CTRL_128B,
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_CTRL_OFF);

	return MV_XOR_V2_EXT_DESC_SIZE;
}