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
struct sprd_dma_desc {int dummy; } ;
typedef  enum sprd_dma_req_mode { ____Placeholder_sprd_dma_req_mode } sprd_dma_req_mode ;
typedef  enum sprd_dma_int_type { ____Placeholder_sprd_dma_int_type } sprd_dma_int_type ;

/* Variables and functions */
 int SPRD_DMA_NO_INT ; 

__attribute__((used)) static bool sprd_dma_check_trans_done(struct sprd_dma_desc *sdesc,
				      enum sprd_dma_int_type int_type,
				      enum sprd_dma_req_mode req_mode)
{
	if (int_type == SPRD_DMA_NO_INT)
		return false;

	if (int_type >= req_mode + 1)
		return true;
	else
		return false;
}