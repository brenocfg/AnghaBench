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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LARGE_PACKET_MAX ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_clnt (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  send_sideband (int,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static ssize_t process_input(int child_fd, int band)
{
	char buf[16384];
	ssize_t sz = read(child_fd, buf, sizeof(buf));
	if (sz < 0) {
		if (errno != EAGAIN && errno != EINTR)
			error_clnt("read error: %s\n", strerror(errno));
		return sz;
	}
	send_sideband(1, band, buf, sz, LARGE_PACKET_MAX);
	return sz;
}