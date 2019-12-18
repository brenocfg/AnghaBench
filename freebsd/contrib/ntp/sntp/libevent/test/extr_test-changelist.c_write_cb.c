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
 int /*<<< orphan*/  event_add (struct event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_del (struct event*) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
write_cb(evutil_socket_t fd, short event, void *arg)
{
	printf("write callback. should only see this once\n");

	/* got what we want remove the event */
	event_del(*(struct event**)arg);

	/* opps changed my mind add it back again */
	event_add(*(struct event**)arg,NULL);

	/* not a good day for decisiveness, I really didn't want it after all */
	event_del(*(struct event**)arg);

}