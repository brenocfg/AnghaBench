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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evutil_gettimeofday (void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit_base ; 
 void* times ; 

__attribute__((used)) static void
note_time_cb(evutil_socket_t fd, short what, void *arg)
{
	evutil_gettimeofday(arg, NULL);
	if (arg == &times[4]) {
		event_base_loopbreak(exit_base);
	}
}