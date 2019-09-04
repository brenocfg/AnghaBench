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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct child_process {char const** argv; int no_stdin; int out; int git_cmd; scalar_t__ err; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 scalar_t__ finish_command (struct child_process*) ; 
 char* oid_to_hex (struct object_id const*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_commented_object(int fd, const struct object_id *object)
{
	const char *show_args[5] =
		{"show", "--stat", "--no-notes", oid_to_hex(object), NULL};
	struct child_process show = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	struct strbuf cbuf = STRBUF_INIT;

	/* Invoke "git show --stat --no-notes $object" */
	show.argv = show_args;
	show.no_stdin = 1;
	show.out = -1;
	show.err = 0;
	show.git_cmd = 1;
	if (start_command(&show))
		die(_("unable to start 'show' for object '%s'"),
		    oid_to_hex(object));

	if (strbuf_read(&buf, show.out, 0) < 0)
		die_errno(_("could not read 'show' output"));
	strbuf_add_commented_lines(&cbuf, buf.buf, buf.len);
	write_or_die(fd, cbuf.buf, cbuf.len);

	strbuf_release(&cbuf);
	strbuf_release(&buf);

	if (finish_command(&show))
		die(_("failed to finish 'show' for object '%s'"),
		    oid_to_hex(object));
}