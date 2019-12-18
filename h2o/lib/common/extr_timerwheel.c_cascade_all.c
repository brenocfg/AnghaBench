#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t num_wheels; int /*<<< orphan*/ ** wheels; int /*<<< orphan*/  last_run; } ;
typedef  TYPE_1__ h2o_timerwheel_t ;

/* Variables and functions */
 int /*<<< orphan*/  cascade_one (TYPE_1__*,size_t,size_t) ; 
 int /*<<< orphan*/  h2o_linklist_is_empty (int /*<<< orphan*/ *) ; 
 size_t timer_slot (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cascade_all(h2o_timerwheel_t *ctx, size_t wheel)
{
    int cascaded = 0;

    for (; wheel < ctx->num_wheels; ++wheel) {
        size_t slot = timer_slot(wheel, ctx->last_run);
        if (!h2o_linklist_is_empty(&ctx->wheels[wheel][slot]))
            cascaded = 1;
        cascade_one(ctx, wheel, slot);
        if (slot != 0)
            break;
    }

    return cascaded;
}