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
struct ssh {int dummy; } ;

/* Variables and functions */
 scalar_t__ STDERR_FILENO ; 
 int /*<<< orphan*/  channel_close_all (struct ssh*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (scalar_t__) ; 
 int /*<<< orphan*/  endpwent () ; 
 int packet_get_connection_in () ; 
 int packet_get_connection_out () ; 

__attribute__((used)) static void
child_close_fds(struct ssh *ssh)
{
	extern int auth_sock;

	if (auth_sock != -1) {
		close(auth_sock);
		auth_sock = -1;
	}

	if (packet_get_connection_in() == packet_get_connection_out())
		close(packet_get_connection_in());
	else {
		close(packet_get_connection_in());
		close(packet_get_connection_out());
	}
	/*
	 * Close all descriptors related to channels.  They will still remain
	 * open in the parent.
	 */
	/* XXX better use close-on-exec? -markus */
	channel_close_all(ssh);

	/*
	 * Close any extra file descriptors.  Note that there may still be
	 * descriptors left by system functions.  They will be closed later.
	 */
	endpwent();

	/*
	 * Close any extra open file descriptors so that we don't have them
	 * hanging around in clients.  Note that we want to do this after
	 * initgroups, because at least on Solaris 2.3 it leaves file
	 * descriptors open.
	 */
	closefrom(STDERR_FILENO + 1);
}