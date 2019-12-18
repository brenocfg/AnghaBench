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
struct sfxge_txq {int /*<<< orphan*/  flush_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_FLUSH_DONE ; 

void
sfxge_tx_qflush_done(struct sfxge_txq *txq)
{

	txq->flush_state = SFXGE_FLUSH_DONE;
}