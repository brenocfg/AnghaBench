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
typedef  int /*<<< orphan*/  u32 ;
struct dw_dma_chan {int dummy; } ;

/* Variables and functions */
 size_t IDMA32C_CTLH_BLOCK_TS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t idma32_block2bytes(struct dw_dma_chan *dwc, u32 block, u32 width)
{
	return IDMA32C_CTLH_BLOCK_TS(block);
}