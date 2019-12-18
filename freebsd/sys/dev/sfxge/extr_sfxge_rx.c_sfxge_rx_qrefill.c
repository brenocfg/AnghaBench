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
struct sfxge_rxq {scalar_t__ init_state; int /*<<< orphan*/  entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EFX_RXQ_LIMIT (int /*<<< orphan*/ ) ; 
 scalar_t__ SFXGE_RXQ_STARTED ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  sfxge_rx_qfill (struct sfxge_rxq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sfxge_rx_qrefill(struct sfxge_rxq *rxq)
{

	if (__predict_false(rxq->init_state != SFXGE_RXQ_STARTED))
		return;

	/* Make sure the queue is full */
	sfxge_rx_qfill(rxq, EFX_RXQ_LIMIT(rxq->entries), B_TRUE);
}