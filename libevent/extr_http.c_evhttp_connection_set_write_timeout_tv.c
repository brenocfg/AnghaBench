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
struct timeval {int dummy; } ;
struct evhttp_connection {scalar_t__ state; int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  bufev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ EVCON_CONNECTING ; 
 int /*<<< orphan*/  EVHTTP_CON_TIMEOUT_ADJUSTED ; 
 int /*<<< orphan*/  bufferevent_set_timeouts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_set_timeout_tv_ (int /*<<< orphan*/ *,struct timeval const*,int) ; 

void evhttp_connection_set_write_timeout_tv(struct evhttp_connection *evcon,
    const struct timeval *tv)
{
	evcon->flags |= EVHTTP_CON_TIMEOUT_ADJUSTED;
	evhttp_set_timeout_tv_(&evcon->timeout_write, tv, -1);
	if (evcon->state != EVCON_CONNECTING)
		bufferevent_set_timeouts(evcon->bufev,
		    &evcon->timeout_read, &evcon->timeout_write);
}