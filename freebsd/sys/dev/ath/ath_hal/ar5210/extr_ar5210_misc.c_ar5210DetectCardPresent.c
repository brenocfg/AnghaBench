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
struct TYPE_2__ {int ah_macRev; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5210DetectCardPresent(struct ath_hal *ah)
{
	/*
	 * Read the Silicon Revision register and compare that
	 * to what we read at attach time.  If the same, we say
	 * a card/device is present.
	 */
	return (AH_PRIVATE(ah)->ah_macRev == (OS_REG_READ(ah, AR_SREV) & 0xff));
}