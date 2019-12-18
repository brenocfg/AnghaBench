#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisContext ;
struct TYPE_6__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ redisAsyncContext ;

/* Variables and functions */
 scalar_t__ REDIS_ERR ; 
 int /*<<< orphan*/  _EL_ADD_READ (TYPE_1__*) ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_1__*) ; 
 scalar_t__ redisBufferRead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redisProcessCallbacks (TYPE_1__*) ; 

void redisAsyncRead(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (redisBufferRead(c) == REDIS_ERR) {
        __redisAsyncDisconnect(ac);
    } else {
        /* Always re-schedule reads */
        _EL_ADD_READ(ac);
        redisProcessCallbacks(ac);
    }
}