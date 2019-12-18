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
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_getNoiseFloor; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 scalar_t__ AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 scalar_t__ ar9280RfAttach (struct ath_hal*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ar9285GetNoiseFloor ; 

HAL_BOOL
ar9285RfAttach(struct ath_hal *ah, HAL_STATUS *status)
{
	if (ar9280RfAttach(ah, status) == AH_FALSE)
		return AH_FALSE;

	AH_PRIVATE(ah)->ah_getNoiseFloor = ar9285GetNoiseFloor;

	return AH_TRUE;
}