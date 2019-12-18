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
struct evhttp_connection {struct event_base* base; } ;
struct event_base {int dummy; } ;

/* Variables and functions */

struct event_base *
evhttp_connection_get_base(struct evhttp_connection *conn)
{
	return conn->base;
}