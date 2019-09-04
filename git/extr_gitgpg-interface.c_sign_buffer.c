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
struct strbuf {size_t len; char* buf; } ;
struct child_process {int /*<<< orphan*/  args; } ;
struct TYPE_2__ {int /*<<< orphan*/  program; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char const*,int /*<<< orphan*/ *) ; 
 int error (int /*<<< orphan*/ ) ; 
 int pipe_command (struct child_process*,char*,size_t,struct strbuf*,int,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strstr (char*,char*) ; 
 TYPE_1__* use_format ; 

int sign_buffer(struct strbuf *buffer, struct strbuf *signature, const char *signing_key)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	int ret;
	size_t i, j, bottom;
	struct strbuf gpg_status = STRBUF_INIT;

	argv_array_pushl(&gpg.args,
			 use_format->program,
			 "--status-fd=2",
			 "-bsau", signing_key,
			 NULL);

	bottom = signature->len;

	/*
	 * When the username signingkey is bad, program could be terminated
	 * because gpg exits without reading and then write gets SIGPIPE.
	 */
	sigchain_push(SIGPIPE, SIG_IGN);
	ret = pipe_command(&gpg, buffer->buf, buffer->len,
			   signature, 1024, &gpg_status, 0);
	sigchain_pop(SIGPIPE);

	ret |= !strstr(gpg_status.buf, "\n[GNUPG:] SIG_CREATED ");
	strbuf_release(&gpg_status);
	if (ret)
		return error(_("gpg failed to sign the data"));

	/* Strip CR from the line endings, in case we are on Windows. */
	for (i = j = bottom; i < signature->len; i++)
		if (signature->buf[i] != '\r') {
			if (i != j)
				signature->buf[j] = signature->buf[i];
			j++;
		}
	strbuf_setlen(signature, j);

	return 0;
}