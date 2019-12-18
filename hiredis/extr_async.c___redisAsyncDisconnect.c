#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_8__ {scalar_t__ err; int /*<<< orphan*/  replies; TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 int REDIS_DISCONNECTING ; 
 int REDIS_ERR ; 
 int REDIS_NO_AUTO_FREE ; 
 int /*<<< orphan*/  _EL_CLEANUP (TYPE_2__*) ; 
 int /*<<< orphan*/  __redisAsyncCopyError (TYPE_2__*) ; 
 int /*<<< orphan*/  __redisAsyncFree (TYPE_2__*) ; 
 int __redisShiftCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

void __redisAsyncDisconnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    /* Make sure error is accessible if there is any */
    __redisAsyncCopyError(ac);

    if (ac->err == 0) {
        /* For clean disconnects, there should be no pending callbacks. */
        int ret = __redisShiftCallback(&ac->replies,NULL);
        assert(ret == REDIS_ERR);
    } else {
        /* Disconnection is caused by an error, make sure that pending
         * callbacks cannot call new commands. */
        c->flags |= REDIS_DISCONNECTING;
    }

    /* cleanup event library on disconnect.
     * this is safe to call multiple times */
    _EL_CLEANUP(ac);

    /* For non-clean disconnects, __redisAsyncFree() will execute pending
     * callbacks with a NULL-reply. */
    if (!(c->flags & REDIS_NO_AUTO_FREE)) {
      __redisAsyncFree(ac);
    }
}