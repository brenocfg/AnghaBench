#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_10__ {int /*<<< orphan*/  (* onConnect ) (TYPE_2__*,int) ;TYPE_1__ c; } ;
typedef  TYPE_2__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CONNECTED ; 
 scalar_t__ REDIS_ERR ; 
 int REDIS_OK ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_2__*) ; 
 scalar_t__ redisCheckConnectDone (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  redisCheckSocketError (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int) ; 

__attribute__((used)) static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
    int completed = 0;
    redisContext *c = &(ac->c);
    if (redisCheckConnectDone(c, &completed) == REDIS_ERR) {
        /* Error! */
        redisCheckSocketError(c);
        if (ac->onConnect) ac->onConnect(ac, REDIS_ERR);
        __redisAsyncDisconnect(ac);
        return REDIS_ERR;
    } else if (completed == 1) {
        /* connected! */
        if (ac->onConnect) ac->onConnect(ac, REDIS_OK);
        c->flags |= REDIS_CONNECTED;
        return REDIS_OK;
    } else {
        return REDIS_OK;
    }
}