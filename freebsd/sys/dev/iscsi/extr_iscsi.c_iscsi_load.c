#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct iscsi_outstanding {int dummy; } ;
struct TYPE_6__ {TYPE_1__* si_drv1; } ;
struct TYPE_5__ {void* sc_shutdown_post_eh; void* sc_shutdown_pre_eh; TYPE_3__* sc_cdev; int /*<<< orphan*/  sc_cv; int /*<<< orphan*/  sc_sessions; int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  ISCSI_WARN (char*,int) ; 
 int /*<<< orphan*/  MAKEDEV_CHECKNAME ; 
 int /*<<< orphan*/  M_ISCSI ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ SHUTDOWN_PRI_DEFAULT ; 
 scalar_t__ SHUTDOWN_PRI_FIRST ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 int /*<<< orphan*/  cv_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iscsi_cdevsw ; 
 int /*<<< orphan*/  iscsi_outstanding_zone ; 
 int /*<<< orphan*/  iscsi_shutdown_post ; 
 int /*<<< orphan*/  iscsi_shutdown_pre ; 
 int make_dev_p (int /*<<< orphan*/ ,TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sc ; 
 int /*<<< orphan*/  shutdown_post_sync ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_load(void)
{
	int error;

	sc = malloc(sizeof(*sc), M_ISCSI, M_ZERO | M_WAITOK);
	sx_init(&sc->sc_lock, "iscsi");
	TAILQ_INIT(&sc->sc_sessions);
	cv_init(&sc->sc_cv, "iscsi_cv");

	iscsi_outstanding_zone = uma_zcreate("iscsi_outstanding",
	    sizeof(struct iscsi_outstanding), NULL, NULL, NULL, NULL,
	    UMA_ALIGN_PTR, 0);

	error = make_dev_p(MAKEDEV_CHECKNAME, &sc->sc_cdev, &iscsi_cdevsw,
	    NULL, UID_ROOT, GID_WHEEL, 0600, "iscsi");
	if (error != 0) {
		ISCSI_WARN("failed to create device node, error %d", error);
		return (error);
	}
	sc->sc_cdev->si_drv1 = sc;

	sc->sc_shutdown_pre_eh = EVENTHANDLER_REGISTER(shutdown_pre_sync,
	    iscsi_shutdown_pre, sc, SHUTDOWN_PRI_FIRST);
	/*
	 * shutdown_post_sync needs to run after filesystem shutdown and before
	 * CAM shutdown - otherwise when rebooting with an iSCSI session that is
	 * disconnected but has outstanding requests, dashutdown() will hang on
	 * cam_periph_runccb().
	 */
	sc->sc_shutdown_post_eh = EVENTHANDLER_REGISTER(shutdown_post_sync,
	    iscsi_shutdown_post, sc, SHUTDOWN_PRI_DEFAULT - 1);

	return (0);
}