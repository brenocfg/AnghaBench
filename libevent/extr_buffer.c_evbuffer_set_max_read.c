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
struct evbuffer {size_t max_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 size_t INT_MAX ; 

int evbuffer_set_max_read(struct evbuffer *buf, size_t max)
{
	if (max > INT_MAX) {
		return -1;
	}

	EVBUFFER_LOCK(buf);
	buf->max_read = max;
	EVBUFFER_UNLOCK(buf);
	return 0;
}