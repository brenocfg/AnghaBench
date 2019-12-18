#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vc_lock; int /*<<< orphan*/  vc_lastused_tree; int /*<<< orphan*/  vc_offset_tree; } ;
struct TYPE_5__ {TYPE_2__ vdev_cache; } ;
typedef  TYPE_1__ vdev_t ;
typedef  TYPE_2__ vdev_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vdev_cache_purge (TYPE_1__*) ; 

void
vdev_cache_fini(vdev_t *vd)
{
	vdev_cache_t *vc = &vd->vdev_cache;

	vdev_cache_purge(vd);

	avl_destroy(&vc->vc_offset_tree);
	avl_destroy(&vc->vc_lastused_tree);

	mutex_destroy(&vc->vc_lock);
}