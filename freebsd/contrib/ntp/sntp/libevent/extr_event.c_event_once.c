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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  current_base ; 
 int event_base_once (int /*<<< orphan*/ ,int /*<<< orphan*/ ,short,void (*) (int /*<<< orphan*/ ,short,void*),void*,struct timeval const*) ; 

int
event_once(evutil_socket_t fd, short events,
    void (*callback)(evutil_socket_t, short, void *),
    void *arg, const struct timeval *tv)
{
	return event_base_once(current_base, fd, events, callback, arg, tv);
}