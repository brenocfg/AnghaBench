#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmpstr ;
struct ctl_lun_create_params {int flags; int device_type; int lun_size_bytes; int blocksize_bytes; char* serial_num; char* device_id; scalar_t__ req_lun_id; } ;
struct TYPE_3__ {struct ctl_lun_create_params create; } ;
struct ctl_lun_req {int /*<<< orphan*/  status; int /*<<< orphan*/  error_str; int /*<<< orphan*/  args_nvl; TYPE_1__ reqdata; } ;
struct ctl_be_lun {int lun_type; int flags; int blocksize; int maxlba; int /*<<< orphan*/  options; scalar_t__ lun_id; scalar_t__ device_id; scalar_t__ serial_num; int /*<<< orphan*/ * be; int /*<<< orphan*/  lun_config_status; int /*<<< orphan*/  lun_shutdown; scalar_t__ req_lun_id; struct ctl_be_block_lun* be_lun; } ;
struct ctl_be_block_softc {int num_luns; int /*<<< orphan*/  lock; int /*<<< orphan*/  lun_list; } ;
struct ctl_be_block_lun {int flags; int size_bytes; int size_blocks; int num_threads; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/ * lun_zone; struct ctl_be_block_lun* dev_path; int /*<<< orphan*/ * io_taskqueue; int /*<<< orphan*/  disk_stats; struct ctl_be_lun cbe_lun; int /*<<< orphan*/  lunname; int /*<<< orphan*/  io_task; int /*<<< orphan*/ * vn; int /*<<< orphan*/  datamove_queue; int /*<<< orphan*/  config_write_queue; int /*<<< orphan*/  config_read_queue; int /*<<< orphan*/  input_queue; struct ctl_be_block_softc* softc; struct ctl_lun_create_params params; } ;
struct TYPE_4__ {int flags; scalar_t__ ha_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLBLK_MAX_SEG ; 
 int CTL_BE_BLOCK_LUN_CONFIG_ERR ; 
 int CTL_BE_BLOCK_LUN_UNCONFIGURED ; 
 int CTL_BE_BLOCK_LUN_WAITING ; 
 int CTL_FLAG_ACTIVE_SHELF ; 
 scalar_t__ CTL_HA_MODE_SER_ONLY ; 
 int /*<<< orphan*/  CTL_LUN_ERROR ; 
 int CTL_LUN_FLAG_DEVID ; 
 int CTL_LUN_FLAG_DEV_TYPE ; 
 int CTL_LUN_FLAG_ID_REQ ; 
 int CTL_LUN_FLAG_NO_MEDIA ; 
 int CTL_LUN_FLAG_PRIMARY ; 
 int CTL_LUN_FLAG_SERIAL_NUM ; 
 int /*<<< orphan*/  CTL_LUN_OK ; 
 int /*<<< orphan*/  CTL_LUN_WARNING ; 
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_OTHER ; 
 int DEVSTAT_TYPE_IF_OTHER ; 
 int EINTR ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CTLBLK ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PCATCH ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ctl_be_block_lun*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct ctl_be_block_lun*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctl_be_block_lun*) ; 
 int T_CDROM ; 
 int T_DIRECT ; 
 int cbb_num_threads ; 
 TYPE_2__* control_softc ; 
 int ctl_add_lun (struct ctl_be_lun*) ; 
 int /*<<< orphan*/  ctl_be_block_close (struct ctl_be_block_lun*) ; 
 int /*<<< orphan*/  ctl_be_block_driver ; 
 int /*<<< orphan*/  ctl_be_block_lun ; 
 int /*<<< orphan*/  ctl_be_block_lun_config_status ; 
 int /*<<< orphan*/  ctl_be_block_lun_shutdown ; 
 int ctl_be_block_open (struct ctl_be_block_lun*,struct ctl_lun_req*) ; 
 int /*<<< orphan*/  ctl_be_block_worker ; 
 int /*<<< orphan*/  devstat_new_entry (char*,scalar_t__,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* dnvlist_get_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct ctl_be_block_lun*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 struct ctl_be_block_lun* malloc (int,int /*<<< orphan*/ ,int) ; 
 int msleep (struct ctl_be_block_lun*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int taskqueue_start_threads (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/ * uma_zcreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_be_block_create(struct ctl_be_block_softc *softc, struct ctl_lun_req *req)
{
	struct ctl_be_lun *cbe_lun;
	struct ctl_be_block_lun *be_lun;
	struct ctl_lun_create_params *params;
	char num_thread_str[16];
	char tmpstr[32];
	const char *value;
	int retval, num_threads;
	int tmp_num_threads;

	params = &req->reqdata.create;
	retval = 0;
	req->status = CTL_LUN_OK;

	be_lun = malloc(sizeof(*be_lun), M_CTLBLK, M_ZERO | M_WAITOK);
	cbe_lun = &be_lun->cbe_lun;
	cbe_lun->be_lun = be_lun;
	be_lun->params = req->reqdata.create;
	be_lun->softc = softc;
	STAILQ_INIT(&be_lun->input_queue);
	STAILQ_INIT(&be_lun->config_read_queue);
	STAILQ_INIT(&be_lun->config_write_queue);
	STAILQ_INIT(&be_lun->datamove_queue);
	sprintf(be_lun->lunname, "cblk%d", softc->num_luns);
	mtx_init(&be_lun->io_lock, "cblk io lock", NULL, MTX_DEF);
	mtx_init(&be_lun->queue_lock, "cblk queue lock", NULL, MTX_DEF);
	cbe_lun->options = nvlist_clone(req->args_nvl);
	be_lun->lun_zone = uma_zcreate(be_lun->lunname, CTLBLK_MAX_SEG,
	    NULL, NULL, NULL, NULL, /*align*/ 0, /*flags*/0);
	if (be_lun->lun_zone == NULL) {
		snprintf(req->error_str, sizeof(req->error_str),
			 "error allocating UMA zone");
		goto bailout_error;
	}

	if (params->flags & CTL_LUN_FLAG_DEV_TYPE)
		cbe_lun->lun_type = params->device_type;
	else
		cbe_lun->lun_type = T_DIRECT;
	be_lun->flags = CTL_BE_BLOCK_LUN_UNCONFIGURED;
	cbe_lun->flags = 0;
	value = dnvlist_get_string(cbe_lun->options, "ha_role", NULL);
	if (value != NULL) {
		if (strcmp(value, "primary") == 0)
			cbe_lun->flags |= CTL_LUN_FLAG_PRIMARY;
	} else if (control_softc->flags & CTL_FLAG_ACTIVE_SHELF)
		cbe_lun->flags |= CTL_LUN_FLAG_PRIMARY;

	if (cbe_lun->lun_type == T_DIRECT ||
	    cbe_lun->lun_type == T_CDROM) {
		be_lun->size_bytes = params->lun_size_bytes;
		if (params->blocksize_bytes != 0)
			cbe_lun->blocksize = params->blocksize_bytes;
		else if (cbe_lun->lun_type == T_CDROM)
			cbe_lun->blocksize = 2048;
		else
			cbe_lun->blocksize = 512;
		be_lun->size_blocks = be_lun->size_bytes / cbe_lun->blocksize;
		cbe_lun->maxlba = (be_lun->size_blocks == 0) ?
		    0 : (be_lun->size_blocks - 1);

		if ((cbe_lun->flags & CTL_LUN_FLAG_PRIMARY) ||
		    control_softc->ha_mode == CTL_HA_MODE_SER_ONLY) {
			retval = ctl_be_block_open(be_lun, req);
			if (retval != 0) {
				retval = 0;
				req->status = CTL_LUN_WARNING;
			}
		}
		num_threads = cbb_num_threads;
	} else {
		num_threads = 1;
	}

	value = dnvlist_get_string(cbe_lun->options, "num_threads", NULL);
	if (value != NULL) {
		tmp_num_threads = strtol(value, NULL, 0);

		/*
		 * We don't let the user specify less than one
		 * thread, but hope he's clueful enough not to
		 * specify 1000 threads.
		 */
		if (tmp_num_threads < 1) {
			snprintf(req->error_str, sizeof(req->error_str),
				 "invalid number of threads %s",
				 num_thread_str);
			goto bailout_error;
		}
		num_threads = tmp_num_threads;
	}

	if (be_lun->vn == NULL)
		cbe_lun->flags |= CTL_LUN_FLAG_NO_MEDIA;
	/* Tell the user the blocksize we ended up using */
	params->lun_size_bytes = be_lun->size_bytes;
	params->blocksize_bytes = cbe_lun->blocksize;
	if (params->flags & CTL_LUN_FLAG_ID_REQ) {
		cbe_lun->req_lun_id = params->req_lun_id;
		cbe_lun->flags |= CTL_LUN_FLAG_ID_REQ;
	} else
		cbe_lun->req_lun_id = 0;

	cbe_lun->lun_shutdown = ctl_be_block_lun_shutdown;
	cbe_lun->lun_config_status = ctl_be_block_lun_config_status;
	cbe_lun->be = &ctl_be_block_driver;

	if ((params->flags & CTL_LUN_FLAG_SERIAL_NUM) == 0) {
		snprintf(tmpstr, sizeof(tmpstr), "MYSERIAL%04d",
			 softc->num_luns);
		strncpy((char *)cbe_lun->serial_num, tmpstr,
			MIN(sizeof(cbe_lun->serial_num), sizeof(tmpstr)));

		/* Tell the user what we used for a serial number */
		strncpy((char *)params->serial_num, tmpstr,
			MIN(sizeof(params->serial_num), sizeof(tmpstr)));
	} else { 
		strncpy((char *)cbe_lun->serial_num, params->serial_num,
			MIN(sizeof(cbe_lun->serial_num),
			sizeof(params->serial_num)));
	}
	if ((params->flags & CTL_LUN_FLAG_DEVID) == 0) {
		snprintf(tmpstr, sizeof(tmpstr), "MYDEVID%04d", softc->num_luns);
		strncpy((char *)cbe_lun->device_id, tmpstr,
			MIN(sizeof(cbe_lun->device_id), sizeof(tmpstr)));

		/* Tell the user what we used for a device ID */
		strncpy((char *)params->device_id, tmpstr,
			MIN(sizeof(params->device_id), sizeof(tmpstr)));
	} else {
		strncpy((char *)cbe_lun->device_id, params->device_id,
			MIN(sizeof(cbe_lun->device_id),
			    sizeof(params->device_id)));
	}

	TASK_INIT(&be_lun->io_task, /*priority*/0, ctl_be_block_worker, be_lun);

	be_lun->io_taskqueue = taskqueue_create(be_lun->lunname, M_WAITOK,
	    taskqueue_thread_enqueue, /*context*/&be_lun->io_taskqueue);

	if (be_lun->io_taskqueue == NULL) {
		snprintf(req->error_str, sizeof(req->error_str),
			 "unable to create taskqueue");
		goto bailout_error;
	}

	/*
	 * Note that we start the same number of threads by default for
	 * both the file case and the block device case.  For the file
	 * case, we need multiple threads to allow concurrency, because the
	 * vnode interface is designed to be a blocking interface.  For the
	 * block device case, ZFS zvols at least will block the caller's
	 * context in many instances, and so we need multiple threads to
	 * overcome that problem.  Other block devices don't need as many
	 * threads, but they shouldn't cause too many problems.
	 *
	 * If the user wants to just have a single thread for a block
	 * device, he can specify that when the LUN is created, or change
	 * the tunable/sysctl to alter the default number of threads.
	 */
	retval = taskqueue_start_threads(&be_lun->io_taskqueue,
					 /*num threads*/num_threads,
					 /*priority*/PUSER,
					 /*thread name*/
					 "%s taskq", be_lun->lunname);

	if (retval != 0)
		goto bailout_error;

	be_lun->num_threads = num_threads;

	mtx_lock(&softc->lock);
	softc->num_luns++;
	STAILQ_INSERT_TAIL(&softc->lun_list, be_lun, links);

	mtx_unlock(&softc->lock);

	retval = ctl_add_lun(&be_lun->cbe_lun);
	if (retval != 0) {
		mtx_lock(&softc->lock);
		STAILQ_REMOVE(&softc->lun_list, be_lun, ctl_be_block_lun,
			      links);
		softc->num_luns--;
		mtx_unlock(&softc->lock);
		snprintf(req->error_str, sizeof(req->error_str),
			 "ctl_add_lun() returned error %d, see dmesg for "
			 "details", retval);
		retval = 0;
		goto bailout_error;
	}

	mtx_lock(&softc->lock);

	/*
	 * Tell the config_status routine that we're waiting so it won't
	 * clean up the LUN in the event of an error.
	 */
	be_lun->flags |= CTL_BE_BLOCK_LUN_WAITING;

	while (be_lun->flags & CTL_BE_BLOCK_LUN_UNCONFIGURED) {
		retval = msleep(be_lun, &softc->lock, PCATCH, "ctlblk", 0);
		if (retval == EINTR)
			break;
	}
	be_lun->flags &= ~CTL_BE_BLOCK_LUN_WAITING;

	if (be_lun->flags & CTL_BE_BLOCK_LUN_CONFIG_ERR) {
		snprintf(req->error_str, sizeof(req->error_str),
			 "LUN configuration error, see dmesg for details");
		STAILQ_REMOVE(&softc->lun_list, be_lun, ctl_be_block_lun,
			      links);
		softc->num_luns--;
		mtx_unlock(&softc->lock);
		goto bailout_error;
	} else {
		params->req_lun_id = cbe_lun->lun_id;
	}

	mtx_unlock(&softc->lock);

	be_lun->disk_stats = devstat_new_entry("cbb", params->req_lun_id,
					       cbe_lun->blocksize,
					       DEVSTAT_ALL_SUPPORTED,
					       cbe_lun->lun_type
					       | DEVSTAT_TYPE_IF_OTHER,
					       DEVSTAT_PRIORITY_OTHER);

	return (retval);

bailout_error:
	req->status = CTL_LUN_ERROR;

	if (be_lun->io_taskqueue != NULL)
		taskqueue_free(be_lun->io_taskqueue);
	ctl_be_block_close(be_lun);
	if (be_lun->dev_path != NULL)
		free(be_lun->dev_path, M_CTLBLK);
	if (be_lun->lun_zone != NULL)
		uma_zdestroy(be_lun->lun_zone);
	nvlist_destroy(cbe_lun->options);
	mtx_destroy(&be_lun->queue_lock);
	mtx_destroy(&be_lun->io_lock);
	free(be_lun, M_CTLBLK);

	return (retval);
}