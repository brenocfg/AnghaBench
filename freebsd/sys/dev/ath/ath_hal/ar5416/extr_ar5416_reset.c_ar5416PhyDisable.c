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
struct TYPE_2__ {int /*<<< orphan*/  (* ah_initPLL ) (struct ath_hal*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH5416 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_NULL ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  HAL_RESET_WARM ; 
 int /*<<< orphan*/  ar5416SetResetReg (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5416PhyDisable(struct ath_hal *ah)
{

	if (! ar5416SetResetReg(ah, HAL_RESET_WARM))
		return AH_FALSE;

	AH5416(ah)->ah_initPLL(ah, AH_NULL);
	return (AH_TRUE);
}