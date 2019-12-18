#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  callout; int /*<<< orphan*/  mtx; } ;
struct delayed_work {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool
linux_cancel_timer(struct delayed_work *dwork, bool drain)
{
	bool cancelled;

	mtx_lock(&dwork->timer.mtx);
	cancelled = (callout_stop(&dwork->timer.callout) == 1);
	mtx_unlock(&dwork->timer.mtx);

	/* check if we should drain */
	if (drain)
		callout_drain(&dwork->timer.callout);
	return (cancelled);
}