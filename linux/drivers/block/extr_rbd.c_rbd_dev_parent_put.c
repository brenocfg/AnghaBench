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
struct rbd_device {int /*<<< orphan*/  parent_ref; int /*<<< orphan*/  parent_spec; } ;

/* Variables and functions */
 int atomic_dec_return_safe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_dev_unparent (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_warn (struct rbd_device*,char*) ; 

__attribute__((used)) static void rbd_dev_parent_put(struct rbd_device *rbd_dev)
{
	int counter;

	if (!rbd_dev->parent_spec)
		return;

	counter = atomic_dec_return_safe(&rbd_dev->parent_ref);
	if (counter > 0)
		return;

	/* Last reference; clean up parent data structures */

	if (!counter)
		rbd_dev_unparent(rbd_dev);
	else
		rbd_warn(rbd_dev, "parent reference underflow");
}