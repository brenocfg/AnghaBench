#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; } ;
struct TYPE_5__ {int used; struct pollfd* poll; } ;
struct TYPE_4__ {int used; struct pollfd* poll; } ;

/* Variables and functions */
 int EIO ; 
 TYPE_3__ current_poll ; 
 int need_poll (TYPE_1__*,int) ; 
 TYPE_1__ next_poll ; 
 int /*<<< orphan*/  sigio_lock () ; 
 int /*<<< orphan*/  sigio_unlock () ; 
 int /*<<< orphan*/  update_thread () ; 
 int write_sigio_pid ; 

int ignore_sigio_fd(int fd)
{
	struct pollfd *p;
	int err = 0, i, n = 0;

	/*
	 * This is called from exitcalls elsewhere in UML - if
	 * sigio_cleanup has already run, then update_thread will hang
	 * or fail because the thread is no longer running.
	 */
	if (write_sigio_pid == -1)
		return -EIO;

	sigio_lock();
	for (i = 0; i < current_poll.used; i++) {
		if (current_poll.poll[i].fd == fd)
			break;
	}
	if (i == current_poll.used)
		goto out;

	err = need_poll(&next_poll, current_poll.used - 1);
	if (err)
		goto out;

	for (i = 0; i < current_poll.used; i++) {
		p = &current_poll.poll[i];
		if (p->fd != fd)
			next_poll.poll[n++] = *p;
	}
	next_poll.used = current_poll.used - 1;

	update_thread();
 out:
	sigio_unlock();
	return err;
}