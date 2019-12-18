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
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HAL_PM_AWAKE ; 
 int /*<<< orphan*/  HAL_RESET_COLD ; 
 int /*<<< orphan*/  ar9300_init_pll (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_power_mode (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_reset_reg (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_disable(struct ath_hal *ah)
{
    if (!ar9300_set_power_mode(ah, HAL_PM_AWAKE, AH_TRUE)) {
        return AH_FALSE;
    }
    if (!ar9300_set_reset_reg(ah, HAL_RESET_COLD)) {
        return AH_FALSE;
    }

    ar9300_init_pll(ah, AH_NULL);

    return AH_TRUE;
}