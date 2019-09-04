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
struct strbuf {char* buf; int len; } ;
struct ref_transaction {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ isspace (char const) ; 
 char const line_termination ; 
 char* parse_cmd_create (struct ref_transaction*,struct strbuf*,char const*) ; 
 char* parse_cmd_delete (struct ref_transaction*,struct strbuf*,char const*) ; 
 char* parse_cmd_option (struct strbuf*,char const*) ; 
 char* parse_cmd_update (struct ref_transaction*,struct strbuf*,char const*) ; 
 char* parse_cmd_verify (struct ref_transaction*,struct strbuf*,char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void update_refs_stdin(struct ref_transaction *transaction)
{
	struct strbuf input = STRBUF_INIT;
	const char *next;

	if (strbuf_read(&input, 0, 1000) < 0)
		die_errno("could not read from stdin");
	next = input.buf;
	/* Read each line dispatch its command */
	while (next < input.buf + input.len) {
		if (*next == line_termination)
			die("empty command in input");
		else if (isspace(*next))
			die("whitespace before command: %s", next);
		else if (skip_prefix(next, "update ", &next))
			next = parse_cmd_update(transaction, &input, next);
		else if (skip_prefix(next, "create ", &next))
			next = parse_cmd_create(transaction, &input, next);
		else if (skip_prefix(next, "delete ", &next))
			next = parse_cmd_delete(transaction, &input, next);
		else if (skip_prefix(next, "verify ", &next))
			next = parse_cmd_verify(transaction, &input, next);
		else if (skip_prefix(next, "option ", &next))
			next = parse_cmd_option(&input, next);
		else
			die("unknown command: %s", next);

		next++;
	}

	strbuf_release(&input);
}