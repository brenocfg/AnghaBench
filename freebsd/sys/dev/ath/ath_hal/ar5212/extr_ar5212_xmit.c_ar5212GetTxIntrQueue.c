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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_hal_5212 {int /*<<< orphan*/  ah_intrTxqs; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 

void
ar5212GetTxIntrQueue(struct ath_hal *ah, uint32_t *txqs)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	*txqs &= ahp->ah_intrTxqs;
	ahp->ah_intrTxqs &= ~(*txqs);
}