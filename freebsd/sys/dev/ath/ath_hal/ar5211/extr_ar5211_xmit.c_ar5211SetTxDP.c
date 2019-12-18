#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ah_txq; } ;
struct TYPE_3__ {scalar_t__ tqi_type; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH5211 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_QTXDP (size_t) ; 
 int /*<<< orphan*/  AR_Q_TXE ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 size_t HAL_NUM_TX_QUEUES ; 
 scalar_t__ HAL_TX_QUEUE_INACTIVE ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5211SetTxDP(struct ath_hal *ah, u_int q, uint32_t txdp)
{
	HALASSERT(q < HAL_NUM_TX_QUEUES);
	HALASSERT(AH5211(ah)->ah_txq[q].tqi_type != HAL_TX_QUEUE_INACTIVE);

	/*
	 * Make sure that TXE is deasserted before setting the TXDP.  If TXE
	 * is still asserted, setting TXDP will have no effect.
	 */
	HALASSERT((OS_REG_READ(ah, AR_Q_TXE) & (1 << q)) == 0);

	OS_REG_WRITE(ah, AR_QTXDP(q), txdp);

	return AH_TRUE;
}