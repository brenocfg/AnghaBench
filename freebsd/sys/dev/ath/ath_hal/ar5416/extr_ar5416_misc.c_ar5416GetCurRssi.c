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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9130_PHY_CURRENT_RSSI ; 
 int /*<<< orphan*/  AR_PHY_CURRENT_RSSI ; 
 scalar_t__ AR_SREV_OWL (struct ath_hal*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

uint32_t
ar5416GetCurRssi(struct ath_hal *ah)
{
	if (AR_SREV_OWL(ah))
		return (OS_REG_READ(ah, AR_PHY_CURRENT_RSSI) & 0xff);
	return (OS_REG_READ(ah, AR9130_PHY_CURRENT_RSSI) & 0xff);
}