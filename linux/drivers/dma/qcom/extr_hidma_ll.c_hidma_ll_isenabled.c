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
struct hidma_lldev {void* evch_state; void* trch_state; scalar_t__ evca; scalar_t__ trca; } ;

/* Variables and functions */
 void* HIDMA_CH_STATE (int /*<<< orphan*/ ) ; 
 scalar_t__ HIDMA_EVCA_CTRLSTS_REG ; 
 scalar_t__ HIDMA_TRCA_CTRLSTS_REG ; 
 scalar_t__ hidma_is_chan_enabled (void*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

bool hidma_ll_isenabled(struct hidma_lldev *lldev)
{
	u32 val;

	val = readl(lldev->trca + HIDMA_TRCA_CTRLSTS_REG);
	lldev->trch_state = HIDMA_CH_STATE(val);
	val = readl(lldev->evca + HIDMA_EVCA_CTRLSTS_REG);
	lldev->evch_state = HIDMA_CH_STATE(val);

	/* both channels have to be enabled before calling this function */
	if (hidma_is_chan_enabled(lldev->trch_state) &&
	    hidma_is_chan_enabled(lldev->evch_state))
		return true;

	return false;
}