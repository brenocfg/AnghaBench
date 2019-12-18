#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct isp_spi {int /*<<< orphan*/ * atused; int /*<<< orphan*/ * atpool; int /*<<< orphan*/  atfree; int /*<<< orphan*/ * ntpool; int /*<<< orphan*/  ntfree; int /*<<< orphan*/  waitq; struct cam_path* path; struct cam_sim* sim; } ;
struct isp_fc {int ready; int num_threads; int /*<<< orphan*/  inject_lost_data_frame; int /*<<< orphan*/  gone_device_time; int /*<<< orphan*/  loop_down_limit; struct cam_sim* sim; struct cam_path* path; int /*<<< orphan*/  kproc; int /*<<< orphan*/ * atused; int /*<<< orphan*/ * atpool; int /*<<< orphan*/  atfree; int /*<<< orphan*/ * ntpool; int /*<<< orphan*/  ntfree; int /*<<< orphan*/  waitq; int /*<<< orphan*/  gtask; int /*<<< orphan*/  gdt; TYPE_2__* isp; } ;
struct TYPE_19__ {int /*<<< orphan*/  func_code; } ;
struct ccb_setasync {struct cam_sim* callback_arg; int /*<<< orphan*/  callback; int /*<<< orphan*/  event_enable; TYPE_4__ ccb_h; } ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct cam_devq {int dummy; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_17__ {TYPE_1__ isp_osinfo; int /*<<< orphan*/  isp_lock; int /*<<< orphan*/  isp_dev; int /*<<< orphan*/  isp_maxcmds; } ;
typedef  TYPE_2__ ispsoftc_t ;
struct TYPE_18__ {int isp_use_gft_id; int isp_use_gff_id; int /*<<< orphan*/  isp_topo; int /*<<< orphan*/  isp_loopstate; int /*<<< orphan*/  isp_fwstate; int /*<<< orphan*/  isp_linkstate; int /*<<< orphan*/  isp_gbspeed; int /*<<< orphan*/  isp_wwpn; int /*<<< orphan*/  isp_wwnn; } ;
typedef  TYPE_3__ fcparam ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int ATPDPHASHSIZE ; 
 int ATPDPSIZE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 scalar_t__ CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int /*<<< orphan*/  CTLFLAG_RWTUN ; 
 int CTLTYPE_INT ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_3__* FCPARAM (TYPE_2__*,int) ; 
 struct isp_fc* ISP_FC_PC (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ISP_LOCK (TYPE_2__*) ; 
 struct isp_spi* ISP_SPI_PC (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ISP_UNLOCK (TYPE_2__*) ; 
 scalar_t__ IS_SCSI (TYPE_2__*) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,TYPE_2__*,int,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_QUAD (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct isp_fc*) ; 
 int /*<<< orphan*/  XPT_SASYNC_CB ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_devq*) ; 
 int /*<<< orphan*/  cam_sim_free (struct cam_sim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (struct cam_sim*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_action ; 
 int /*<<< orphan*/  isp_cam_async ; 
 int /*<<< orphan*/  isp_gdt_task ; 
 int /*<<< orphan*/  isp_kthread ; 
 int /*<<< orphan*/  isp_loop_changed (TYPE_2__*,int) ; 
 int /*<<< orphan*/  isp_poll ; 
 int /*<<< orphan*/  isp_role_sysctl ; 
 scalar_t__ kproc_create (int /*<<< orphan*/ ,struct isp_fc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_4__*,struct cam_path*,int) ; 

__attribute__((used)) static int
isp_attach_chan(ispsoftc_t *isp, struct cam_devq *devq, int chan)
{
	struct ccb_setasync csa;
	struct cam_sim *sim;
	struct cam_path *path;
#ifdef	ISP_TARGET_MODE
	int i;
#endif

	sim = cam_sim_alloc(isp_action, isp_poll, "isp", isp,
	    device_get_unit(isp->isp_dev), &isp->isp_lock,
	    isp->isp_maxcmds, isp->isp_maxcmds, devq);
	if (sim == NULL)
		return (ENOMEM);

	ISP_LOCK(isp);
	if (xpt_bus_register(sim, isp->isp_dev, chan) != CAM_SUCCESS) {
		ISP_UNLOCK(isp);
		cam_sim_free(sim, FALSE);
		return (EIO);
	}
	ISP_UNLOCK(isp);
	if (xpt_create_path(&path, NULL, cam_sim_path(sim), CAM_TARGET_WILDCARD, CAM_LUN_WILDCARD) != CAM_REQ_CMP) {
		ISP_LOCK(isp);
		xpt_bus_deregister(cam_sim_path(sim));
		ISP_UNLOCK(isp);
		cam_sim_free(sim, FALSE);
		return (ENXIO);
	}
	xpt_setup_ccb(&csa.ccb_h, path, 5);
	csa.ccb_h.func_code = XPT_SASYNC_CB;
	csa.event_enable = AC_LOST_DEVICE;
	csa.callback = isp_cam_async;
	csa.callback_arg = sim;

	ISP_LOCK(isp);
	xpt_action((union ccb *)&csa);
	ISP_UNLOCK(isp);

	if (IS_SCSI(isp)) {
		struct isp_spi *spi = ISP_SPI_PC(isp, chan);
		spi->sim = sim;
		spi->path = path;
#ifdef	ISP_TARGET_MODE
		TAILQ_INIT(&spi->waitq);
		STAILQ_INIT(&spi->ntfree);
		for (i = 0; i < ATPDPSIZE; i++)
			STAILQ_INSERT_TAIL(&spi->ntfree, &spi->ntpool[i], next);
		LIST_INIT(&spi->atfree);
		for (i = ATPDPSIZE-1; i >= 0; i--)
			LIST_INSERT_HEAD(&spi->atfree, &spi->atpool[i], next);
		for (i = 0; i < ATPDPHASHSIZE; i++)
			LIST_INIT(&spi->atused[i]);
#endif
	} else {
		fcparam *fcp = FCPARAM(isp, chan);
		struct isp_fc *fc = ISP_FC_PC(isp, chan);
		struct sysctl_ctx_list *ctx = device_get_sysctl_ctx(isp->isp_osinfo.dev);
		struct sysctl_oid *tree = device_get_sysctl_tree(isp->isp_osinfo.dev);
		char name[16];

		ISP_LOCK(isp);
		fc->sim = sim;
		fc->path = path;
		fc->isp = isp;
		fc->ready = 1;
		fcp->isp_use_gft_id = 1;
		fcp->isp_use_gff_id = 1;

		callout_init_mtx(&fc->gdt, &isp->isp_lock, 0);
		TASK_INIT(&fc->gtask, 1, isp_gdt_task, fc);
#ifdef	ISP_TARGET_MODE
		TAILQ_INIT(&fc->waitq);
		STAILQ_INIT(&fc->ntfree);
		for (i = 0; i < ATPDPSIZE; i++)
			STAILQ_INSERT_TAIL(&fc->ntfree, &fc->ntpool[i], next);
		LIST_INIT(&fc->atfree);
		for (i = ATPDPSIZE-1; i >= 0; i--)
			LIST_INSERT_HEAD(&fc->atfree, &fc->atpool[i], next);
		for (i = 0; i < ATPDPHASHSIZE; i++)
			LIST_INIT(&fc->atused[i]);
#endif
		isp_loop_changed(isp, chan);
		ISP_UNLOCK(isp);
		if (kproc_create(isp_kthread, fc, &fc->kproc, 0, 0,
		    "%s_%d", device_get_nameunit(isp->isp_osinfo.dev), chan)) {
			xpt_free_path(fc->path);
			ISP_LOCK(isp);
			xpt_bus_deregister(cam_sim_path(fc->sim));
			ISP_UNLOCK(isp);
			cam_sim_free(fc->sim, FALSE);
			return (ENOMEM);
		}
		fc->num_threads += 1;
		if (chan > 0) {
			snprintf(name, sizeof(name), "chan%d", chan);
			tree = SYSCTL_ADD_NODE(ctx, SYSCTL_CHILDREN(tree),
			    OID_AUTO, name, CTLFLAG_RW, 0, "Virtual channel");
		}
		SYSCTL_ADD_QUAD(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "wwnn", CTLFLAG_RD, &fcp->isp_wwnn,
		    "World Wide Node Name");
		SYSCTL_ADD_QUAD(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "wwpn", CTLFLAG_RD, &fcp->isp_wwpn,
		    "World Wide Port Name");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "loop_down_limit", CTLFLAG_RW, &fc->loop_down_limit, 0,
		    "Loop Down Limit");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "gone_device_time", CTLFLAG_RW, &fc->gone_device_time, 0,
		    "Gone Device Time");
#if defined(ISP_TARGET_MODE) && defined(DEBUG)
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "inject_lost_data_frame", CTLFLAG_RW, &fc->inject_lost_data_frame, 0,
		    "Cause a Lost Frame on a Read");
#endif
		SYSCTL_ADD_PROC(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "role", CTLTYPE_INT | CTLFLAG_RW, isp, chan,
		    isp_role_sysctl, "I", "Current role");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "speed", CTLFLAG_RD, &fcp->isp_gbspeed, 0,
		    "Connection speed in gigabits");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "linkstate", CTLFLAG_RD, &fcp->isp_linkstate, 0,
		    "Link state");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "fwstate", CTLFLAG_RD, &fcp->isp_fwstate, 0,
		    "Firmware state");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "loopstate", CTLFLAG_RD, &fcp->isp_loopstate, 0,
		    "Loop state");
		SYSCTL_ADD_UINT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "topo", CTLFLAG_RD, &fcp->isp_topo, 0,
		    "Connection topology");
		SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "use_gft_id", CTLFLAG_RWTUN, &fcp->isp_use_gft_id, 0,
		    "Use GFT_ID during fabric scan");
		SYSCTL_ADD_INT(ctx, SYSCTL_CHILDREN(tree), OID_AUTO,
		    "use_gff_id", CTLFLAG_RWTUN, &fcp->isp_use_gff_id, 0,
		    "Use GFF_ID during fabric scan");
	}
	return (0);
}