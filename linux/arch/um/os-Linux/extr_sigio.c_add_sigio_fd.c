#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int fd; } ;
struct TYPE_9__ {int used; struct pollfd* poll; } ;
struct TYPE_8__ {int used; TYPE_3__* poll; } ;
struct TYPE_7__ {int fd; } ;
struct TYPE_6__ {int used; struct pollfd* poll; } ;

/* Variables and functions */
 TYPE_5__ all_sigio_fds ; 
 TYPE_4__ current_poll ; 
 int /*<<< orphan*/  memcpy (struct pollfd*,TYPE_3__*,int) ; 
 int need_poll (TYPE_1__*,int) ; 
 TYPE_1__ next_poll ; 
 int /*<<< orphan*/  sigio_lock () ; 
 int /*<<< orphan*/  sigio_unlock () ; 
 int /*<<< orphan*/  update_thread () ; 

int add_sigio_fd(int fd)
{
	struct pollfd *p;
	int err = 0, i, n;

	sigio_lock();
	for (i = 0; i < all_sigio_fds.used; i++) {
		if (all_sigio_fds.poll[i].fd == fd)
			break;
	}
	if (i == all_sigio_fds.used)
		goto out;

	p = &all_sigio_fds.poll[i];

	for (i = 0; i < current_poll.used; i++) {
		if (current_poll.poll[i].fd == fd)
			goto out;
	}

	n = current_poll.used;
	err = need_poll(&next_poll, n + 1);
	if (err)
		goto out;

	memcpy(next_poll.poll, current_poll.poll,
	       current_poll.used * sizeof(struct pollfd));
	next_poll.poll[n] = *p;
	next_poll.used = n + 1;
	update_thread();
 out:
	sigio_unlock();
	return err;
}