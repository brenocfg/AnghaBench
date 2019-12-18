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
struct extcon_dev_notifier_devres {int /*<<< orphan*/  nb; int /*<<< orphan*/  id; int /*<<< orphan*/  edev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  extcon_unregister_notifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void devm_extcon_dev_notifier_unreg(struct device *dev, void *res)
{
	struct extcon_dev_notifier_devres *this = res;

	extcon_unregister_notifier(this->edev, this->id, this->nb);
}