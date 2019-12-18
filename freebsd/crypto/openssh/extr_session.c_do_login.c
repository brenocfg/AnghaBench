#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_name; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  from ;
struct TYPE_8__ {scalar_t__ use_pam; int /*<<< orphan*/  use_dns; } ;
struct TYPE_7__ {TYPE_1__* authctxt; int /*<<< orphan*/  tty; struct passwd* pw; } ;
struct TYPE_6__ {scalar_t__ force_pwchange; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 scalar_t__ check_quietlogin (TYPE_2__*,char const*) ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_loginmsg () ; 
 int /*<<< orphan*/  do_motd () ; 
 int /*<<< orphan*/  do_pam_chauthtok () ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__ options ; 
 scalar_t__ packet_connection_is_on_socket () ; 
 int /*<<< orphan*/  packet_get_connection_in () ; 
 int /*<<< orphan*/  record_login (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  session_get_remote_name_or_ip (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_privsep ; 
 int /*<<< orphan*/  utmp_len ; 

void
do_login(struct ssh *ssh, Session *s, const char *command)
{
	socklen_t fromlen;
	struct sockaddr_storage from;
	struct passwd * pw = s->pw;
	pid_t pid = getpid();

	/*
	 * Get IP address of client. If the connection is not a socket, let
	 * the address be 0.0.0.0.
	 */
	memset(&from, 0, sizeof(from));
	fromlen = sizeof(from);
	if (packet_connection_is_on_socket()) {
		if (getpeername(packet_get_connection_in(),
		    (struct sockaddr *)&from, &fromlen) < 0) {
			debug("getpeername: %.100s", strerror(errno));
			cleanup_exit(255);
		}
	}

	/* Record that there was a login on that tty from the remote host. */
	if (!use_privsep)
		record_login(pid, s->tty, pw->pw_name, pw->pw_uid,
		    session_get_remote_name_or_ip(ssh, utmp_len,
		    options.use_dns),
		    (struct sockaddr *)&from, fromlen);

#ifdef USE_PAM
	/*
	 * If password change is needed, do it now.
	 * This needs to occur before the ~/.hushlogin check.
	 */
	if (options.use_pam && !use_privsep && s->authctxt->force_pwchange) {
		display_loginmsg();
		do_pam_chauthtok();
		s->authctxt->force_pwchange = 0;
		/* XXX - signal [net] parent to enable forwardings */
	}
#endif

	if (check_quietlogin(s, command))
		return;

	display_loginmsg();

	do_motd();
}