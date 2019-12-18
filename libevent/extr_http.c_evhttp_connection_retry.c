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
struct evhttp_connection {int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVCON_DISCONNECTED ; 
 int /*<<< orphan*/  evhttp_connection_connect_ (struct evhttp_connection*) ; 

__attribute__((used)) static void
evhttp_connection_retry(evutil_socket_t fd, short what, void *arg)
{
	struct evhttp_connection *evcon = arg;

	evcon->state = EVCON_DISCONNECTED;
	evhttp_connection_connect_(evcon);
}