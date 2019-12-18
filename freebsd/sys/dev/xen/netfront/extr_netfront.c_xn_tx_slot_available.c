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
struct netfront_txq {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 scalar_t__ MAX_TX_REQ_FRAGS ; 
 scalar_t__ RING_FREE_REQUESTS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
xn_tx_slot_available(struct netfront_txq *txq)
{

	return (RING_FREE_REQUESTS(&txq->ring) > (MAX_TX_REQ_FRAGS + 2));
}