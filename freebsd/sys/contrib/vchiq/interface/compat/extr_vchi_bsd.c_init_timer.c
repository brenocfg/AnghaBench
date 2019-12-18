#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timer_list {scalar_t__ expires; int /*<<< orphan*/  callout; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
init_timer(struct timer_list *t)
{
	mtx_init(&t->mtx, "dahdi timer lock", NULL, MTX_SPIN);
	callout_init(&t->callout, 1);
	t->expires = 0;
	/*
	 * function and data are not initialized intentionally:
	 * they are not initialized by Linux implementation too
	 */
}