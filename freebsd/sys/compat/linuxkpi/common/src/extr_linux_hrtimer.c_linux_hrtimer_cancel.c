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
struct hrtimer {int /*<<< orphan*/  callout; } ;

/* Variables and functions */
 scalar_t__ callout_drain (int /*<<< orphan*/ *) ; 

int
linux_hrtimer_cancel(struct hrtimer *hrtimer)
{

	return (callout_drain(&hrtimer->callout) > 0);
}