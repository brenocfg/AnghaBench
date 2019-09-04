#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ redisContext ;
struct TYPE_8__ {int /*<<< orphan*/  privdata; int /*<<< orphan*/  (* fn ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ redisCallback ;
struct TYPE_9__ {TYPE_1__ c; } ;
typedef  TYPE_3__ redisAsyncContext ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_IN_CALLBACK ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __redisRunCallback(redisAsyncContext *ac, redisCallback *cb, redisReply *reply) {
    redisContext *c = &(ac->c);
    if (cb->fn != NULL) {
        c->flags |= REDIS_IN_CALLBACK;
        cb->fn(ac,reply,cb->privdata);
        c->flags &= ~REDIS_IN_CALLBACK;
    }
}