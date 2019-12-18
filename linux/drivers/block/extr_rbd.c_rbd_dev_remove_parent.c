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
struct rbd_device {struct rbd_device* parent_spec; scalar_t__ parent_overlap; struct rbd_device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  rbd_assert (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_dev_destroy (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_dev_image_release (struct rbd_device*) ; 
 int /*<<< orphan*/  rbd_spec_put (struct rbd_device*) ; 

__attribute__((used)) static void rbd_dev_remove_parent(struct rbd_device *rbd_dev)
{
	while (rbd_dev->parent) {
		struct rbd_device *first = rbd_dev;
		struct rbd_device *second = first->parent;
		struct rbd_device *third;

		/*
		 * Follow to the parent with no grandparent and
		 * remove it.
		 */
		while (second && (third = second->parent)) {
			first = second;
			second = third;
		}
		rbd_assert(second);
		rbd_dev_image_release(second);
		rbd_dev_destroy(second);
		first->parent = NULL;
		first->parent_overlap = 0;

		rbd_assert(first->parent_spec);
		rbd_spec_put(first->parent_spec);
		first->parent_spec = NULL;
	}
}