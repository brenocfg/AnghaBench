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
struct child_process {char const** argv; int err; int stdout_to_stderr; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int error (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  finish_command (struct child_process*) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  starts_with (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strbuf_read (struct strbuf*,int,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int check_emacsclient_version(void)
{
	struct strbuf buffer = STRBUF_INIT;
	struct child_process ec_process = CHILD_PROCESS_INIT;
	const char *argv_ec[] = { "emacsclient", "--version", NULL };
	int version;

	/* emacsclient prints its version number on stderr */
	ec_process.argv = argv_ec;
	ec_process.err = -1;
	ec_process.stdout_to_stderr = 1;
	if (start_command(&ec_process))
		return error(_("Failed to start emacsclient."));

	strbuf_read(&buffer, ec_process.err, 20);
	close(ec_process.err);

	/*
	 * Don't bother checking return value, because "emacsclient --version"
	 * seems to always exits with code 1.
	 */
	finish_command(&ec_process);

	if (!starts_with(buffer.buf, "emacsclient")) {
		strbuf_release(&buffer);
		return error(_("Failed to parse emacsclient version."));
	}

	strbuf_remove(&buffer, 0, strlen("emacsclient"));
	version = atoi(buffer.buf);

	if (version < 22) {
		strbuf_release(&buffer);
		return error(_("emacsclient version '%d' too old (< 22)."),
			version);
	}

	strbuf_release(&buffer);
	return 0;
}