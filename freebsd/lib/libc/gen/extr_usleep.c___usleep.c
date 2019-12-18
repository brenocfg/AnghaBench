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
typedef  int useconds_t ;
typedef  struct timespec {int tv_nsec; int tv_sec; } const timespec ;

/* Variables and functions */
 size_t INTERPOS_nanosleep ; 
 scalar_t__* __libc_interposing ; 
 int stub1 (struct timespec const*,struct timespec const*) ; 

int
__usleep(useconds_t useconds)
{
	struct timespec time_to_sleep;

	time_to_sleep.tv_nsec = (useconds % 1000000) * 1000;
	time_to_sleep.tv_sec = useconds / 1000000;
	return (((int (*)(const struct timespec *, struct timespec *))
	    __libc_interposing[INTERPOS_nanosleep])(&time_to_sleep, NULL));
}