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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct shallow_info {int dummy; } ;
struct command {char* error_string; struct command* next; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  ref_transaction_begin (struct strbuf*) ; 
 scalar_t__ ref_transaction_commit (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  ref_transaction_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rp_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  should_process_cmd (struct command*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  transaction ; 
 char* update (struct command*,struct shallow_info*) ; 

__attribute__((used)) static void execute_commands_non_atomic(struct command *commands,
					struct shallow_info *si)
{
	struct command *cmd;
	struct strbuf err = STRBUF_INIT;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (!should_process_cmd(cmd))
			continue;

		transaction = ref_transaction_begin(&err);
		if (!transaction) {
			rp_error("%s", err.buf);
			strbuf_reset(&err);
			cmd->error_string = "transaction failed to start";
			continue;
		}

		cmd->error_string = update(cmd, si);

		if (!cmd->error_string
		    && ref_transaction_commit(transaction, &err)) {
			rp_error("%s", err.buf);
			strbuf_reset(&err);
			cmd->error_string = "failed to update ref";
		}
		ref_transaction_free(transaction);
	}
	strbuf_release(&err);
}