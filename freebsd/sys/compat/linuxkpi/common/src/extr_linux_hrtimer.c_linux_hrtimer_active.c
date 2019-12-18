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
struct hrtimer {int /*<<< orphan*/  mtx; int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 int callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

bool
linux_hrtimer_active(struct hrtimer *hrtimer)
{
	bool ret;

	mtx_lock(&hrtimer->mtx);
	ret = callout_active(&hrtimer->callout);
	mtx_unlock(&hrtimer->mtx);

	return (ret);
}