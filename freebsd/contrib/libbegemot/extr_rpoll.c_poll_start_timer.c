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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  timer_f ;

/* Variables and functions */
 int poll_start_utimer (unsigned long long,int,int /*<<< orphan*/ ,void*) ; 

int
poll_start_timer(u_int msecs, int repeat, timer_f func, void *arg)
{
	return (poll_start_utimer((unsigned long long)msecs * 1000,
	    repeat, func, arg));
}