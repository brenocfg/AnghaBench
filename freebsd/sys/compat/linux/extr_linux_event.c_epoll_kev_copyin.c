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
struct kevent {int dummy; } ;
struct epoll_copyin_args {int changelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct kevent*,int,int) ; 

__attribute__((used)) static int
epoll_kev_copyin(void *arg, struct kevent *kevp, int count)
{
	struct epoll_copyin_args *args;

	args = (struct epoll_copyin_args*) arg;

	memcpy(kevp, args->changelist, count * sizeof(*kevp));
	args->changelist += count;

	return (0);
}