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
struct sockaddr {int dummy; } ;
struct evhttp_connection {int /*<<< orphan*/  bufev; } ;

/* Variables and functions */
 struct sockaddr const* bufferevent_socket_get_conn_address_ (int /*<<< orphan*/ ) ; 

const struct sockaddr*
evhttp_connection_get_addr(struct evhttp_connection *evcon)
{
	return bufferevent_socket_get_conn_address_(evcon->bufev);
}