#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_5__ {TYPE_2__* sc; } ;
struct TYPE_6__ {TYPE_1__ app_sc; TYPE_3__* hv_appvss_dev; TYPE_1__ daemon_sc; TYPE_3__* hv_vss_dev; int /*<<< orphan*/  task; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ hv_vss_sc ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {TYPE_1__* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  APP_VSS_DEV_NAME ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  FS_VSS_DEV_NAME ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_appvss_cdevsw ; 
 int /*<<< orphan*/  hv_vss_callback ; 
 int /*<<< orphan*/  hv_vss_cdevsw ; 
 int /*<<< orphan*/  hv_vss_init_send_receive_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_vss_log ; 
 int /*<<< orphan*/  hv_vss_log_info (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hv_vss_process_request ; 
 int make_dev_p (int,TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vmbus_ic_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_vss_attach(device_t dev)
{
	int error;
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;

	hv_vss_sc *sc = (hv_vss_sc*)device_get_softc(dev);

	sc->dev = dev;
	mtx_init(&sc->pending_mutex, "hv_vss pending mutex", NULL, MTX_DEF);

	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "hv_vss_log",
	    CTLFLAG_RWTUN, &hv_vss_log, 0, "Hyperv VSS service log level");

	TASK_INIT(&sc->task, 0, hv_vss_process_request, sc);
	hv_vss_init_send_receive_queue(dev);
	/* create character device for file system freeze/thaw */
	error = make_dev_p(MAKEDEV_CHECKNAME | MAKEDEV_WAITOK,
		    &sc->hv_vss_dev,
		    &hv_vss_cdevsw,
		    0,
		    UID_ROOT,
		    GID_WHEEL,
		    0640,
		    FS_VSS_DEV_NAME);

	if (error != 0) {
		hv_vss_log_info("Fail to create '%s': %d\n", FS_VSS_DEV_NAME, error);
		return (error);
	}
	sc->hv_vss_dev->si_drv1 = &sc->daemon_sc;
	sc->daemon_sc.sc = sc;
	/* create character device for application freeze/thaw */
	error = make_dev_p(MAKEDEV_CHECKNAME | MAKEDEV_WAITOK,
		    &sc->hv_appvss_dev,
		    &hv_appvss_cdevsw,
		    0,
		    UID_ROOT,
		    GID_WHEEL,
		    0640,
		    APP_VSS_DEV_NAME);

	if (error != 0) {
		hv_vss_log_info("Fail to create '%s': %d\n", APP_VSS_DEV_NAME, error);
		return (error);
	}
	sc->hv_appvss_dev->si_drv1 = &sc->app_sc;
	sc->app_sc.sc = sc;

	return (vmbus_ic_attach(dev, hv_vss_callback));
}