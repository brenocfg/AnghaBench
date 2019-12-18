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
struct evbuffer_ptr {int dummy; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 struct evbuffer_ptr evbuffer_search_range (struct evbuffer*,char const*,size_t,struct evbuffer_ptr const*,int /*<<< orphan*/ *) ; 

struct evbuffer_ptr
evbuffer_search(struct evbuffer *buffer, const char *what, size_t len, const struct evbuffer_ptr *start)
{
	return evbuffer_search_range(buffer, what, len, start, NULL);
}