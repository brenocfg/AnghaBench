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
struct evbuffer {int dummy; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int evbuffer_write_atmost (struct evbuffer*,int /*<<< orphan*/ ,int) ; 

int
evbuffer_write(struct evbuffer *buffer, evutil_socket_t fd)
{
	return evbuffer_write_atmost(buffer, fd, -1);
}