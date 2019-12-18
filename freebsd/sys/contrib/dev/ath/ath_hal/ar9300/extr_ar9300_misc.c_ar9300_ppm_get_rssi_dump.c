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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR_PHY_ANALOG_SWAP ; 
 scalar_t__ AR_PHY_CHAN_INFO_GAIN_0 ; 
 int AR_PHY_SWAP_ALT_CHAIN ; 
 int OS_REG_READ (struct ath_hal*,scalar_t__) ; 

u_int32_t
ar9300_ppm_get_rssi_dump(struct ath_hal *ah)
{
    u_int32_t retval;
    u_int32_t off1;
    u_int32_t off2;

    if (OS_REG_READ(ah, AR_PHY_ANALOG_SWAP) & AR_PHY_SWAP_ALT_CHAIN) {
        off1 = 0x2000;
        off2 = 0x1000;
    } else {
        off1 = 0x1000;
        off2 = 0x2000;
    }

    retval = ((0xff & OS_REG_READ(ah, AR_PHY_CHAN_INFO_GAIN_0       )) << 0) |
             ((0xff & OS_REG_READ(ah, AR_PHY_CHAN_INFO_GAIN_0 + off1)) << 8) |
             ((0xff & OS_REG_READ(ah, AR_PHY_CHAN_INFO_GAIN_0 + off2)) << 16);

    return retval;
}