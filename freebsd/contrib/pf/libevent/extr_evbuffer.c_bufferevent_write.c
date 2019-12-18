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
struct bufferevent {int enabled; int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  ev_write; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int evbuffer_add (int /*<<< orphan*/ ,void*,size_t) ; 

int
bufferevent_write(struct bufferevent *bufev, void *data, size_t size)
{
	int res;

	res = evbuffer_add(bufev->output, data, size);

	if (res == -1)
		return (res);

	/* If everything is okay, we need to schedule a write */
	if (size > 0 && (bufev->enabled & EV_WRITE))
		bufferevent_add(&bufev->ev_write, bufev->timeout_write);

	return (res);
}