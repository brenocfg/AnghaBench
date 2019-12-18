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
struct evbuffer {int freeze_start; int freeze_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 

int
evbuffer_freeze(struct evbuffer *buffer, int start)
{
	EVBUFFER_LOCK(buffer);
	if (start)
		buffer->freeze_start = 1;
	else
		buffer->freeze_end = 1;
	EVBUFFER_UNLOCK(buffer);
	return 0;
}