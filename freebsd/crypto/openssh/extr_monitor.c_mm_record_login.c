#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssh {int dummy; } ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
struct passwd {int /*<<< orphan*/  pw_uid; int /*<<< orphan*/  pw_name; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  from ;
struct TYPE_5__ {int /*<<< orphan*/  use_dns; } ;
struct TYPE_4__ {int /*<<< orphan*/  tty; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 struct ssh* active_state ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ getpeername (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_storage*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ options ; 
 scalar_t__ packet_connection_is_on_socket () ; 
 int /*<<< orphan*/  packet_get_connection_in () ; 
 int /*<<< orphan*/  record_login (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  session_get_remote_name_or_ip (struct ssh*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utmp_len ; 

__attribute__((used)) static void
mm_record_login(Session *s, struct passwd *pw)
{
	struct ssh *ssh = active_state;	/* XXX */
	socklen_t fromlen;
	struct sockaddr_storage from;

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
	record_login(s->pid, s->tty, pw->pw_name, pw->pw_uid,
	    session_get_remote_name_or_ip(ssh, utmp_len, options.use_dns),
	    (struct sockaddr *)&from, fromlen);
}