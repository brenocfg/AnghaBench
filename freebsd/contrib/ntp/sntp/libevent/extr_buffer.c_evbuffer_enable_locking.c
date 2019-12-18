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
struct evbuffer {int own_lock; void* lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_ALLOC_LOCK (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 

int
evbuffer_enable_locking(struct evbuffer *buf, void *lock)
{
#ifdef EVENT__DISABLE_THREAD_SUPPORT
	return -1;
#else
	if (buf->lock)
		return -1;

	if (!lock) {
		EVTHREAD_ALLOC_LOCK(lock, EVTHREAD_LOCKTYPE_RECURSIVE);
		if (!lock)
			return -1;
		buf->lock = lock;
		buf->own_lock = 1;
	} else {
		buf->lock = lock;
		buf->own_lock = 0;
	}

	return 0;
#endif
}