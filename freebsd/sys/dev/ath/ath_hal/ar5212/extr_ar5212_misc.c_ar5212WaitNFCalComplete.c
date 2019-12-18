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
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  ar5212IsNFCalInProgress (struct ath_hal*) ; 

HAL_BOOL
ar5212WaitNFCalComplete(struct ath_hal *ah, int i)
{
	int j;
	if (i <= 0)
		i = 1;	  /* it should run at least once */
	for (j = 0; j < i; j++) {
		if (! ar5212IsNFCalInProgress(ah))
			return AH_TRUE;
		OS_DELAY(10);
	}
	return AH_FALSE;
}