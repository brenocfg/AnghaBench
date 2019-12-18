#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct evconnlistener {int refcnt; int /*<<< orphan*/  lock; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct evconnlistener*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVTHREAD_FREE_LOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVTHREAD_LOCKTYPE_RECURSIVE ; 
 int /*<<< orphan*/  UNLOCK (struct evconnlistener*) ; 
 int /*<<< orphan*/  mm_free (struct evconnlistener*) ; 
 int /*<<< orphan*/  stub1 (struct evconnlistener*) ; 

__attribute__((used)) static int
listener_decref_and_unlock(struct evconnlistener *listener)
{
	int refcnt = --listener->refcnt;
	if (refcnt == 0) {
		listener->ops->destroy(listener);
		UNLOCK(listener);
		EVTHREAD_FREE_LOCK(listener->lock, EVTHREAD_LOCKTYPE_RECURSIVE);
		mm_free(listener);
		return 1;
	} else {
		UNLOCK(listener);
		return 0;
	}
}