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

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int MSG_DONTWAIT ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 scalar_t__ buffer_size ; 
 int flags ; 
 int /*<<< orphan*/  rs_fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static void set_options(int fd)
{
	int val;

	if (buffer_size) {
		rs_setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *) &buffer_size,
			      sizeof buffer_size);
		rs_setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *) &buffer_size,
			      sizeof buffer_size);
	} else {
		val = 1 << 19;
		rs_setsockopt(fd, SOL_SOCKET, SO_SNDBUF, (void *) &val, sizeof val);
		rs_setsockopt(fd, SOL_SOCKET, SO_RCVBUF, (void *) &val, sizeof val);
	}

	if (flags & MSG_DONTWAIT)
		rs_fcntl(fd, F_SETFL, O_NONBLOCK);
}