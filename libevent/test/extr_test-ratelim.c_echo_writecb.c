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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_enable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 struct evbuffer* bufferevent_get_output (struct bufferevent*) ; 
 int evbuffer_get_length (struct evbuffer*) ; 

__attribute__((used)) static void
echo_writecb(struct bufferevent *bev, void *ctx)
{
	struct evbuffer *output = bufferevent_get_output(bev);
	if (evbuffer_get_length(output) < 512000)
		bufferevent_enable(bev, EV_READ);
}