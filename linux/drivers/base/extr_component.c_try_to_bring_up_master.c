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
struct master {int bound; int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct component {int /*<<< orphan*/  dev; struct master* master; } ;
struct TYPE_2__ {int (* bind ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_open_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ find_components (struct master*) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int try_to_bring_up_master(struct master *master,
	struct component *component)
{
	int ret;

	dev_dbg(master->dev, "trying to bring up master\n");

	if (find_components(master)) {
		dev_dbg(master->dev, "master has incomplete components\n");
		return 0;
	}

	if (component && component->master != master) {
		dev_dbg(master->dev, "master is not for this component (%s)\n",
			dev_name(component->dev));
		return 0;
	}

	if (!devres_open_group(master->dev, NULL, GFP_KERNEL))
		return -ENOMEM;

	/* Found all components */
	ret = master->ops->bind(master->dev);
	if (ret < 0) {
		devres_release_group(master->dev, NULL);
		dev_info(master->dev, "master bind failed: %d\n", ret);
		return ret;
	}

	master->bound = true;
	return 1;
}