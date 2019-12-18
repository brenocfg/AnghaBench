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
struct transport {struct helper_data* data; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct helper_data {int no_disconnect_req; } ;
struct child_process {int /*<<< orphan*/  out; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _IONBF ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 struct child_process* get_helper (struct transport*) ; 
 scalar_t__ recvline_fh (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  sendline (struct helper_data*,struct strbuf*) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * xfdopen (int,char*) ; 

__attribute__((used)) static int run_connect(struct transport *transport, struct strbuf *cmdbuf)
{
	struct helper_data *data = transport->data;
	int ret = 0;
	int duped;
	FILE *input;
	struct child_process *helper;

	helper = get_helper(transport);

	/*
	 * Yes, dup the pipe another time, as we need unbuffered version
	 * of input pipe as FILE*. fclose() closes the underlying fd and
	 * stream buffering only can be changed before first I/O operation
	 * on it.
	 */
	duped = dup(helper->out);
	if (duped < 0)
		die_errno(_("can't dup helper output fd"));
	input = xfdopen(duped, "r");
	setvbuf(input, NULL, _IONBF, 0);

	sendline(data, cmdbuf);
	if (recvline_fh(input, cmdbuf))
		exit(128);

	if (!strcmp(cmdbuf->buf, "")) {
		data->no_disconnect_req = 1;
		if (debug)
			fprintf(stderr, "Debug: Smart transport connection "
				"ready.\n");
		ret = 1;
	} else if (!strcmp(cmdbuf->buf, "fallback")) {
		if (debug)
			fprintf(stderr, "Debug: Falling back to dumb "
				"transport.\n");
	} else {
		die(_("unknown response to connect: %s"),
		    cmdbuf->buf);
	}

	fclose(input);
	return ret;
}