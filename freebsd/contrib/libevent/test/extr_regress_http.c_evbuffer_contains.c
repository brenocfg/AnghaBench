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
struct evbuffer_ptr {int pos; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 struct evbuffer_ptr evbuffer_search (struct evbuffer*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
evbuffer_contains(struct evbuffer *buf, const char *s)
{
	struct evbuffer_ptr ptr;
	ptr = evbuffer_search(buf, s, strlen(s), NULL);
	return ptr.pos != -1;
}