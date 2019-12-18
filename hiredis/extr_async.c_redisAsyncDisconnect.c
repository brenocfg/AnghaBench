#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; } ;
typedef  TYPE_2__ redisContext ;
struct TYPE_6__ {int /*<<< orphan*/ * head; } ;
struct TYPE_8__ {TYPE_1__ replies; TYPE_2__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;

/* Variables and functions */
 int REDIS_DISCONNECTING ; 
 int REDIS_IN_CALLBACK ; 
 int REDIS_NO_AUTO_FREE ; 
 int /*<<< orphan*/  __redisAsyncDisconnect (TYPE_3__*) ; 

void redisAsyncDisconnect(redisAsyncContext *ac) {
    redisContext *c = &(ac->c);
    c->flags |= REDIS_DISCONNECTING;

    /** unset the auto-free flag here, because disconnect undoes this */
    c->flags &= ~REDIS_NO_AUTO_FREE;
    if (!(c->flags & REDIS_IN_CALLBACK) && ac->replies.head == NULL)
        __redisAsyncDisconnect(ac);
}