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

/* Variables and functions */
 int /*<<< orphan*/  AR_RSSI_BCN_RSSI_RST ; 
 int /*<<< orphan*/  AR_RSSI_THR ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ar9300_reset_hw_beacon_rssi(struct ath_hal *ah)
{
    OS_REG_SET_BIT(ah, AR_RSSI_THR, AR_RSSI_BCN_RSSI_RST);
}