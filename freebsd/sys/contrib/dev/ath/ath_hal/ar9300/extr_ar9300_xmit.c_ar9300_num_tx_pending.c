#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_8__ {TYPE_1__* ah_txq; } ;
struct TYPE_6__ {int halTotalQueues; } ;
struct TYPE_7__ {TYPE_2__ ah_caps; } ;
struct TYPE_5__ {scalar_t__ tqi_type; } ;

/* Variables and functions */
 TYPE_4__* AH9300 (struct ath_hal*) ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_QSTS (int) ; 
 int /*<<< orphan*/  AR_Q_RDYTIMESHDN ; 
 int AR_Q_STS_PEND_FR_CNT ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_DEBUG_QUEUE ; 
 scalar_t__ HAL_TX_QUEUE_CAB ; 
 scalar_t__ HAL_TX_QUEUE_INACTIVE ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

u_int32_t
ar9300_num_tx_pending(struct ath_hal *ah, u_int q)
{
    u_int32_t npend;

    HALASSERT(q < AH_PRIVATE(ah)->ah_caps.halTotalQueues);

    npend = OS_REG_READ(ah, AR_QSTS(q)) & AR_Q_STS_PEND_FR_CNT;
    if (npend == 0) {
        /*
         * Pending frame count (PFC) can momentarily go to zero
         * while TXE remains asserted.  In other words a PFC of
         * zero is not sufficient to say that the queue has stopped.
         */
        if (OS_REG_READ(ah, AR_Q_TXE) & (1 << q)) {
            npend = 1;              /* arbitrarily return 1 */
        }
    }
#ifdef DEBUG
    if (npend && (AH9300(ah)->ah_txq[q].tqi_type == HAL_TX_QUEUE_CAB)) {
        if (OS_REG_READ(ah, AR_Q_RDYTIMESHDN) & (1 << q)) {
            HALDEBUG(ah, HAL_DEBUG_QUEUE, "RTSD on CAB queue\n");
            /* Clear the ready_time shutdown status bits */
            OS_REG_WRITE(ah, AR_Q_RDYTIMESHDN, 1 << q);
        }
    }
#endif
    HALASSERT((npend == 0) ||
        (AH9300(ah)->ah_txq[q].tqi_type != HAL_TX_QUEUE_INACTIVE));

    return npend;
}