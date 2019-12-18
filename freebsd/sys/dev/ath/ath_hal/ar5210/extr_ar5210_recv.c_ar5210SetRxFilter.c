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
 int /*<<< orphan*/  AR_RX_FILTER ; 
 int AR_RX_FILTER_PROMISCUOUS ; 
 int HAL_RX_FILTER_PHYRADAR ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5210SetRxFilter(struct ath_hal *ah, uint32_t bits)
{
	if (bits & HAL_RX_FILTER_PHYRADAR) {
		/* must enable promiscuous mode to get radar */
		bits = (bits &~ HAL_RX_FILTER_PHYRADAR) | AR_RX_FILTER_PROMISCUOUS;
	}
	OS_REG_WRITE(ah, AR_RX_FILTER, bits);
}