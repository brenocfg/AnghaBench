#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* timeout; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* scheduleTimer ) (int /*<<< orphan*/ ,TYPE_4__) ;} ;
struct TYPE_8__ {TYPE_1__ c; TYPE_2__ ev; } ;
typedef  TYPE_3__ redisAsyncContext ;
struct TYPE_9__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__) ; 

__attribute__((used)) static inline void refreshTimeout(redisAsyncContext *ctx) {
    if (ctx->c.timeout && ctx->ev.scheduleTimer &&
        (ctx->c.timeout->tv_sec || ctx->c.timeout->tv_usec)) {
        ctx->ev.scheduleTimer(ctx->ev.data, *ctx->c.timeout);
    // } else {
    //     printf("Not scheduling timer.. (tmo=%p)\n", ctx->c.timeout);
    //     if (ctx->c.timeout){
    //         printf("tv_sec: %u. tv_usec: %u\n", ctx->c.timeout->tv_sec,
    //                ctx->c.timeout->tv_usec);
    //     }
    }
}