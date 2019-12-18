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
struct transaction_callback_data {int rcode; int /*<<< orphan*/  done; void* payload; } ;
struct fw_transaction {int /*<<< orphan*/  split_timeout_timer; } ;
struct fw_card {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_timer_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fw_send_request (struct fw_card*,struct fw_transaction*,int,int,int,int,unsigned long long,void*,size_t,int /*<<< orphan*/ ,struct transaction_callback_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup_on_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_callback ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int fw_run_transaction(struct fw_card *card, int tcode, int destination_id,
		       int generation, int speed, unsigned long long offset,
		       void *payload, size_t length)
{
	struct transaction_callback_data d;
	struct fw_transaction t;

	timer_setup_on_stack(&t.split_timeout_timer, NULL, 0);
	init_completion(&d.done);
	d.payload = payload;
	fw_send_request(card, &t, tcode, destination_id, generation, speed,
			offset, payload, length, transaction_callback, &d);
	wait_for_completion(&d.done);
	destroy_timer_on_stack(&t.split_timeout_timer);

	return d.rcode;
}