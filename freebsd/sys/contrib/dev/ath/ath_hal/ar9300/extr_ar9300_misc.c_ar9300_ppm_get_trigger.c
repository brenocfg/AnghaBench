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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_PHY_CHAN_INFO_MEMORY ; 
 int AR_PHY_CHAN_INFO_MEMORY_CAPTURE_MASK ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

int
ar9300_ppm_get_trigger(struct ath_hal *ah)
{
    if (OS_REG_READ(ah, AR_PHY_CHAN_INFO_MEMORY) &
        AR_PHY_CHAN_INFO_MEMORY_CAPTURE_MASK)
    {
        /* has not triggered yet, return AH_FALSE */
        return 0;
    }

    /* else triggered, return AH_TRUE */
    return 1;
}