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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct tempfile {TYPE_1__ filename; int /*<<< orphan*/  fd; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct gpg_format {int /*<<< orphan*/  verify_args; int /*<<< orphan*/  program; } ;
struct child_process {int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIG_IGN ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  argv_array_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argv_array_pushl (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  argv_array_pushv (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ close_tempfile_gently (struct tempfile*) ; 
 int /*<<< orphan*/  delete_tempfile (struct tempfile**) ; 
 int error_errno (int /*<<< orphan*/ ,...) ; 
 struct gpg_format* get_format_by_sig (char const*) ; 
 struct tempfile* mks_tempfile_t (char*) ; 
 int pipe_command (struct child_process*,char const*,size_t,struct strbuf*,int /*<<< orphan*/ ,struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigchain_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strstr (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,char const*,size_t) ; 

int verify_signed_buffer(const char *payload, size_t payload_size,
			 const char *signature, size_t signature_size,
			 struct strbuf *gpg_output, struct strbuf *gpg_status)
{
	struct child_process gpg = CHILD_PROCESS_INIT;
	struct gpg_format *fmt;
	struct tempfile *temp;
	int ret;
	struct strbuf buf = STRBUF_INIT;

	temp = mks_tempfile_t(".git_vtag_tmpXXXXXX");
	if (!temp)
		return error_errno(_("could not create temporary file"));
	if (write_in_full(temp->fd, signature, signature_size) < 0 ||
	    close_tempfile_gently(temp) < 0) {
		error_errno(_("failed writing detached signature to '%s'"),
			    temp->filename.buf);
		delete_tempfile(&temp);
		return -1;
	}

	fmt = get_format_by_sig(signature);
	if (!fmt)
		BUG("bad signature '%s'", signature);

	argv_array_push(&gpg.args, fmt->program);
	argv_array_pushv(&gpg.args, fmt->verify_args);
	argv_array_pushl(&gpg.args,
			 "--status-fd=1",
			 "--verify", temp->filename.buf, "-",
			 NULL);

	if (!gpg_status)
		gpg_status = &buf;

	sigchain_push(SIGPIPE, SIG_IGN);
	ret = pipe_command(&gpg, payload, payload_size,
			   gpg_status, 0, gpg_output, 0);
	sigchain_pop(SIGPIPE);

	delete_tempfile(&temp);

	ret |= !strstr(gpg_status->buf, "\n[GNUPG:] GOODSIG ");
	strbuf_release(&buf); /* no matter it was used or not */

	return ret;
}