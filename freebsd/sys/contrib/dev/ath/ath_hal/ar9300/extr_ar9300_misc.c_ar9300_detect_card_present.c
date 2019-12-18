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
typedef  int u_int32_t ;
typedef  int u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int ah_macVersion; int ah_macRev; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_SREV ; 
 int AR_SREV_ID ; 
 int AR_SREV_REVISION ; 
 int /*<<< orphan*/  AR_SREV_REVISION2 ; 
 int AR_SREV_TYPE2_S ; 
 int /*<<< orphan*/  AR_SREV_VERSION ; 
 int AR_SREV_VERSION2 ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_detect_card_present(struct ath_hal *ah)
{
    u_int16_t mac_version, mac_rev;
    u_int32_t v;

    /*
     * Read the Silicon Revision register and compare that
     * to what we read at attach time.  If the same, we say
     * a card/device is present.
     */
    v = OS_REG_READ(ah, AR_HOSTIF_REG(ah, AR_SREV)) & AR_SREV_ID;
    if (v == 0xFF) {
        /* new SREV format */
        v = OS_REG_READ(ah, AR_HOSTIF_REG(ah, AR_SREV));
        /*
         * Include 6-bit Chip Type (masked to 0) to differentiate
         * from pre-Sowl versions
         */
        mac_version = (v & AR_SREV_VERSION2) >> AR_SREV_TYPE2_S;
        mac_rev = MS(v, AR_SREV_REVISION2);
    } else {
        mac_version = MS(v, AR_SREV_VERSION);
        mac_rev = v & AR_SREV_REVISION;
    }
    return (AH_PRIVATE(ah)->ah_macVersion == mac_version &&
            AH_PRIVATE(ah)->ah_macRev == mac_rev);
}