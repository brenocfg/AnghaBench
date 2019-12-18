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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AR_BCN_RSSI_AVE ; 
 int /*<<< orphan*/  AR_BCN_RSSI_AVE_VAL ; 
 int OS_REG_READ_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int32_t ar9300_get_hw_beacon_rssi(struct ath_hal *ah)
{
    int32_t val = OS_REG_READ_FIELD(ah, AR_BCN_RSSI_AVE, AR_BCN_RSSI_AVE_VAL);

    /* RSSI format is 8.4.  Ignore lowest four bits */
    val = val >> 4;
    return val;
}