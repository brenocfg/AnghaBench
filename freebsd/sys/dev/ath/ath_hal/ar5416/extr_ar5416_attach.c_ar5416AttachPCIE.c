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
struct TYPE_2__ {scalar_t__ ah_ispcie; } ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  ath_hal_configPCIE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_hal_disablePCIE (struct ath_hal*) ; 

void
ar5416AttachPCIE(struct ath_hal *ah)
{
	if (AH_PRIVATE(ah)->ah_ispcie)
		ath_hal_configPCIE(ah, AH_FALSE, AH_FALSE);
	else
		ath_hal_disablePCIE(ah);
}