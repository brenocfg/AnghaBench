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
struct bufferevent {int dummy; } ;

/* Variables and functions */

struct bufferevent* evhttp_connection_get_bufferevent(struct evhttp_connection *evcon)
{
	return evcon->bufev;
}