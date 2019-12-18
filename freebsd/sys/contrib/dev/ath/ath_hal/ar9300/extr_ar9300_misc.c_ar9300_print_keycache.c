#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halKeyCacheSize; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;
typedef  TYPE_1__ HAL_CAPABILITIES ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY1 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY2 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY3 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_KEY4 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC0 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_MAC1 (scalar_t__) ; 
 int /*<<< orphan*/  AR_KEYTABLE_TYPE (scalar_t__) ; 
 int AR_KEYTABLE_VALID ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*,...) ; 

HAL_BOOL
ar9300_print_keycache(struct ath_hal *ah)
{

    const HAL_CAPABILITIES *p_cap = &AH_PRIVATE(ah)->ah_caps;
    u_int32_t key0, key1, key2, key3, key4;
    u_int32_t mac_hi, mac_lo;
    u_int16_t entry = 0;
    u_int32_t valid = 0;
    u_int32_t key_type;

    ath_hal_printf(ah, "Slot   Key\t\t\t          Valid  Type  Mac  \n");

    for (entry = 0 ; entry < p_cap->halKeyCacheSize; entry++) {
        key0 = OS_REG_READ(ah, AR_KEYTABLE_KEY0(entry));
        key1 = OS_REG_READ(ah, AR_KEYTABLE_KEY1(entry));
        key2 = OS_REG_READ(ah, AR_KEYTABLE_KEY2(entry));
        key3 = OS_REG_READ(ah, AR_KEYTABLE_KEY3(entry));
        key4 = OS_REG_READ(ah, AR_KEYTABLE_KEY4(entry));

        key_type = OS_REG_READ(ah, AR_KEYTABLE_TYPE(entry));

        mac_lo = OS_REG_READ(ah, AR_KEYTABLE_MAC0(entry));
        mac_hi = OS_REG_READ(ah, AR_KEYTABLE_MAC1(entry));

        if (mac_hi & AR_KEYTABLE_VALID) {
            valid = 1;
        } else {
            valid = 0;
        }

        if ((mac_hi != 0) && (mac_lo != 0)) {
            mac_hi &= ~0x8000;
            mac_hi <<= 1;
            mac_hi |= ((mac_lo & (1 << 31) )) >> 31;
            mac_lo <<= 1;
        }

        ath_hal_printf(ah,
            "%03d    "
            "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x"
            "   %02d     %02d    "
            "%02x:%02x:%02x:%02x:%02x:%02x \n",
            entry,
            (key0 << 24) >> 24, (key0 << 16) >> 24,
            (key0 << 8) >> 24, key0 >> 24,
            (key1 << 24) >> 24, (key1 << 16) >> 24,
            //(key1 << 8) >> 24, key1 >> 24,
            (key2 << 24) >> 24, (key2 << 16) >> 24,
            (key2 << 8) >> 24, key2 >> 24,
            (key3 << 24) >> 24, (key3 << 16) >> 24,
            //(key3 << 8) >> 24, key3 >> 24,
            (key4 << 24) >> 24, (key4 << 16) >> 24,
            (key4 << 8) >> 24, key4 >> 24,
            valid, key_type,
            (mac_lo << 24) >> 24, (mac_lo << 16) >> 24, (mac_lo << 8) >> 24,
            (mac_lo) >> 24, (mac_hi << 24) >> 24, (mac_hi << 16) >> 24 );
    }

    return AH_TRUE;
}