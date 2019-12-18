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
struct timespec {int dummy; } ;
struct kevent {int dummy; } ;

/* Variables and functions */
 size_t INTERPOS_kevent ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (int,struct kevent const*,int,struct kevent*,int,struct timespec const*) ; 

int
kevent(int kq, const struct kevent *changelist, int nchanges,
    struct kevent *eventlist, int nevents, const struct timespec *timeout)
{

	return (((int (*)(int, const struct kevent *, int,
	    struct kevent *, int, const struct timespec *))
	    __libc_interposing[INTERPOS_kevent])(kq, changelist, nchanges,
	   eventlist, nevents, timeout));
}