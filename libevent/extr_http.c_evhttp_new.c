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
struct evhttp {struct event_base* base; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 struct evhttp* evhttp_new_object () ; 

struct evhttp *
evhttp_new(struct event_base *base)
{
	struct evhttp *http = NULL;

	http = evhttp_new_object();
	if (http == NULL)
		return (NULL);
	http->base = base;

	return (http);
}