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
struct evhttp_connection {scalar_t__ state; int /*<<< orphan*/  bufev; struct event_base* base; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 scalar_t__ EVCON_DISCONNECTED ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 
 int /*<<< orphan*/  bufferevent_base_set (struct event_base*,int /*<<< orphan*/ ) ; 

void
evhttp_connection_set_base(struct evhttp_connection *evcon,
    struct event_base *base)
{
	EVUTIL_ASSERT(evcon->base == NULL);
	EVUTIL_ASSERT(evcon->state == EVCON_DISCONNECTED);
	evcon->base = base;
	bufferevent_base_set(base, evcon->bufev);
}