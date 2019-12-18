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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct cam_sim* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  event_enable; } ;
struct TYPE_4__ {int priority; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {int /*<<< orphan*/  func_code; TYPE_1__ pinfo; } ;
union ccb {TYPE_2__ csa; TYPE_3__ ccb_h; int /*<<< orphan*/  path; int /*<<< orphan*/  lock; int /*<<< orphan*/  hpt_dev; int /*<<< orphan*/  hpt_intr; int /*<<< orphan*/ * hpt_irq; } ;
struct cam_sim {int dummy; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  union ccb IAL_ADAPTER_T ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CAM_UNQUEUED_INDEX ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  DRIVER_VERSION ; 
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int /*<<< orphan*/  KdPrint (char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  PROC_DIR_NAME ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  __str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 int /*<<< orphan*/  cam_simq_free (struct cam_devq*) ; 
 union ccb* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (union ccb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpt_action ; 
 int /*<<< orphan*/  hpt_async ; 
 int /*<<< orphan*/  hpt_intr ; 
 int /*<<< orphan*/  hpt_poll ; 
 int /*<<< orphan*/  hpt_printk (char*) ; 
 int init_adapter (union ccb*) ; 
 int /*<<< orphan*/  launch_worker_thread () ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
hpt_attach(device_t dev)
{
	IAL_ADAPTER_T * pAdapter = device_get_softc(dev);
	int rid;
	union ccb *ccb;
	struct cam_devq *devq;
	struct cam_sim *hpt_vsim;

	device_printf(dev, "%s Version %s \n", DRIVER_NAME, DRIVER_VERSION);

	pAdapter->hpt_dev = dev;
	
	rid = init_adapter(pAdapter);
	if (rid)
		return rid;

	rid = 0;
	if ((pAdapter->hpt_irq = bus_alloc_resource_any(pAdapter->hpt_dev, SYS_RES_IRQ, &rid, RF_SHAREABLE | RF_ACTIVE)) == NULL)
	{
		hpt_printk(("can't allocate interrupt\n"));
		return(ENXIO);
	}

	if (bus_setup_intr(pAdapter->hpt_dev, pAdapter->hpt_irq,
				INTR_TYPE_CAM | INTR_MPSAFE,
				NULL, hpt_intr, pAdapter, &pAdapter->hpt_intr))
	{
		hpt_printk(("can't set up interrupt\n"));
		free(pAdapter, M_DEVBUF);
		return(ENXIO);
	}


	if((ccb = (union ccb *)malloc(sizeof(*ccb), M_DEVBUF, M_WAITOK)) != (union ccb*)NULL)
	{
		bzero(ccb, sizeof(*ccb));
		ccb->ccb_h.pinfo.priority = 1;
		ccb->ccb_h.pinfo.index = CAM_UNQUEUED_INDEX;
	}
	else
	{
		return ENOMEM;
	}
	/*
	 * Create the device queue for our SIM(s).
	 */
	if((devq = cam_simq_alloc(8/*MAX_QUEUE_COMM*/)) == NULL)
	{
		KdPrint(("ENXIO\n"));
		return ENOMEM;
	}

	/*
	 * Construct our SIM entry
	 */
	hpt_vsim = cam_sim_alloc(hpt_action, hpt_poll, __str(PROC_DIR_NAME),
			pAdapter, device_get_unit(pAdapter->hpt_dev),
			&pAdapter->lock, 1, 8, devq);
	if (hpt_vsim == NULL) {
		cam_simq_free(devq);
		return ENOMEM;
	}

	mtx_lock(&pAdapter->lock);
	if (xpt_bus_register(hpt_vsim, dev, 0) != CAM_SUCCESS)
	{
		cam_sim_free(hpt_vsim, /*free devq*/ TRUE);
		mtx_unlock(&pAdapter->lock);
		hpt_vsim = NULL;
		return ENXIO;
	}

	if(xpt_create_path(&pAdapter->path, /*periph */ NULL,
			cam_sim_path(hpt_vsim), CAM_TARGET_WILDCARD,
			CAM_LUN_WILDCARD) != CAM_REQ_CMP)
	{
		xpt_bus_deregister(cam_sim_path(hpt_vsim));
		cam_sim_free(hpt_vsim, /*free_devq*/TRUE);
		mtx_unlock(&pAdapter->lock);
		hpt_vsim = NULL;
		return ENXIO;
	}
	mtx_unlock(&pAdapter->lock);

	xpt_setup_ccb(&(ccb->ccb_h), pAdapter->path, /*priority*/5);
	ccb->ccb_h.func_code = XPT_SASYNC_CB;
	ccb->csa.event_enable = AC_LOST_DEVICE;
	ccb->csa.callback = hpt_async;
	ccb->csa.callback_arg = hpt_vsim;
	xpt_action((union ccb *)ccb);
	free(ccb, M_DEVBUF);

	if (device_get_unit(dev) == 0) {
		/* Start the work thread.  XXX */
		launch_worker_thread();
	}

	return 0;
}