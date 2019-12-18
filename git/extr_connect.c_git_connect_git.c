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
struct child_process {int dummy; } ;
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 struct child_process* git_proxy_connect (int*,char*) ; 
 struct child_process* git_tcp_connect (int*,char*,int) ; 
 scalar_t__ git_use_proxy (char*) ; 
 int /*<<< orphan*/  packet_write (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  transport_check_allowed (char*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static struct child_process *git_connect_git(int fd[2], char *hostandport,
					     const char *path, const char *prog,
					     enum protocol_version version,
					     int flags)
{
	struct child_process *conn;
	struct strbuf request = STRBUF_INIT;
	/*
	 * Set up virtual host information based on where we will
	 * connect, unless the user has overridden us in
	 * the environment.
	 */
	char *target_host = getenv("GIT_OVERRIDE_VIRTUAL_HOST");
	if (target_host)
		target_host = xstrdup(target_host);
	else
		target_host = xstrdup(hostandport);

	transport_check_allowed("git");

	/*
	 * These underlying connection commands die() if they
	 * cannot connect.
	 */
	if (git_use_proxy(hostandport))
		conn = git_proxy_connect(fd, hostandport);
	else
		conn = git_tcp_connect(fd, hostandport, flags);
	/*
	 * Separate original protocol components prog and path
	 * from extended host header with a NUL byte.
	 *
	 * Note: Do not add any other headers here!  Doing so
	 * will cause older git-daemon servers to crash.
	 */
	strbuf_addf(&request,
		    "%s %s%chost=%s%c",
		    prog, path, 0,
		    target_host, 0);

	/* If using a new version put that stuff here after a second null byte */
	if (version > 0) {
		strbuf_addch(&request, '\0');
		strbuf_addf(&request, "version=%d%c",
			    version, '\0');
	}

	packet_write(fd[1], request.buf, request.len);

	free(target_host);
	strbuf_release(&request);
	return conn;
}