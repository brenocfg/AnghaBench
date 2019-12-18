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
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AR_HWBCNPROC1 ; 
 int AR_HWBCNPROC1_CRC_ENABLE ; 
 int AR_HWBCNPROC1_EXCLUDE_TIM_ELM ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void ar9300_set_hw_beacon_proc(struct ath_hal *ah, HAL_BOOL on)
{
    if (on) {
        OS_REG_SET_BIT(ah, AR_HWBCNPROC1, AR_HWBCNPROC1_CRC_ENABLE |
                       AR_HWBCNPROC1_EXCLUDE_TIM_ELM);
    }
    else {
        OS_REG_CLR_BIT(ah, AR_HWBCNPROC1, AR_HWBCNPROC1_CRC_ENABLE |
                       AR_HWBCNPROC1_EXCLUDE_TIM_ELM);
    }
}