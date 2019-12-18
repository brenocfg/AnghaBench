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
struct evhttp {struct bufferevent* (* bevcb ) (struct event_base*,void*) ;void* bevcbarg; } ;

/* Variables and functions */

void
evhttp_set_bevcb(struct evhttp *http,
    struct bufferevent* (*cb)(struct event_base *, void *), void *cbarg)
{
	http->bevcb = cb;
	http->bevcbarg = cbarg;
}