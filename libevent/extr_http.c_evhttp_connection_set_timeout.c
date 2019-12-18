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
struct evhttp_connection {int /*<<< orphan*/  timeout_write; int /*<<< orphan*/  timeout_read; int /*<<< orphan*/  bufev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_CON_TIMEOUT_ADJUSTED ; 
 int /*<<< orphan*/  HTTP_READ_TIMEOUT ; 
 int /*<<< orphan*/  HTTP_WRITE_TIMEOUT ; 
 int /*<<< orphan*/  bufferevent_set_timeouts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_set_timeout_ (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void
evhttp_connection_set_timeout(struct evhttp_connection *evcon,
    int timeout)
{
	if (timeout != -1) {
		evcon->flags |= EVHTTP_CON_TIMEOUT_ADJUSTED;
	} else {
		evcon->flags &= ~EVHTTP_CON_TIMEOUT_ADJUSTED;
	}
	evhttp_set_timeout_(&evcon->timeout_read,  timeout, HTTP_READ_TIMEOUT);
	evhttp_set_timeout_(&evcon->timeout_write, timeout, HTTP_WRITE_TIMEOUT);
	bufferevent_set_timeouts(evcon->bufev,
	    &evcon->timeout_read, &evcon->timeout_write);
}