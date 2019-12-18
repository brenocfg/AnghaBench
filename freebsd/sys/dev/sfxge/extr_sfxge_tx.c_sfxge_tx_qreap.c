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
struct sfxge_txq {int /*<<< orphan*/  completed; int /*<<< orphan*/  reaped; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_TXQ_LOCK_ASSERT_OWNED (struct sfxge_txq*) ; 

__attribute__((used)) static void
sfxge_tx_qreap(struct sfxge_txq *txq)
{
	SFXGE_TXQ_LOCK_ASSERT_OWNED(txq);

	txq->reaped = txq->completed;
}