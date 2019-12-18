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
typedef  int ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_LOCK (struct evbuffer*) ; 
 int /*<<< orphan*/  EVBUFFER_UNLOCK (struct evbuffer*) ; 
 int evbuffer_copyout_from (struct evbuffer*,int /*<<< orphan*/ *,void*,size_t) ; 
 scalar_t__ evbuffer_drain (struct evbuffer*,int) ; 

int
evbuffer_remove(struct evbuffer *buf, void *data_out, size_t datlen)
{
	ev_ssize_t n;
	EVBUFFER_LOCK(buf);
	n = evbuffer_copyout_from(buf, NULL, data_out, datlen);
	if (n > 0) {
		if (evbuffer_drain(buf, n)<0)
			n = -1;
	}
	EVBUFFER_UNLOCK(buf);
	return (int)n;
}