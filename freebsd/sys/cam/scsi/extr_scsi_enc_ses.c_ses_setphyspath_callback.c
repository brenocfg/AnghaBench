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
typedef  union ccb {int dummy; } ccb ;
struct TYPE_4__ {int status; int /*<<< orphan*/  path; void* func_code; } ;
struct ccb_dev_advinfo {char* buf; TYPE_2__ ccb_h; int /*<<< orphan*/  bufsiz; int /*<<< orphan*/  flags; void* buftype; } ;
struct cam_path {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_set; int /*<<< orphan*/  physpath; } ;
typedef  TYPE_1__ ses_setphyspath_callback_args_t ;
typedef  int /*<<< orphan*/  enc_softc_t ;
typedef  int /*<<< orphan*/  enc_element_t ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_REQ_CMP ; 
 int /*<<< orphan*/  CDAI_FLAG_NONE ; 
 int /*<<< orphan*/  CDAI_FLAG_STORE ; 
 void* CDAI_TYPE_PHYS_PATH ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_SCSIENC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 void* XPT_DEV_ADVINFO ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* sbuf_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_len (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_lock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_unlock (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_2__*,struct cam_path*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ses_setphyspath_callback(enc_softc_t *enc, enc_element_t *elm,
			 struct cam_path *path, void *arg)
{
	struct ccb_dev_advinfo cdai;
	ses_setphyspath_callback_args_t *args;
	char *old_physpath;

	args = (ses_setphyspath_callback_args_t *)arg;
	old_physpath = malloc(MAXPATHLEN, M_SCSIENC, M_WAITOK|M_ZERO);
	xpt_path_lock(path);
	xpt_setup_ccb(&cdai.ccb_h, path, CAM_PRIORITY_NORMAL);
	cdai.ccb_h.func_code = XPT_DEV_ADVINFO;
	cdai.buftype = CDAI_TYPE_PHYS_PATH;
	cdai.flags = CDAI_FLAG_NONE;
	cdai.bufsiz = MAXPATHLEN;
	cdai.buf = old_physpath;
	xpt_action((union ccb *)&cdai);
	if ((cdai.ccb_h.status & CAM_DEV_QFRZN) != 0)
		cam_release_devq(cdai.ccb_h.path, 0, 0, 0, FALSE);

	if (strcmp(old_physpath, sbuf_data(args->physpath)) != 0) {

		xpt_setup_ccb(&cdai.ccb_h, path, CAM_PRIORITY_NORMAL);
		cdai.ccb_h.func_code = XPT_DEV_ADVINFO;
		cdai.buftype = CDAI_TYPE_PHYS_PATH;
		cdai.flags = CDAI_FLAG_STORE;
		cdai.bufsiz = sbuf_len(args->physpath);
		cdai.buf = sbuf_data(args->physpath);
		xpt_action((union ccb *)&cdai);
		if ((cdai.ccb_h.status & CAM_DEV_QFRZN) != 0)
			cam_release_devq(cdai.ccb_h.path, 0, 0, 0, FALSE);
		if (cdai.ccb_h.status == CAM_REQ_CMP)
			args->num_set++;
	}
	xpt_path_unlock(path);
	free(old_physpath, M_SCSIENC);
}