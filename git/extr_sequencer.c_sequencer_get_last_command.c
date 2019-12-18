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
struct strbuf {char* buf; } ;
struct repository {int dummy; } ;
typedef  enum replay_action { ____Placeholder_replay_action } replay_action ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int REPLAY_PICK ; 
 int REPLAY_REVERT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  TODO_PICK ; 
 int /*<<< orphan*/  TODO_REVERT ; 
 scalar_t__ errno ; 
 int error_errno (char*,char const*) ; 
 char* git_path_todo_file () ; 
 scalar_t__ is_command (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int strspn (char*,char*) ; 

int sequencer_get_last_command(struct repository *r, enum replay_action *action)
{
	const char *todo_file, *bol;
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;

	todo_file = git_path_todo_file();
	if (strbuf_read_file(&buf, todo_file, 0) < 0) {
		if (errno == ENOENT || errno == ENOTDIR)
			return -1;
		else
			return error_errno("unable to open '%s'", todo_file);
	}
	bol = buf.buf + strspn(buf.buf, " \t\r\n");
	if (is_command(TODO_PICK, &bol) && (*bol == ' ' || *bol == '\t'))
		*action = REPLAY_PICK;
	else if (is_command(TODO_REVERT, &bol) &&
		 (*bol == ' ' || *bol == '\t'))
		*action = REPLAY_REVERT;
	else
		ret = -1;

	strbuf_release(&buf);

	return ret;
}