#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ request_tty; int /*<<< orphan*/ * control_path; } ;

/* Variables and functions */
 scalar_t__ REQUEST_TTY_FORCE ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  leave_non_blocking () ; 
 int /*<<< orphan*/  leave_raw_mode (int) ; 
 int muxserver_sock ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  ssh_kill_proxy_command () ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ *) ; 

void
cleanup_exit(int i)
{
	leave_raw_mode(options.request_tty == REQUEST_TTY_FORCE);
	leave_non_blocking();
	if (options.control_path != NULL && muxserver_sock != -1)
		unlink(options.control_path);
	ssh_kill_proxy_command();
	_exit(i);
}