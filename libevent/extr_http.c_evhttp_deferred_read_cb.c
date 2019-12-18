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
struct evhttp_connection {struct bufferevent* bufev; } ;
struct event_callback {int dummy; } ;
struct bufferevent {int /*<<< orphan*/  (* readcb ) (struct bufferevent*,struct evhttp_connection*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bufferevent*,struct evhttp_connection*) ; 

__attribute__((used)) static void
evhttp_deferred_read_cb(struct event_callback *cb, void *data)
{
	struct evhttp_connection *evcon = data;
	struct bufferevent *bev = evcon->bufev;
	if (bev->readcb)
		(bev->readcb)(evcon->bufev, evcon);
}