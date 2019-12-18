#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  timers; } ;
typedef  TYPE_1__ evContext_p ;

/* Variables and functions */
 int /*<<< orphan*/  free_timer ; 
 int /*<<< orphan*/  heap_for_each (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

void
evDestroyTimers(const evContext_p *ctx) {
	(void) heap_for_each(ctx->timers, free_timer, NULL);
	(void) heap_free(ctx->timers);
}