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
struct TYPE_2__ {int /*<<< orphan*/  lwb_waiters; int /*<<< orphan*/  lwb_vdev_tree; int /*<<< orphan*/  lwb_vdev_lock; } ;
typedef  TYPE_1__ lwb_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zil_lwb_dest(void *vbuf, void *unused)
{
	lwb_t *lwb = vbuf;
	mutex_destroy(&lwb->lwb_vdev_lock);
	avl_destroy(&lwb->lwb_vdev_tree);
	list_destroy(&lwb->lwb_waiters);
}