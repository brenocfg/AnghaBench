#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ pendingWrite; scalar_t__ wantRead; } ;
typedef  TYPE_1__ redisSSLContext ;
struct TYPE_12__ {TYPE_1__* privdata; } ;
typedef  TYPE_2__ redisContext ;
struct TYPE_13__ {TYPE_2__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;

/* Variables and functions */
 int REDIS_ERR ; 
 int /*<<< orphan*/  _EL_ADD_READ (TYPE_3__*) ; 
 int /*<<< orphan*/  _EL_ADD_WRITE (TYPE_3__*) ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_3__*) ; 
 int redisBufferRead (TYPE_2__*) ; 
 int redisBufferWrite (TYPE_2__*,int*) ; 
 int /*<<< orphan*/  redisProcessCallbacks (TYPE_3__*) ; 

__attribute__((used)) static void redisSSLAsyncRead(redisAsyncContext *ac) {
    int rv;
    redisSSLContext *rssl = ac->c.privdata;
    redisContext *c = &ac->c;

    rssl->wantRead = 0;

    if (rssl->pendingWrite) {
        int done;

        /* This is probably just a write event */
        rssl->pendingWrite = 0;
        rv = redisBufferWrite(c, &done);
        if (rv == REDIS_ERR) {
            __redisAsyncDisconnect(ac);
            return;
        } else if (!done) {
            _EL_ADD_WRITE(ac);
        }
    }

    rv = redisBufferRead(c);
    if (rv == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        _EL_ADD_READ(ac);
        redisProcessCallbacks(ac);
    }
}