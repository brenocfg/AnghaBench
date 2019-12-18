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
 scalar_t__ MV_XOR_V2_DMA_DESQ_ADD_OFF ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mv_xor_v2_add_desc_to_desq(struct mv_xor_v2_device *xor_dev,
				       int num_of_desc)
{
	/* write the number of new descriptors in the DESQ. */
	writel(num_of_desc, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ADD_OFF);
}