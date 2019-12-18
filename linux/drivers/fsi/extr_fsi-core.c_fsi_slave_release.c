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
struct TYPE_2__ {int /*<<< orphan*/  devt; } ;
struct fsi_slave {TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  fsi_free_minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsi_slave*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct fsi_slave* to_fsi_slave (struct device*) ; 

__attribute__((used)) static void fsi_slave_release(struct device *dev)
{
	struct fsi_slave *slave = to_fsi_slave(dev);

	fsi_free_minor(slave->dev.devt);
	of_node_put(dev->of_node);
	kfree(slave);
}