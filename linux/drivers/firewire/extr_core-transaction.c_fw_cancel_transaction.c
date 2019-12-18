#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fw_transaction {int /*<<< orphan*/  packet; } ;
struct fw_card {TYPE_1__* driver; } ;
struct TYPE_2__ {scalar_t__ (* cancel_packet ) (struct fw_card*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RCODE_CANCELLED ; 
 int close_transaction (struct fw_transaction*,struct fw_card*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct fw_card*,int /*<<< orphan*/ *) ; 

int fw_cancel_transaction(struct fw_card *card,
			  struct fw_transaction *transaction)
{
	/*
	 * Cancel the packet transmission if it's still queued.  That
	 * will call the packet transmission callback which cancels
	 * the transaction.
	 */

	if (card->driver->cancel_packet(card, &transaction->packet) == 0)
		return 0;

	/*
	 * If the request packet has already been sent, we need to see
	 * if the transaction is still pending and remove it in that case.
	 */

	return close_transaction(transaction, card, RCODE_CANCELLED);
}