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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ath_hal_9300 {int /*<<< orphan*/  ah_intr_txqs; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_NULL ; 
 int /*<<< orphan*/  HALDEBUG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_DEBUG_UNMASKABLE ; 

void
ar9300_get_tx_intr_queue(struct ath_hal *ah, u_int32_t *txqs)
{
    HALDEBUG(AH_NULL, HAL_DEBUG_UNMASKABLE,
                 "ar9300_get_tx_intr_queue: Should not be called\n");
#if 0
    struct ath_hal_9300 *ahp = AH9300(ah);
    *txqs &= ahp->ah_intr_txqs;
    ahp->ah_intr_txqs &= ~(*txqs);
#endif
}