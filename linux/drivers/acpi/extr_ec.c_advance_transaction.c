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
typedef  int u8 ;
struct transaction {int flags; scalar_t__ wlen; scalar_t__ wi; scalar_t__ rlen; scalar_t__ ri; int* rdata; scalar_t__ command; scalar_t__ irq_count; int /*<<< orphan*/ * wdata; } ;
struct acpi_ec {int /*<<< orphan*/  wait; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending_queries; struct transaction* curr; } ;

/* Variables and functions */
 int ACPI_EC_COMMAND_COMPLETE ; 
 int ACPI_EC_COMMAND_POLL ; 
 scalar_t__ ACPI_EC_COMMAND_QUERY ; 
 scalar_t__ ACPI_EC_EVT_TIMING_EVENT ; 
 int ACPI_EC_FLAG_IBF ; 
 int ACPI_EC_FLAG_OBF ; 
 int ACPI_EC_FLAG_SCI ; 
 int /*<<< orphan*/  EC_FLAGS_QUERY_GUARDING ; 
 scalar_t__ EC_FLAGS_QUERY_HANDSHAKE ; 
 int /*<<< orphan*/  acpi_ec_clear_gpe (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_cmd_string (scalar_t__) ; 
 int /*<<< orphan*/  acpi_ec_complete_query (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_mask_gpe (struct acpi_ec*) ; 
 int acpi_ec_read_data (struct acpi_ec*) ; 
 int acpi_ec_read_status (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_submit_query (struct acpi_ec*) ; 
 int /*<<< orphan*/  acpi_ec_write_cmd (struct acpi_ec*,scalar_t__) ; 
 int /*<<< orphan*/  acpi_ec_write_data (struct acpi_ec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_dbg_evt (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_dbg_stm (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ec_event_clearing ; 
 scalar_t__ ec_storm_threshold ; 
 int /*<<< orphan*/  ec_transaction_transition (struct acpi_ec*,int) ; 
 scalar_t__ in_interrupt () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void advance_transaction(struct acpi_ec *ec)
{
	struct transaction *t;
	u8 status;
	bool wakeup = false;

	ec_dbg_stm("%s (%d)", in_interrupt() ? "IRQ" : "TASK",
		   smp_processor_id());
	/*
	 * By always clearing STS before handling all indications, we can
	 * ensure a hardware STS 0->1 change after this clearing can always
	 * trigger a GPE interrupt.
	 */
	acpi_ec_clear_gpe(ec);
	status = acpi_ec_read_status(ec);
	t = ec->curr;
	/*
	 * Another IRQ or a guarded polling mode advancement is detected,
	 * the next QR_EC submission is then allowed.
	 */
	if (!t || !(t->flags & ACPI_EC_COMMAND_POLL)) {
		if (ec_event_clearing == ACPI_EC_EVT_TIMING_EVENT &&
		    (!ec->nr_pending_queries ||
		     test_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags))) {
			clear_bit(EC_FLAGS_QUERY_GUARDING, &ec->flags);
			acpi_ec_complete_query(ec);
		}
	}
	if (!t)
		goto err;
	if (t->flags & ACPI_EC_COMMAND_POLL) {
		if (t->wlen > t->wi) {
			if ((status & ACPI_EC_FLAG_IBF) == 0)
				acpi_ec_write_data(ec, t->wdata[t->wi++]);
			else
				goto err;
		} else if (t->rlen > t->ri) {
			if ((status & ACPI_EC_FLAG_OBF) == 1) {
				t->rdata[t->ri++] = acpi_ec_read_data(ec);
				if (t->rlen == t->ri) {
					ec_transaction_transition(ec, ACPI_EC_COMMAND_COMPLETE);
					if (t->command == ACPI_EC_COMMAND_QUERY)
						ec_dbg_evt("Command(%s) completed by hardware",
							   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
					wakeup = true;
				}
			} else
				goto err;
		} else if (t->wlen == t->wi &&
			   (status & ACPI_EC_FLAG_IBF) == 0) {
			ec_transaction_transition(ec, ACPI_EC_COMMAND_COMPLETE);
			wakeup = true;
		}
		goto out;
	} else {
		if (EC_FLAGS_QUERY_HANDSHAKE &&
		    !(status & ACPI_EC_FLAG_SCI) &&
		    (t->command == ACPI_EC_COMMAND_QUERY)) {
			ec_transaction_transition(ec, ACPI_EC_COMMAND_POLL);
			t->rdata[t->ri++] = 0x00;
			ec_transaction_transition(ec, ACPI_EC_COMMAND_COMPLETE);
			ec_dbg_evt("Command(%s) completed by software",
				   acpi_ec_cmd_string(ACPI_EC_COMMAND_QUERY));
			wakeup = true;
		} else if ((status & ACPI_EC_FLAG_IBF) == 0) {
			acpi_ec_write_cmd(ec, t->command);
			ec_transaction_transition(ec, ACPI_EC_COMMAND_POLL);
		} else
			goto err;
		goto out;
	}
err:
	/*
	 * If SCI bit is set, then don't think it's a false IRQ
	 * otherwise will take a not handled IRQ as a false one.
	 */
	if (!(status & ACPI_EC_FLAG_SCI)) {
		if (in_interrupt() && t) {
			if (t->irq_count < ec_storm_threshold)
				++t->irq_count;
			/* Allow triggering on 0 threshold */
			if (t->irq_count == ec_storm_threshold)
				acpi_ec_mask_gpe(ec);
		}
	}
out:
	if (status & ACPI_EC_FLAG_SCI)
		acpi_ec_submit_query(ec);
	if (wakeup && in_interrupt())
		wake_up(&ec->wait);
}