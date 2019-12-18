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
typedef  scalar_t__ u32 ;
struct dw_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct dw_desc {scalar_t__ total_len; scalar_t__ residue; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  DW_DMA_IS_SOFT_LLP ; 
 struct dw_desc* dwc_find_desc (struct dw_dma_chan*,int /*<<< orphan*/ ) ; 
 struct dw_desc* dwc_first_active (struct dw_dma_chan*) ; 
 scalar_t__ dwc_get_sent (struct dw_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 dwc_get_residue(struct dw_dma_chan *dwc, dma_cookie_t cookie)
{
	struct dw_desc *desc;
	unsigned long flags;
	u32 residue;

	spin_lock_irqsave(&dwc->lock, flags);

	desc = dwc_find_desc(dwc, cookie);
	if (desc) {
		if (desc == dwc_first_active(dwc)) {
			residue = desc->residue;
			if (test_bit(DW_DMA_IS_SOFT_LLP, &dwc->flags) && residue)
				residue -= dwc_get_sent(dwc);
		} else {
			residue = desc->total_len;
		}
	} else {
		residue = 0;
	}

	spin_unlock_irqrestore(&dwc->lock, flags);
	return residue;
}