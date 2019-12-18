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
 int /*<<< orphan*/  HAL_CAP_LDPCWAR ; 
 int /*<<< orphan*/  HAL_CAP_RIFS_RX ; 
 scalar_t__ HAL_OK ; 
 scalar_t__ ar9300_get_capability (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_rifs_delay (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ ath_hal_getcapability (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_set_11n_rx_rifs(struct ath_hal *ah, HAL_BOOL enable)
{
    /* Non-Owl 11n chips */
    if ((ath_hal_getcapability(ah, HAL_CAP_RIFS_RX, 0, AH_NULL) == HAL_OK)) {
        if (ar9300_get_capability(ah, HAL_CAP_LDPCWAR, 0, AH_NULL) == HAL_OK) {
            return ar9300_set_rifs_delay(ah, enable);
        }
        return AH_FALSE;
    }

    return AH_TRUE;
}