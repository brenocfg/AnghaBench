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
struct rbd_device {int /*<<< orphan*/  running_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbd_pre_release_action (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_unlock (struct rbd_device*) ; 

__attribute__((used)) static void __rbd_release_lock(struct rbd_device *rbd_dev)
{
	rbd_assert(list_empty(&rbd_dev->running_list));

	rbd_pre_release_action(rbd_dev);
	rbd_unlock(rbd_dev);
}