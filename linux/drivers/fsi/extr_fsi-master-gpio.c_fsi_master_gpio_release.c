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
struct fsi_master_gpio {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_fsi_master (struct device*) ; 
 int /*<<< orphan*/  kfree (struct fsi_master_gpio*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct fsi_master_gpio* to_fsi_master_gpio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsi_master_gpio_release(struct device *dev)
{
	struct fsi_master_gpio *master = to_fsi_master_gpio(dev_to_fsi_master(dev));

	of_node_put(dev_of_node(master->dev));

	kfree(master);
}