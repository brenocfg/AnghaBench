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
typedef  scalar_t__ u_int32_t ;
typedef  size_t u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_8__ {TYPE_2__* ah_txq; } ;
struct TYPE_5__ {size_t halTotalQueues; } ;
struct TYPE_7__ {TYPE_1__ ah_caps; } ;
struct TYPE_6__ {scalar_t__ tqi_type; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_4__* AH9300 (struct ath_hal*) ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_QTXDP (size_t) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_TX_QUEUE_INACTIVE ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,scalar_t__) ; 

HAL_BOOL
ar9300_set_tx_dp(struct ath_hal *ah, u_int q, u_int32_t txdp)
{
    HALASSERT(q < AH_PRIVATE(ah)->ah_caps.halTotalQueues);
    HALASSERT(AH9300(ah)->ah_txq[q].tqi_type != HAL_TX_QUEUE_INACTIVE);
    HALASSERT(txdp != 0);

    OS_REG_WRITE(ah, AR_QTXDP(q), txdp);

    return AH_TRUE;
}