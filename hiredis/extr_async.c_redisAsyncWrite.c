#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisContext ;
struct TYPE_7__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ redisAsyncContext ;

/* Variables and functions */
 scalar_t__ REDIS_ERR ; 
 int /*<<< orphan*/  _EL_ADD_READ (TYPE_1__*) ; 
 int /*<<< orphan*/  _EL_ADD_WRITE (TYPE_1__*) ; 
 int /*<<< orphan*/  _EL_DEL_WRITE (TYPE_1__*) ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_1__*) ; 
 scalar_t__ redisBufferWrite (int /*<<< orphan*/ *,int*) ; 

void redisAsyncWrite(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    int done = 0;

    if (redisBufferWrite(c,&done) == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        /* Continue writing when not done, stop writing otherwise */
        if (!done)
            _EL_ADD_WRITE(ac);
        else
            _EL_DEL_WRITE(ac);

        /* Always schedule reads after writes */
        _EL_ADD_READ(ac);
    }
}