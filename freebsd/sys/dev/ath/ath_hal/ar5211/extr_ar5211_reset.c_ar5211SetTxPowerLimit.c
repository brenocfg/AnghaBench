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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_powerLimit; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_POWER_TX_RATE_MAX ; 
 int /*<<< orphan*/  MAX_RATE_POWER ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5211SetTxPowerLimit(struct ath_hal *ah, uint32_t limit)
{

	AH_PRIVATE(ah)->ah_powerLimit = AH_MIN(limit, MAX_RATE_POWER);
	OS_REG_WRITE(ah, AR_PHY_POWER_TX_RATE_MAX, limit);
	return AH_TRUE;
}