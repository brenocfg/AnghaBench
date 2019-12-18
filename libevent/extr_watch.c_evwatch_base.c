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
struct evwatch {struct event_base* base; } ;
struct event_base {int dummy; } ;

/* Variables and functions */

struct event_base *
evwatch_base(struct evwatch *watcher)
{
	return watcher->base;
}