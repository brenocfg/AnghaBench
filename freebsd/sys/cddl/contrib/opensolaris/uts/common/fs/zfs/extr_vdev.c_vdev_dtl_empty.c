#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vdev_dtl_lock; int /*<<< orphan*/ ** vdev_dtl; } ;
typedef  TYPE_1__ vdev_t ;
typedef  size_t vdev_dtl_type_t ;
typedef  int /*<<< orphan*/  range_tree_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  range_tree_is_empty (int /*<<< orphan*/ *) ; 

boolean_t
vdev_dtl_empty(vdev_t *vd, vdev_dtl_type_t t)
{
	range_tree_t *rt = vd->vdev_dtl[t];
	boolean_t empty;

	mutex_enter(&vd->vdev_dtl_lock);
	empty = range_tree_is_empty(rt);
	mutex_exit(&vd->vdev_dtl_lock);

	return (empty);
}