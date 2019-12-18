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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup_exit (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  packet_process_incoming (char*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  ssh_remote_ipaddr (struct ssh*) ; 
 int /*<<< orphan*/  ssh_remote_port (struct ssh*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int
process_input(struct ssh *ssh, fd_set *readset, int connection_in)
{
	int len;
	char buf[16384];

	/* Read and buffer any input data from the client. */
	if (FD_ISSET(connection_in, readset)) {
		len = read(connection_in, buf, sizeof(buf));
		if (len == 0) {
			verbose("Connection closed by %.100s port %d",
			    ssh_remote_ipaddr(ssh), ssh_remote_port(ssh));
			return -1;
		} else if (len < 0) {
			if (errno != EINTR && errno != EAGAIN &&
			    errno != EWOULDBLOCK) {
				verbose("Read error from remote host "
				    "%.100s port %d: %.100s",
				    ssh_remote_ipaddr(ssh),
				    ssh_remote_port(ssh), strerror(errno));
				cleanup_exit(255);
			}
		} else {
			/* Buffer any received data. */
			packet_process_incoming(buf, len);
		}
	}
	return 0;
}