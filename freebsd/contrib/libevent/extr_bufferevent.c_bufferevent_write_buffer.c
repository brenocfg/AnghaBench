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
struct evbuffer {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int evbuffer_add_buffer (int /*<<< orphan*/ ,struct evbuffer*) ; 

int
bufferevent_write_buffer(struct bufferevent *bufev, struct evbuffer *buf)
{
	if (evbuffer_add_buffer(bufev->output, buf) == -1)
		return (-1);

	return 0;
}