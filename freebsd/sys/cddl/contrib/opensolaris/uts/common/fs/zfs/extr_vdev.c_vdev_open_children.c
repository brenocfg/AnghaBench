#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int vdev_children; TYPE_4__** vdev_child; scalar_t__ vdev_nonrot; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  taskq_t ;
struct TYPE_7__ {scalar_t__ vdev_nonrot; int /*<<< orphan*/  vdev_open_error; } ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  TASKQ_PREPOPULATE ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  minclsyspri ; 
 int /*<<< orphan*/ * taskq_create (char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ taskq_dispatch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_open (TYPE_4__*) ; 
 int /*<<< orphan*/  vdev_open_child ; 
 scalar_t__ vdev_uses_zvols (TYPE_1__*) ; 

void
vdev_open_children(vdev_t *vd)
{
	taskq_t *tq;
	int children = vd->vdev_children;

	vd->vdev_nonrot = B_TRUE;

	/*
	 * in order to handle pools on top of zvols, do the opens
	 * in a single thread so that the same thread holds the
	 * spa_namespace_lock
	 */
	if (B_TRUE || vdev_uses_zvols(vd)) {
		for (int c = 0; c < children; c++) {
			vd->vdev_child[c]->vdev_open_error =
			    vdev_open(vd->vdev_child[c]);
			vd->vdev_nonrot &= vd->vdev_child[c]->vdev_nonrot;
		}
		return;
	}
	tq = taskq_create("vdev_open", children, minclsyspri,
	    children, children, TASKQ_PREPOPULATE);

	for (int c = 0; c < children; c++)
		VERIFY(taskq_dispatch(tq, vdev_open_child, vd->vdev_child[c],
		    TQ_SLEEP) != 0);

	taskq_destroy(tq);

	for (int c = 0; c < children; c++)
		vd->vdev_nonrot &= vd->vdev_child[c]->vdev_nonrot;
}