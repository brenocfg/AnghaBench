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
struct TYPE_4__ {size_t num_wheels; } ;
typedef  TYPE_1__ h2o_timerwheel_t ;

/* Variables and functions */
 size_t H2O_TIMERWHEEL_SLOTS_PER_WHEEL ; 
 int /*<<< orphan*/  validate_slot (TYPE_1__*,size_t,size_t) ; 

int h2o_timerwheel_validate(h2o_timerwheel_t *ctx)
{
    size_t wheel, slot;
    int success = 1;

    for (wheel = 0; wheel < ctx->num_wheels; ++wheel)
        for (slot = 0; slot < H2O_TIMERWHEEL_SLOTS_PER_WHEEL; ++slot)
            if (!validate_slot(ctx, wheel, slot))
                success = 0;

    return success;
}