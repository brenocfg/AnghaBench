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
struct vio_driver_state {TYPE_1__* cmp; } ;
struct TYPE_2__ {int waiting_for; int err; int /*<<< orphan*/  com; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vdc_finish(struct vio_driver_state *vio, int err, int waiting_for)
{
	if (vio->cmp &&
	    (waiting_for == -1 ||
	     vio->cmp->waiting_for == waiting_for)) {
		vio->cmp->err = err;
		complete(&vio->cmp->com);
		vio->cmp = NULL;
	}
}