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
struct device {int dummy; } ;
struct devfreq_notifier_devres {int /*<<< orphan*/  list; int /*<<< orphan*/  nb; int /*<<< orphan*/  devfreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  devfreq_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_devfreq_notifier_release(struct device *dev, void *res)
{
	struct devfreq_notifier_devres *this = res;

	devfreq_unregister_notifier(this->devfreq, this->nb, this->list);
}