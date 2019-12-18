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
struct evhttp_connection {scalar_t__ state; int /*<<< orphan*/  bind_port; } ;
typedef  int /*<<< orphan*/  ev_uint16_t ;

/* Variables and functions */
 scalar_t__ EVCON_DISCONNECTED ; 
 int /*<<< orphan*/  EVUTIL_ASSERT (int) ; 

void
evhttp_connection_set_local_port(struct evhttp_connection *evcon,
    ev_uint16_t port)
{
	EVUTIL_ASSERT(evcon->state == EVCON_DISCONNECTED);
	evcon->bind_port = port;
}