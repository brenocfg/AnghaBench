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
struct event {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int called ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int event_get_signal (struct event*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
signal_cb(evutil_socket_t fd, short event, void *arg)
{
	struct event *signal = arg;

	printf("signal_cb: got signal %d\n", event_get_signal(signal));

	if (called >= 2)
		event_del(signal);

	called++;
}