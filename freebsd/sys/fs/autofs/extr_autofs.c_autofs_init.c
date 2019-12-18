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
struct vfsconf {int dummy; } ;
struct autofs_request {int dummy; } ;
struct autofs_node {int dummy; } ;
struct TYPE_6__ {TYPE_1__* si_drv1; } ;
struct TYPE_5__ {TYPE_2__* sc_cdev; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_WARN (char*,int) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAKEDEV_CHECKNAME ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  autofs_cdevsw ; 
 int /*<<< orphan*/  autofs_node_zone ; 
 int /*<<< orphan*/  autofs_request_zone ; 
 TYPE_1__* autofs_softc ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int make_dev_p (int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ ) ; 

int
autofs_init(struct vfsconf *vfsp)
{
	int error;

	KASSERT(autofs_softc == NULL,
	    ("softc %p, should be NULL", autofs_softc));

	autofs_softc = malloc(sizeof(*autofs_softc), M_AUTOFS,
	    M_WAITOK | M_ZERO);

	autofs_request_zone = uma_zcreate("autofs_request",
	    sizeof(struct autofs_request), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);
	autofs_node_zone = uma_zcreate("autofs_node",
	    sizeof(struct autofs_node), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

	TAILQ_INIT(&autofs_softc->sc_requests);
	cv_init(&autofs_softc->sc_cv, "autofscv");
	sx_init(&autofs_softc->sc_lock, "autofslk");

	error = make_dev_p(MAKEDEV_CHECKNAME, &autofs_softc->sc_cdev,
	    &autofs_cdevsw, NULL, UID_ROOT, GID_WHEEL, 0600, "autofs");
	if (error != 0) {
		AUTOFS_WARN("failed to create device node, error %d", error);
		uma_zdestroy(autofs_request_zone);
		uma_zdestroy(autofs_node_zone);
		free(autofs_softc, M_AUTOFS);

		return (error);
	}
	autofs_softc->sc_cdev->si_drv1 = autofs_softc;

	return (0);
}