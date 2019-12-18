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
typedef  int u8 ;
typedef  size_t u32 ;
struct hidma_tre {int err_code; } ;
struct hidma_lldev {int /*<<< orphan*/  lock; struct hidma_tre* trepool; } ;
typedef  enum dma_status { ____Placeholder_dma_status } dma_status ;

/* Variables and functions */
 int DMA_COMPLETE ; 
 int DMA_ERROR ; 
 int DMA_IN_PROGRESS ; 
 int HIDMA_EVRE_STATUS_COMPLETE ; 
 int HIDMA_EVRE_STATUS_ERROR ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

enum dma_status hidma_ll_status(struct hidma_lldev *lldev, u32 tre_ch)
{
	enum dma_status ret = DMA_ERROR;
	struct hidma_tre *tre;
	unsigned long flags;
	u8 err_code;

	spin_lock_irqsave(&lldev->lock, flags);

	tre = &lldev->trepool[tre_ch];
	err_code = tre->err_code;

	if (err_code & HIDMA_EVRE_STATUS_COMPLETE)
		ret = DMA_COMPLETE;
	else if (err_code & HIDMA_EVRE_STATUS_ERROR)
		ret = DMA_ERROR;
	else
		ret = DMA_IN_PROGRESS;
	spin_unlock_irqrestore(&lldev->lock, flags);

	return ret;
}