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
 int /*<<< orphan*/  RECV_INIT ; 
 int /*<<< orphan*/ * addremove_io_fd ; 
 int /*<<< orphan*/  init_io_completion_port () ; 
 int /*<<< orphan*/  init_recvbuff (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_handler ; 
 int interface_interval ; 
 int /*<<< orphan*/  ntpd_addremove_io_fd ; 
 int /*<<< orphan*/  set_signal (int /*<<< orphan*/ ) ; 

void
init_io(void)
{
	/* Init buffer free list and stat counters */
	init_recvbuff(RECV_INIT);
	/* update interface every 5 minutes as default */
	interface_interval = 300;

#ifdef WORK_PIPE
	addremove_io_fd = &ntpd_addremove_io_fd;
#endif

#if defined(SYS_WINNT)
	init_io_completion_port();
#elif defined(HAVE_SIGNALED_IO)
	(void) set_signal(input_handler);
#endif
}