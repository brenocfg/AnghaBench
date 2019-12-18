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
 scalar_t__ PORT1 ; 
 scalar_t__ PORT2 ; 
 int /*<<< orphan*/  close_both (int*) ; 
 int /*<<< orphan*/  setup_fifo (char*,int*) ; 
 int /*<<< orphan*/  setup_pipe (char*,int*) ; 
 int /*<<< orphan*/  setup_tcp (char*,int*,scalar_t__) ; 
 int /*<<< orphan*/  setup_udp (char*,int*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  setup_udsdgram (char*,int*) ; 
 int /*<<< orphan*/  setup_udsstream (char*,int*) ; 
 int /*<<< orphan*/  try_0send (char*,int) ; 
 int /*<<< orphan*/  try_0write (char*,int) ; 

int
main(void)
{
	int fd[2];

	setup_udp("udp_0send", fd, PORT1, PORT2);
	try_0send("udp_0send", fd[0]);
	close_both(fd);

	setup_udp("udp_0write", fd, PORT1 + 10, PORT2 + 10);
	try_0write("udp_0write", fd[0]);
	close_both(fd);

	setup_tcp("tcp_0send", fd, PORT1);
	try_0send("tcp_0send", fd[0]);
	close_both(fd);

	setup_tcp("tcp_0write", fd, PORT1 + 10);
	try_0write("tcp_0write", fd[0]);
	close_both(fd);

	setup_udsstream("udsstream_0send", fd);
	try_0send("udsstream_0send", fd[0]);
	close_both(fd);

	setup_udsstream("udsstream_0write", fd);
	try_0write("udsstream_0write", fd[0]);
	close_both(fd);

	setup_udsdgram("udsdgram_0send", fd);
	try_0send("udsdgram_0send", fd[0]);
	close_both(fd);

	setup_udsdgram("udsdgram_0write", fd);
	try_0write("udsdgram_0write", fd[0]);
	close_both(fd);

	setup_pipe("pipe_0write", fd);
	try_0write("pipd_0write", fd[0]);
	close_both(fd);

	setup_fifo("fifo_0write", fd);
	try_0write("fifo_0write", fd[0]);
	close_both(fd);

	return (0);
}