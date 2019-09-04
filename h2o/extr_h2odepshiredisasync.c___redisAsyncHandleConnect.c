#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_9__ {int /*<<< orphan*/  (* onConnect ) (TYPE_2__*,int) ;TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  REDIS_CONNECTED ; 
 scalar_t__ REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_2__*) ; 
 scalar_t__ errno ; 
 scalar_t__ redisCheckSocketError (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);

    if (redisCheckSocketError(c) == REDIS_ERR) {
        /* Try again later when connect(2) is still in progress. */
        if (errno == EINPROGRESS)
            return REDIS_OK;

        if (ac->onConnect) ac->onConnect(ac,REDIS_ERR);
        __redisAsyncDisconnect(ac);
        return REDIS_ERR;
    }

    /* Mark context as connected. */
    c->flags |= REDIS_CONNECTED;
    if (ac->onConnect) ac->onConnect(ac,REDIS_OK);
    return REDIS_OK;
}