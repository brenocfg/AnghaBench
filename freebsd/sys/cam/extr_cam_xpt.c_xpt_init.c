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
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct cam_devq {int dummy; } ;
typedef  int cam_status ;
struct TYPE_7__ {int /*<<< orphan*/  ich_func; } ;
struct TYPE_6__ {int /*<<< orphan*/  cam_doneq; int /*<<< orphan*/  cam_doneq_mtx; } ;
struct TYPE_5__ {TYPE_3__ xpt_config_hook; int /*<<< orphan*/  xpt_lock; int /*<<< orphan*/  boot_delay; int /*<<< orphan*/  xpt_taskq; int /*<<< orphan*/  xpt_highpower_lock; int /*<<< orphan*/  num_highpower; int /*<<< orphan*/  highpowerq; int /*<<< orphan*/  ccb_scanq; int /*<<< orphan*/  xpt_busses; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_BOOT_DELAY ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  CAM_MAX_HIGHPOWER ; 
 int /*<<< orphan*/  CAM_PERIPH_BIO ; 
 int CAM_REQ_CMP ; 
 int CAM_SUCCESS ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CAM_XPT_PATH_ID ; 
 int EINVAL ; 
 int ENOMEM ; 
 int MAXCPU ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_2__* cam_doneqs ; 
 int cam_num_doneqs ; 
 int /*<<< orphan*/  cam_periph_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cam_sim*) ; 
 int /*<<< orphan*/  cam_proc ; 
 struct cam_sim* cam_sim_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cam_devq*) ; 
 struct cam_devq* cam_simq_alloc (int) ; 
 scalar_t__ config_intrhook_establish (TYPE_3__*) ; 
 int kproc_kthread_add (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int xpt_bus_register (struct cam_sim*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_config ; 
 int xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_done_td ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 
 int /*<<< orphan*/  xptaction ; 
 int /*<<< orphan*/  xptpoll ; 
 int /*<<< orphan*/  xptregister ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static int
xpt_init(void *dummy)
{
	struct cam_sim *xpt_sim;
	struct cam_path *path;
	struct cam_devq *devq;
	cam_status status;
	int error, i;

	TAILQ_INIT(&xsoftc.xpt_busses);
	TAILQ_INIT(&xsoftc.ccb_scanq);
	STAILQ_INIT(&xsoftc.highpowerq);
	xsoftc.num_highpower = CAM_MAX_HIGHPOWER;

	mtx_init(&xsoftc.xpt_lock, "XPT lock", NULL, MTX_DEF);
	mtx_init(&xsoftc.xpt_highpower_lock, "XPT highpower lock", NULL, MTX_DEF);
	xsoftc.xpt_taskq = taskqueue_create("CAM XPT task", M_WAITOK,
	    taskqueue_thread_enqueue, /*context*/&xsoftc.xpt_taskq);

#ifdef CAM_BOOT_DELAY
	/*
	 * Override this value at compile time to assist our users
	 * who don't use loader to boot a kernel.
	 */
	xsoftc.boot_delay = CAM_BOOT_DELAY;
#endif
	/*
	 * The xpt layer is, itself, the equivalent of a SIM.
	 * Allow 16 ccbs in the ccb pool for it.  This should
	 * give decent parallelism when we probe buses and
	 * perform other XPT functions.
	 */
	devq = cam_simq_alloc(16);
	xpt_sim = cam_sim_alloc(xptaction,
				xptpoll,
				"xpt",
				/*softc*/NULL,
				/*unit*/0,
				/*mtx*/&xsoftc.xpt_lock,
				/*max_dev_transactions*/0,
				/*max_tagged_dev_transactions*/0,
				devq);
	if (xpt_sim == NULL)
		return (ENOMEM);

	mtx_lock(&xsoftc.xpt_lock);
	if ((status = xpt_bus_register(xpt_sim, NULL, 0)) != CAM_SUCCESS) {
		mtx_unlock(&xsoftc.xpt_lock);
		printf("xpt_init: xpt_bus_register failed with status %#x,"
		       " failing attach\n", status);
		return (EINVAL);
	}
	mtx_unlock(&xsoftc.xpt_lock);

	/*
	 * Looking at the XPT from the SIM layer, the XPT is
	 * the equivalent of a peripheral driver.  Allocate
	 * a peripheral driver entry for us.
	 */
	if ((status = xpt_create_path(&path, NULL, CAM_XPT_PATH_ID,
				      CAM_TARGET_WILDCARD,
				      CAM_LUN_WILDCARD)) != CAM_REQ_CMP) {
		printf("xpt_init: xpt_create_path failed with status %#x,"
		       " failing attach\n", status);
		return (EINVAL);
	}
	xpt_path_lock(path);
	cam_periph_alloc(xptregister, NULL, NULL, NULL, "xpt", CAM_PERIPH_BIO,
			 path, NULL, 0, xpt_sim);
	xpt_path_unlock(path);
	xpt_free_path(path);

	if (cam_num_doneqs < 1)
		cam_num_doneqs = 1 + mp_ncpus / 6;
	else if (cam_num_doneqs > MAXCPU)
		cam_num_doneqs = MAXCPU;
	for (i = 0; i < cam_num_doneqs; i++) {
		mtx_init(&cam_doneqs[i].cam_doneq_mtx, "CAM doneq", NULL,
		    MTX_DEF);
		STAILQ_INIT(&cam_doneqs[i].cam_doneq);
		error = kproc_kthread_add(xpt_done_td, &cam_doneqs[i],
		    &cam_proc, NULL, 0, 0, "cam", "doneq%d", i);
		if (error != 0) {
			cam_num_doneqs = i;
			break;
		}
	}
	if (cam_num_doneqs < 1) {
		printf("xpt_init: Cannot init completion queues "
		       "- failing attach\n");
		return (ENOMEM);
	}
	/*
	 * Register a callback for when interrupts are enabled.
	 */
	xsoftc.xpt_config_hook.ich_func = xpt_config;
	if (config_intrhook_establish(&xsoftc.xpt_config_hook) != 0) {
		printf("xpt_init: config_intrhook_establish failed "
		       "- failing attach\n");
	}

	return (0);
}