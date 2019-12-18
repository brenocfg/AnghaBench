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
struct dev_pm_ops {int /*<<< orphan*/  complete; int /*<<< orphan*/  resume; int /*<<< orphan*/  resume_early; int /*<<< orphan*/  resume_noirq; int /*<<< orphan*/  suspend_noirq; int /*<<< orphan*/  suspend_late; int /*<<< orphan*/  suspend; int /*<<< orphan*/  prepare; } ;

/* Variables and functions */

__attribute__((used)) static bool pm_ops_is_empty(const struct dev_pm_ops *ops)
{
	if (!ops)
		return true;

	return !ops->prepare &&
	       !ops->suspend &&
	       !ops->suspend_late &&
	       !ops->suspend_noirq &&
	       !ops->resume_noirq &&
	       !ops->resume_early &&
	       !ops->resume &&
	       !ops->complete;
}