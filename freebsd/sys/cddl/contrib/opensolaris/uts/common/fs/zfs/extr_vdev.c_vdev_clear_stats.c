#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vs_alloc; scalar_t__ vs_dspace; scalar_t__ vs_space; } ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_stat_lock; TYPE_1__ vdev_stat; } ;
typedef  TYPE_2__ vdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
vdev_clear_stats(vdev_t *vd)
{
	mutex_enter(&vd->vdev_stat_lock);
	vd->vdev_stat.vs_space = 0;
	vd->vdev_stat.vs_dspace = 0;
	vd->vdev_stat.vs_alloc = 0;
	mutex_exit(&vd->vdev_stat_lock);
}