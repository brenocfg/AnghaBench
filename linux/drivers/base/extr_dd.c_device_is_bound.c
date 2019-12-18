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
struct device {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  knode_driver; } ;

/* Variables and functions */
 scalar_t__ klist_node_attached (int /*<<< orphan*/ *) ; 

bool device_is_bound(struct device *dev)
{
	return dev->p && klist_node_attached(&dev->p->knode_driver);
}