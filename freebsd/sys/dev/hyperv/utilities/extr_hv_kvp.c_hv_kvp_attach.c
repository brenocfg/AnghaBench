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
struct sysctl_oid_list {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_4__ {TYPE_2__* hv_kvp_dev; int /*<<< orphan*/  task; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  dev_sema; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ hv_kvp_sc ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {TYPE_1__* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int MAKEDEV_CHECKNAME ; 
 int MAKEDEV_WAITOK ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid_list* SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hv_kvp_callback ; 
 int /*<<< orphan*/  hv_kvp_cdevsw ; 
 int /*<<< orphan*/  hv_kvp_log ; 
 int /*<<< orphan*/  hv_kvp_process_request ; 
 int make_dev_p (int,TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int vmbus_ic_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hv_kvp_attach(device_t dev)
{
	int error;
	struct sysctl_oid_list *child;
	struct sysctl_ctx_list *ctx;

	hv_kvp_sc *sc = (hv_kvp_sc*)device_get_softc(dev);

	sc->dev = dev;
	sema_init(&sc->dev_sema, 0, "hv_kvp device semaphore");
	mtx_init(&sc->pending_mutex, "hv-kvp pending mutex",
		NULL, MTX_DEF);

	ctx = device_get_sysctl_ctx(dev);
	child = SYSCTL_CHILDREN(device_get_sysctl_tree(dev));

	SYSCTL_ADD_INT(ctx, child, OID_AUTO, "hv_kvp_log",
	    CTLFLAG_RWTUN, &hv_kvp_log, 0, "Hyperv KVP service log level");

	TASK_INIT(&sc->task, 0, hv_kvp_process_request, sc);

	/* create character device */
	error = make_dev_p(MAKEDEV_CHECKNAME | MAKEDEV_WAITOK,
			&sc->hv_kvp_dev,
			&hv_kvp_cdevsw,
			0,
			UID_ROOT,
			GID_WHEEL,
			0640,
			"hv_kvp_dev");

	if (error != 0)
		return (error);
	sc->hv_kvp_dev->si_drv1 = sc;

	return (vmbus_ic_attach(dev, hv_kvp_callback));
}