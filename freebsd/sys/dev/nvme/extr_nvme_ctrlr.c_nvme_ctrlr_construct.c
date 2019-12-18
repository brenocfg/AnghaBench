#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvme_controller {int min_page_size; int ready_timeout_in_ms; int timeout_period; int enable_aborts; int /*<<< orphan*/  cdev; int /*<<< orphan*/  is_failed; int /*<<< orphan*/  fail_req; int /*<<< orphan*/  fail_req_task; int /*<<< orphan*/  reset_task; scalar_t__ notification_sent; scalar_t__ is_initialized; scalar_t__ is_resetting; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  max_xfer_size; scalar_t__ dstrd; scalar_t__ domain; int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct make_dev_args {int mda_mode; void* mda_si_drv1; int /*<<< orphan*/  mda_unit; int /*<<< orphan*/  mda_gid; int /*<<< orphan*/  mda_uid; int /*<<< orphan*/ * mda_devsw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ NVME_CAP_HI_DSTRD (int) ; 
 int NVME_CAP_HI_MPSMIN (int) ; 
 int NVME_CAP_LO_TO (int) ; 
 int NVME_DEFAULT_RETRY_COUNT ; 
 int NVME_DEFAULT_TIMEOUT_PERIOD ; 
 int /*<<< orphan*/  NVME_MAX_TIMEOUT_PERIOD ; 
 int /*<<< orphan*/  NVME_MAX_XFER_SIZE ; 
 int /*<<< orphan*/  NVME_MIN_TIMEOUT_PERIOD ; 
 int /*<<< orphan*/  PI_DISK ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_controller*) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 scalar_t__ bus_get_domain (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_dev_args_init (struct make_dev_args*) ; 
 int make_dev_s (struct make_dev_args*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_ctrlr_cdevsw ; 
 scalar_t__ nvme_ctrlr_construct_admin_qpair (struct nvme_controller*) ; 
 int /*<<< orphan*/  nvme_ctrlr_fail_req_task ; 
 int /*<<< orphan*/  nvme_ctrlr_reset_task ; 
 int nvme_mmio_read_4 (struct nvme_controller*,int) ; 
 int nvme_retry_count ; 
 int /*<<< orphan*/  taskqueue_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 

int
nvme_ctrlr_construct(struct nvme_controller *ctrlr, device_t dev)
{
	struct make_dev_args	md_args;
	uint32_t	cap_lo;
	uint32_t	cap_hi;
	uint32_t	to;
	uint8_t		mpsmin;
	int		status, timeout_period;

	ctrlr->dev = dev;

	mtx_init(&ctrlr->lock, "nvme ctrlr lock", NULL, MTX_DEF);
	if (bus_get_domain(dev, &ctrlr->domain) != 0)
		ctrlr->domain = 0;

	cap_hi = nvme_mmio_read_4(ctrlr, cap_hi);
	ctrlr->dstrd = NVME_CAP_HI_DSTRD(cap_hi) + 2;

	mpsmin = NVME_CAP_HI_MPSMIN(cap_hi);
	ctrlr->min_page_size = 1 << (12 + mpsmin);

	/* Get ready timeout value from controller, in units of 500ms. */
	cap_lo = nvme_mmio_read_4(ctrlr, cap_lo);
	to = NVME_CAP_LO_TO(cap_lo) + 1;
	ctrlr->ready_timeout_in_ms = to * 500;

	timeout_period = NVME_DEFAULT_TIMEOUT_PERIOD;
	TUNABLE_INT_FETCH("hw.nvme.timeout_period", &timeout_period);
	timeout_period = min(timeout_period, NVME_MAX_TIMEOUT_PERIOD);
	timeout_period = max(timeout_period, NVME_MIN_TIMEOUT_PERIOD);
	ctrlr->timeout_period = timeout_period;

	nvme_retry_count = NVME_DEFAULT_RETRY_COUNT;
	TUNABLE_INT_FETCH("hw.nvme.retry_count", &nvme_retry_count);

	ctrlr->enable_aborts = 0;
	TUNABLE_INT_FETCH("hw.nvme.enable_aborts", &ctrlr->enable_aborts);

	ctrlr->max_xfer_size = NVME_MAX_XFER_SIZE;
	if (nvme_ctrlr_construct_admin_qpair(ctrlr) != 0)
		return (ENXIO);

	ctrlr->taskqueue = taskqueue_create("nvme_taskq", M_WAITOK,
	    taskqueue_thread_enqueue, &ctrlr->taskqueue);
	taskqueue_start_threads(&ctrlr->taskqueue, 1, PI_DISK, "nvme taskq");

	ctrlr->is_resetting = 0;
	ctrlr->is_initialized = 0;
	ctrlr->notification_sent = 0;
	TASK_INIT(&ctrlr->reset_task, 0, nvme_ctrlr_reset_task, ctrlr);
	TASK_INIT(&ctrlr->fail_req_task, 0, nvme_ctrlr_fail_req_task, ctrlr);
	STAILQ_INIT(&ctrlr->fail_req);
	ctrlr->is_failed = FALSE;

	make_dev_args_init(&md_args);
	md_args.mda_devsw = &nvme_ctrlr_cdevsw;
	md_args.mda_uid = UID_ROOT;
	md_args.mda_gid = GID_WHEEL;
	md_args.mda_mode = 0600;
	md_args.mda_unit = device_get_unit(dev);
	md_args.mda_si_drv1 = (void *)ctrlr;
	status = make_dev_s(&md_args, &ctrlr->cdev, "nvme%d",
	    device_get_unit(dev));
	if (status != 0)
		return (ENXIO);

	return (0);
}