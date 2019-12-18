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
struct rbd_device {scalar_t__ object_map_size; int /*<<< orphan*/ * object_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbd_object_map_free(struct rbd_device *rbd_dev)
{
	kvfree(rbd_dev->object_map);
	rbd_dev->object_map = NULL;
	rbd_dev->object_map_size = 0;
}