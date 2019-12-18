#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/ * sc_shutdown_post_eh; int /*<<< orphan*/ * sc_shutdown_pre_eh; int /*<<< orphan*/ * sc_cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISCSI_DEBUG (char*) ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_outstanding_zone ; 
 int /*<<< orphan*/  iscsi_terminate_sessions (TYPE_1__*) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  shutdown_post_sync ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_unload(void)
{

	if (sc->sc_cdev != NULL) {
		ISCSI_DEBUG("removing device node");
		destroy_dev(sc->sc_cdev);
		ISCSI_DEBUG("device node removed");
	}

	if (sc->sc_shutdown_pre_eh != NULL)
		EVENTHANDLER_DEREGISTER(shutdown_pre_sync, sc->sc_shutdown_pre_eh);
	if (sc->sc_shutdown_post_eh != NULL)
		EVENTHANDLER_DEREGISTER(shutdown_post_sync, sc->sc_shutdown_post_eh);

	iscsi_terminate_sessions(sc);

	uma_zdestroy(iscsi_outstanding_zone);
	sx_destroy(&sc->sc_lock);
	cv_destroy(&sc->sc_cv);
	free(sc, M_ISCSI);
	return (0);
}