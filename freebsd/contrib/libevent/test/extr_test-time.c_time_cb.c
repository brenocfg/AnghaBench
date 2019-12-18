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
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int NEVENT ; 
 int called ; 
 int /*<<< orphan*/ * ev ; 
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ ,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ ) ; 
 void* rand_int (int) ; 

__attribute__((used)) static void
time_cb(evutil_socket_t fd, short event, void *arg)
{
	struct timeval tv;
	int i, j;

	called++;

	if (called < 10*NEVENT) {
		for (i = 0; i < 10; i++) {
			j = rand_int(NEVENT);
			tv.tv_sec = 0;
			tv.tv_usec = rand_int(50000);
			if (tv.tv_usec % 2 || called < NEVENT)
				evtimer_add(ev[j], &tv);
			else
				evtimer_del(ev[j]);
		}
	}
}