#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ses_iterator {int /*<<< orphan*/  type_element_index; int /*<<< orphan*/  type_index; } ;
struct scsi_vpd_id_descriptor {int /*<<< orphan*/  identifier; } ;
struct scsi_vpd_device_id {int dummy; } ;
struct sbuf {int dummy; } ;
struct TYPE_20__ {int status; int /*<<< orphan*/  path; int /*<<< orphan*/  func_code; } ;
struct ccb_dev_advinfo {int /*<<< orphan*/  provsiz; int /*<<< orphan*/ * buf; TYPE_6__ ccb_h; int /*<<< orphan*/  bufsiz; int /*<<< orphan*/  buftype; int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {scalar_t__ num_set; struct sbuf* physpath; } ;
typedef  TYPE_2__ ses_setphyspath_callback_args_t ;
struct TYPE_15__ {int /*<<< orphan*/ * hdr; } ;
struct TYPE_17__ {char* descr; int descr_len; TYPE_1__ addl; } ;
typedef  TYPE_3__ ses_element_t ;
struct TYPE_18__ {TYPE_12__* periph; } ;
typedef  TYPE_4__ enc_softc_t ;
struct TYPE_19__ {TYPE_3__* elm_private; } ;
typedef  TYPE_5__ enc_element_t ;
struct TYPE_14__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 int CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_SCSI_DEVID_MAXLEN ; 
 int /*<<< orphan*/  CDAI_FLAG_NONE ; 
 int /*<<< orphan*/  CDAI_TYPE_SCSI_DEVID ; 
 int EIO ; 
 int /*<<< orphan*/  ENC_FREE (int /*<<< orphan*/ *) ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  M_SCSIENC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int /*<<< orphan*/  XPT_DEV_ADVINFO ; 
 int /*<<< orphan*/  cam_periph_lock (TYPE_12__*) ; 
 int /*<<< orphan*/  cam_periph_unlock (TYPE_12__*) ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isprint (char const) ; 
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/ * sbuf_new (struct sbuf*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char const) ; 
 int /*<<< orphan*/  scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_devid_is_naa_ieee_reg ; 
 struct scsi_vpd_id_descriptor* scsi_get_devid (struct scsi_vpd_device_id*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ses_paths_iter (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ses_setphyspath_callback ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ses_set_physpath(enc_softc_t *enc, enc_element_t *elm,
		 struct ses_iterator *iter)
{
	struct ccb_dev_advinfo cdai;
	ses_setphyspath_callback_args_t args;
	int i, ret;
	struct sbuf sb;
	struct scsi_vpd_id_descriptor *idd;
	uint8_t *devid;
	ses_element_t *elmpriv;
	const char *c;

	ret = EIO;
	devid = NULL;

	elmpriv = elm->elm_private;
	if (elmpriv->addl.hdr == NULL)
		goto out;

	/*
	 * Assemble the components of the physical path starting with
	 * the device ID of the enclosure itself.
	 */
	xpt_setup_ccb(&cdai.ccb_h, enc->periph->path, CAM_PRIORITY_NORMAL);
	cdai.ccb_h.func_code = XPT_DEV_ADVINFO;
	cdai.flags = CDAI_FLAG_NONE;
	cdai.buftype = CDAI_TYPE_SCSI_DEVID;
	cdai.bufsiz = CAM_SCSI_DEVID_MAXLEN;
	cdai.buf = devid = malloc(cdai.bufsiz, M_SCSIENC, M_WAITOK|M_ZERO);
	cam_periph_lock(enc->periph);
	xpt_action((union ccb *)&cdai);
	if ((cdai.ccb_h.status & CAM_DEV_QFRZN) != 0)
		cam_release_devq(cdai.ccb_h.path, 0, 0, 0, FALSE);
	cam_periph_unlock(enc->periph);
	if (cdai.ccb_h.status != CAM_REQ_CMP)
		goto out;

	idd = scsi_get_devid((struct scsi_vpd_device_id *)cdai.buf,
	    cdai.provsiz, scsi_devid_is_naa_ieee_reg);
	if (idd == NULL)
		goto out;

	if (sbuf_new(&sb, NULL, 128, SBUF_AUTOEXTEND) == NULL) {
		ret = ENOMEM;
		goto out;
	}
	/* Next, generate the physical path string */
	sbuf_printf(&sb, "id1,enc@n%jx/type@%x/slot@%x",
	    scsi_8btou64(idd->identifier), iter->type_index,
	    iter->type_element_index);
	/* Append the element descriptor if one exists */
	if (elmpriv->descr != NULL && elmpriv->descr_len > 0) {
		sbuf_cat(&sb, "/elmdesc@");
		for (i = 0, c = elmpriv->descr; i < elmpriv->descr_len;
		    i++, c++) {
			if (!isprint(*c) || isspace(*c) || *c == '/')
				sbuf_putc(&sb, '_');
			else
				sbuf_putc(&sb, *c);
		}
	}
	sbuf_finish(&sb);

	/*
	 * Set this physical path on any CAM devices with a device ID
	 * descriptor that matches one created from the SES additional
	 * status data for this element.
	 */
	args.physpath= &sb;
	args.num_set = 0;
	ses_paths_iter(enc, elm, ses_setphyspath_callback, &args);
	sbuf_delete(&sb);

	ret = args.num_set == 0 ? ENOENT : 0;

out:
	if (devid != NULL)
		ENC_FREE(devid);
	return (ret);
}