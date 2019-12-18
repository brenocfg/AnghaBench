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
typedef  size_t u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ah_txq; } ;
struct TYPE_3__ {scalar_t__ tqi_type; } ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH5211 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_Q_TXD ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 size_t HAL_NUM_TX_QUEUES ; 
 scalar_t__ HAL_TX_QUEUE_INACTIVE ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ar5211NumTxPending (struct ath_hal*,size_t) ; 

HAL_BOOL
ar5211StopTxDma(struct ath_hal *ah, u_int q)
{
	int i;

	HALASSERT(q < HAL_NUM_TX_QUEUES);
	HALASSERT(AH5211(ah)->ah_txq[q].tqi_type != HAL_TX_QUEUE_INACTIVE);

	OS_REG_WRITE(ah, AR_Q_TXD, 1<<q);
	for (i = 0; i < 10000; i++) {
		if (ar5211NumTxPending(ah, q) == 0)
			break;
		OS_DELAY(10);
	}
	OS_REG_WRITE(ah, AR_Q_TXD, 0);

	return (i < 10000);
}