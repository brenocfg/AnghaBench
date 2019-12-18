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
 int /*<<< orphan*/  event_loopexit (struct timeval*) ; 

__attribute__((used)) static void
child_signal_cb(evutil_socket_t fd, short event, void *arg)
{
	struct timeval tv;
	int *pint = arg;

	*pint = 1;

	tv.tv_usec = 500000;
	tv.tv_sec = 0;
	event_loopexit(&tv);
}