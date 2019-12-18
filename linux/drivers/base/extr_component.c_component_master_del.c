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
struct master {int dummy; } ;
struct device {int dummy; } ;
struct component_master_ops {int dummy; } ;

/* Variables and functions */
 struct master* __master_find (struct device*,struct component_master_ops const*) ; 
 int /*<<< orphan*/  component_mutex ; 
 int /*<<< orphan*/  free_master (struct master*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  take_down_master (struct master*) ; 

void component_master_del(struct device *dev,
	const struct component_master_ops *ops)
{
	struct master *master;

	mutex_lock(&component_mutex);
	master = __master_find(dev, ops);
	if (master) {
		take_down_master(master);
		free_master(master);
	}
	mutex_unlock(&component_mutex);
}