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
struct vfsconf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/ * sc_cdev; scalar_t__ sc_dev_opened; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 int /*<<< orphan*/  autofs_node_zone ; 
 int /*<<< orphan*/  autofs_request_zone ; 
 TYPE_1__* autofs_softc ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

int
autofs_uninit(struct vfsconf *vfsp)
{

	sx_xlock(&autofs_softc->sc_lock);
	if (autofs_softc->sc_dev_opened) {
		sx_xunlock(&autofs_softc->sc_lock);
		return (EBUSY);
	}
	if (autofs_softc->sc_cdev != NULL)
		destroy_dev(autofs_softc->sc_cdev);

	uma_zdestroy(autofs_request_zone);
	uma_zdestroy(autofs_node_zone);

	sx_xunlock(&autofs_softc->sc_lock);
	/*
	 * XXX: Race with open?
	 */
	free(autofs_softc, M_AUTOFS);

	return (0);
}