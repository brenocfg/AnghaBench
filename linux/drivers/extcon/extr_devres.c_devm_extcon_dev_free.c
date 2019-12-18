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
struct extcon_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_extcon_dev_match ; 
 int /*<<< orphan*/  devm_extcon_dev_release ; 
 int /*<<< orphan*/  devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct extcon_dev*) ; 

void devm_extcon_dev_free(struct device *dev, struct extcon_dev *edev)
{
	WARN_ON(devres_release(dev, devm_extcon_dev_release,
			       devm_extcon_dev_match, edev));
}