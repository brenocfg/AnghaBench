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
struct trelay {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  dev2; int /*<<< orphan*/  dev1; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trelay*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_rx_handler_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trelay_do_remove(struct trelay *tr)
{
	list_del(&tr->list);

	dev_put(tr->dev1);
	dev_put(tr->dev2);

	netdev_rx_handler_unregister(tr->dev1);
	netdev_rx_handler_unregister(tr->dev2);

	debugfs_remove_recursive(tr->debugfs);
	kfree(tr);

	return 0;
}