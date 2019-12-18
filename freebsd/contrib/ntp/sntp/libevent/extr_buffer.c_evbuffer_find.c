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
struct evbuffer_ptr {scalar_t__ pos; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 unsigned char* evbuffer_pullup (struct evbuffer*,scalar_t__) ; 
 struct evbuffer_ptr evbuffer_search (struct evbuffer*,char const*,size_t,int /*<<< orphan*/ *) ; 

unsigned char *
evbuffer_find(struct evbuffer *buffer, const unsigned char *what, size_t len)
{
	unsigned char *search;
	struct evbuffer_ptr ptr;

	EVBUFFER_LOCK(buffer);

	ptr = evbuffer_search(buffer, (const char *)what, len, NULL);
	if (ptr.pos < 0) {
		search = NULL;
	} else {
		search = evbuffer_pullup(buffer, ptr.pos + len);
		if (search)
			search += ptr.pos;
	}
	EVBUFFER_UNLOCK(buffer);
	return search;
}