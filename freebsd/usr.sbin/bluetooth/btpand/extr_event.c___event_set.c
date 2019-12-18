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
struct event {int fd; short flags; void (* cb ) (int,short,void*) ;void* cbarg; } ;

/* Variables and functions */

void
__event_set(struct event *ev, int fd, short flags,
	void (*cb)(int, short, void *), void *cbarg)
{
	ev->fd = fd;
	ev->flags = flags;
	ev->cb = cb;
	ev->cbarg = cbarg;
}