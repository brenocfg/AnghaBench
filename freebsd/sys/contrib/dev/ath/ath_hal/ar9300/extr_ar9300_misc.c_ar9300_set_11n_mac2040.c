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
typedef  scalar_t__ u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ath_hal_cwm_ignore_ext_cca; } ;
struct ath_hal {TYPE_1__ ah_config; } ;
typedef  scalar_t__ HAL_HT_MACMODE ;

/* Variables and functions */
 scalar_t__ AR_2040_JOINED_RX_CLEAR ; 
 int /*<<< orphan*/  AR_2040_MODE ; 
 scalar_t__ HAL_HT_MACMODE_2040 ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 

void
ar9300_set_11n_mac2040(struct ath_hal *ah, HAL_HT_MACMODE mode)
{
    u_int32_t macmode;

    /* Configure MAC for 20/40 operation */
    if (mode == HAL_HT_MACMODE_2040 &&
        !ah->ah_config.ath_hal_cwm_ignore_ext_cca) {
        macmode = AR_2040_JOINED_RX_CLEAR;
    } else {
        macmode = 0;
    }
    OS_REG_WRITE(ah, AR_2040_MODE, macmode);
}