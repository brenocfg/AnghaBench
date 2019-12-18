#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ redisContext ;
typedef  int /*<<< orphan*/  redisCallback ;
struct TYPE_11__ {int /*<<< orphan*/ * head; } ;
struct TYPE_10__ {TYPE_5__ replies; int /*<<< orphan*/  (* onConnect ) (TYPE_2__*,int /*<<< orphan*/ ) ;TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 int REDIS_CONNECTED ; 
 int /*<<< orphan*/  REDIS_ERR ; 
 int /*<<< orphan*/  REDIS_ERR_TIMEOUT ; 
 scalar_t__ REDIS_OK ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_2__*) ; 
 int /*<<< orphan*/  __redisRunCallback (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __redisSetError (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ __redisShiftCallback (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void redisAsyncHandleTimeout(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    redisCallback cb;

    if ((c->flags & REDIS_CONNECTED) && ac->replies.head == NULL) {
        /* Nothing to do - just an idle timeout */
        return;
    }

    if (!c->err) {
        __redisSetError(c, REDIS_ERR_TIMEOUT, "Timeout");
    }

    if (!(c->flags & REDIS_CONNECTED) && ac->onConnect) {
        ac->onConnect(ac, REDIS_ERR);
    }

    while (__redisShiftCallback(&ac->replies, &cb) == REDIS_OK) {
        __redisRunCallback(ac, &cb, NULL);
    }

    /**
     * TODO: Don't automatically sever the connection,
     * rather, allow to ignore <x> responses before the queue is clear
     */
    __redisAsyncDisconnect(ac);
}