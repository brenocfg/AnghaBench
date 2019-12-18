#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ last_run; } ;
typedef  TYPE_1__ h2o_timerwheel_t ;
struct TYPE_8__ {scalar_t__ expire_at; } ;
typedef  TYPE_2__ h2o_timerwheel_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  link_timer (TYPE_1__*,TYPE_2__*) ; 

void h2o_timerwheel_link_abs(h2o_timerwheel_t *ctx, h2o_timerwheel_entry_t *entry, uint64_t at)
{
    entry->expire_at = at < ctx->last_run ? ctx->last_run : at;
    link_timer(ctx, entry);
}