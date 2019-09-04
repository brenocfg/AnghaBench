#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  buf; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct hostinfo {TYPE_2__ tcp_port; TYPE_1__ hostname; } ;
struct daemon_service {int /*<<< orphan*/  name; } ;
struct child_process {int use_shell; char const** argv; int no_stdin; int no_stderr; int out; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int /*<<< orphan*/  EACCES ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  access_hook ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  daemon_error (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ finish_command (struct child_process*) ; 
 int /*<<< orphan*/  get_canon_hostname (struct hostinfo*) ; 
 int /*<<< orphan*/  get_ip_address (struct hostinfo*) ; 
 int /*<<< orphan*/  logerror (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ start_command (struct child_process*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_ltrim (struct strbuf*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int run_access_hook(struct daemon_service *service, const char *dir,
			   const char *path, struct hostinfo *hi)
{
	struct child_process child = CHILD_PROCESS_INIT;
	struct strbuf buf = STRBUF_INIT;
	const char *argv[8];
	const char **arg = argv;
	char *eol;
	int seen_errors = 0;

	*arg++ = access_hook;
	*arg++ = service->name;
	*arg++ = path;
	*arg++ = hi->hostname.buf;
	*arg++ = get_canon_hostname(hi);
	*arg++ = get_ip_address(hi);
	*arg++ = hi->tcp_port.buf;
	*arg = NULL;

	child.use_shell = 1;
	child.argv = argv;
	child.no_stdin = 1;
	child.no_stderr = 1;
	child.out = -1;
	if (start_command(&child)) {
		logerror("daemon access hook '%s' failed to start",
			 access_hook);
		goto error_return;
	}
	if (strbuf_read(&buf, child.out, 0) < 0) {
		logerror("failed to read from pipe to daemon access hook '%s'",
			 access_hook);
		strbuf_reset(&buf);
		seen_errors = 1;
	}
	if (close(child.out) < 0) {
		logerror("failed to close pipe to daemon access hook '%s'",
			 access_hook);
		seen_errors = 1;
	}
	if (finish_command(&child))
		seen_errors = 1;

	if (!seen_errors) {
		strbuf_release(&buf);
		return 0;
	}

error_return:
	strbuf_ltrim(&buf);
	if (!buf.len)
		strbuf_addstr(&buf, "service rejected");
	eol = strchr(buf.buf, '\n');
	if (eol)
		*eol = '\0';
	errno = EACCES;
	daemon_error(dir, buf.buf);
	strbuf_release(&buf);
	return -1;
}