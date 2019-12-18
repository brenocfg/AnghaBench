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
struct evhttp_connection {scalar_t__ max_headers_size; } ;
typedef  scalar_t__ ev_ssize_t ;

/* Variables and functions */
 scalar_t__ EV_SIZE_MAX ; 

void
evhttp_connection_set_max_headers_size(struct evhttp_connection *evcon,
    ev_ssize_t new_max_headers_size)
{
	if (new_max_headers_size<0)
		evcon->max_headers_size = EV_SIZE_MAX;
	else
		evcon->max_headers_size = new_max_headers_size;
}