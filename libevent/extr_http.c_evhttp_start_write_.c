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
struct evhttp_connection {int /*<<< orphan*/  state; int /*<<< orphan*/  bufev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVCON_WRITING ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evhttp_write_buffer (struct evhttp_connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evhttp_write_connectioncb ; 

void
evhttp_start_write_(struct evhttp_connection *evcon)
{
	bufferevent_disable(evcon->bufev, EV_WRITE);
	bufferevent_enable(evcon->bufev, EV_READ);

	evcon->state = EVCON_WRITING;
	evhttp_write_buffer(evcon, evhttp_write_connectioncb, NULL);
}