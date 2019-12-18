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
struct ath_hal_9300 {scalar_t__ ah_enable_tsf2; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_DC_AP_STA_EN ; 
 int /*<<< orphan*/  AR_DIRECT_CONNECT ; 
 int /*<<< orphan*/  AR_RESET_TSF ; 
 int /*<<< orphan*/  AR_RESET_TSF2_ONCE ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9300_start_tsf2(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    if (ahp->ah_enable_tsf2) {
        /* Delay might be needed after TSF2 reset */
        OS_REG_SET_BIT(ah, AR_DIRECT_CONNECT, AR_DC_AP_STA_EN);
        OS_REG_SET_BIT(ah, AR_RESET_TSF, AR_RESET_TSF2_ONCE);
    }
}