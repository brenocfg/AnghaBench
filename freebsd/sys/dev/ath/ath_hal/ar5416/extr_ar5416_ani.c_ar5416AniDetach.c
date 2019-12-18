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
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_DEBUG_ANI ; 
 int /*<<< orphan*/  disableAniMIBCounters (struct ath_hal*) ; 

void
ar5416AniDetach(struct ath_hal *ah)
{
	HALDEBUG(ah, HAL_DEBUG_ANI, "Detaching Ani\n");
	disableAniMIBCounters(ah);
}