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
struct ath_hal_5212 {scalar_t__ ah_rfHal; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 scalar_t__ AH_NULL ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  ath_hal_free (scalar_t__) ; 

__attribute__((used)) static void
ar5413RfDetach(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	HALASSERT(ahp->ah_rfHal != AH_NULL);
	ath_hal_free(ahp->ah_rfHal);
	ahp->ah_rfHal = AH_NULL;
}