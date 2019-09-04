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
struct strbuf {size_t len; int /*<<< orphan*/  buf; } ;
struct command {char* error_string; int /*<<< orphan*/  new_oid; int /*<<< orphan*/  ref_name; struct command* next; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  get_git_namespace () ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ref_is_hidden (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

__attribute__((used)) static void reject_updates_to_hidden(struct command *commands)
{
	struct strbuf refname_full = STRBUF_INIT;
	size_t prefix_len;
	struct command *cmd;

	strbuf_addstr(&refname_full, get_git_namespace());
	prefix_len = refname_full.len;

	for (cmd = commands; cmd; cmd = cmd->next) {
		if (cmd->error_string)
			continue;

		strbuf_setlen(&refname_full, prefix_len);
		strbuf_addstr(&refname_full, cmd->ref_name);

		if (!ref_is_hidden(cmd->ref_name, refname_full.buf))
			continue;
		if (is_null_oid(&cmd->new_oid))
			cmd->error_string = "deny deleting a hidden ref";
		else
			cmd->error_string = "deny updating a hidden ref";
	}

	strbuf_release(&refname_full);
}