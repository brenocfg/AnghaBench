#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_currentRD; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HAL_EIO ; 

HAL_BOOL
ar9300_set_regulatory_domain(struct ath_hal *ah,
        u_int16_t reg_domain, HAL_STATUS *status)
{
    HAL_STATUS ecode;

    if (AH_PRIVATE(ah)->ah_currentRD == 0) {
        AH_PRIVATE(ah)->ah_currentRD = reg_domain;
        return AH_TRUE;
    }
    ecode = HAL_EIO;

#if 0
bad:
#endif
    if (status) {
        *status = ecode;
    }
    return AH_FALSE;
}