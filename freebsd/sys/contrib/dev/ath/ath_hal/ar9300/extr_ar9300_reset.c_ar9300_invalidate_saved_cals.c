#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_5__ {int ath_hal_cal_reuse; } ;
struct TYPE_7__ {TYPE_1__ ah_config; } ;
struct TYPE_6__ {void* one_time_txclcal_done; void* one_time_txiqcal_done; } ;
typedef  TYPE_2__ HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 void* AH_FALSE ; 
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
 int ATH_CAL_REUSE_REDO_IN_FULL_RESET ; 

__attribute__((used)) static inline void
ar9300_invalidate_saved_cals(struct ath_hal *ah, HAL_CHANNEL_INTERNAL *ichan)
{
#if ATH_SUPPORT_CAL_REUSE
    if (AH_PRIVATE(ah)->ah_config.ath_hal_cal_reuse &
        ATH_CAL_REUSE_REDO_IN_FULL_RESET)
    {
        ichan->one_time_txiqcal_done = AH_FALSE;
        ichan->one_time_txclcal_done = AH_FALSE;
    }
#endif
}