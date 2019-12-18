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
struct bufferevent {int /*<<< orphan*/  input; } ;

/* Variables and functions */
 int evbuffer_add_buffer (struct evbuffer*,int /*<<< orphan*/ ) ; 

int
bufferevent_read_buffer(struct bufferevent *bufev, struct evbuffer *buf)
{
	return (evbuffer_add_buffer(buf, bufev->input));
}