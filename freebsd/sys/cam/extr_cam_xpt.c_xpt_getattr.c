#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
struct scsi_vpd_id_descriptor {int proto_codeset; size_t length; char* identifier; int id_type; } ;
struct scsi_vpd_device_id {int dummy; } ;
struct TYPE_2__ {int status; int /*<<< orphan*/  path; int /*<<< orphan*/  func_code; } ;
struct ccb_dev_advinfo {size_t bufsiz; char* buf; int buftype; scalar_t__ provsiz; TYPE_1__ ccb_h; int /*<<< orphan*/  flags; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  cdai ;

/* Variables and functions */
 int CAM_DEV_QFRZN ; 
 int /*<<< orphan*/  CAM_PRIORITY_NORMAL ; 
 size_t CAM_SCSI_DEVID_MAXLEN ; 
 int /*<<< orphan*/  CDAI_FLAG_NONE ; 
 int CDAI_TYPE_PHYS_PATH ; 
#define  CDAI_TYPE_SCSI_DEVID 128 
 int CDAI_TYPE_SERIAL_NUM ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int SVPD_ID_CODESET_ASCII ; 
 int SVPD_ID_CODESET_MASK ; 
 int SVPD_ID_CODESET_UTF8 ; 
 int SVPD_ID_TYPE_MASK ; 
 int SVPD_ID_TYPE_UUID ; 
 int /*<<< orphan*/  XPT_DEV_ADVINFO ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  cam_release_devq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ccb_dev_advinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_devid_is_lun_eui64 ; 
 int /*<<< orphan*/  scsi_devid_is_lun_md5 ; 
 int /*<<< orphan*/  scsi_devid_is_lun_naa ; 
 int /*<<< orphan*/  scsi_devid_is_lun_name ; 
 int /*<<< orphan*/  scsi_devid_is_lun_t10 ; 
 int /*<<< orphan*/  scsi_devid_is_lun_uuid ; 
 struct scsi_vpd_id_descriptor* scsi_get_devid (struct scsi_vpd_device_id*,scalar_t__,int /*<<< orphan*/ ) ; 
 int sprintf (char*,char*,...) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strnlen (char*,int) ; 
 int /*<<< orphan*/  xpt_action (union ccb*) ; 
 int /*<<< orphan*/  xpt_path_assert (struct cam_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_setup_ccb (TYPE_1__*,struct cam_path*,int /*<<< orphan*/ ) ; 

int
xpt_getattr(char *buf, size_t len, const char *attr, struct cam_path *path)
{
	int ret = -1, l, o;
	struct ccb_dev_advinfo cdai;
	struct scsi_vpd_device_id *did;
	struct scsi_vpd_id_descriptor *idd;

	xpt_path_assert(path, MA_OWNED);

	memset(&cdai, 0, sizeof(cdai));
	xpt_setup_ccb(&cdai.ccb_h, path, CAM_PRIORITY_NORMAL);
	cdai.ccb_h.func_code = XPT_DEV_ADVINFO;
	cdai.flags = CDAI_FLAG_NONE;
	cdai.bufsiz = len;
	cdai.buf = buf;

	if (!strcmp(attr, "GEOM::ident"))
		cdai.buftype = CDAI_TYPE_SERIAL_NUM;
	else if (!strcmp(attr, "GEOM::physpath"))
		cdai.buftype = CDAI_TYPE_PHYS_PATH;
	else if (strcmp(attr, "GEOM::lunid") == 0 ||
		 strcmp(attr, "GEOM::lunname") == 0) {
		cdai.buftype = CDAI_TYPE_SCSI_DEVID;
		cdai.bufsiz = CAM_SCSI_DEVID_MAXLEN;
		cdai.buf = malloc(cdai.bufsiz, M_CAMXPT, M_NOWAIT);
		if (cdai.buf == NULL) {
			ret = ENOMEM;
			goto out;
		}
	} else
		goto out;

	xpt_action((union ccb *)&cdai); /* can only be synchronous */
	if ((cdai.ccb_h.status & CAM_DEV_QFRZN) != 0)
		cam_release_devq(cdai.ccb_h.path, 0, 0, 0, FALSE);
	if (cdai.provsiz == 0)
		goto out;
	switch(cdai.buftype) {
	case CDAI_TYPE_SCSI_DEVID:
		did = (struct scsi_vpd_device_id *)cdai.buf;
		if (strcmp(attr, "GEOM::lunid") == 0) {
			idd = scsi_get_devid(did, cdai.provsiz,
			    scsi_devid_is_lun_naa);
			if (idd == NULL)
				idd = scsi_get_devid(did, cdai.provsiz,
				    scsi_devid_is_lun_eui64);
			if (idd == NULL)
				idd = scsi_get_devid(did, cdai.provsiz,
				    scsi_devid_is_lun_uuid);
			if (idd == NULL)
				idd = scsi_get_devid(did, cdai.provsiz,
				    scsi_devid_is_lun_md5);
		} else
			idd = NULL;

		if (idd == NULL)
			idd = scsi_get_devid(did, cdai.provsiz,
			    scsi_devid_is_lun_t10);
		if (idd == NULL)
			idd = scsi_get_devid(did, cdai.provsiz,
			    scsi_devid_is_lun_name);
		if (idd == NULL)
			break;

		ret = 0;
		if ((idd->proto_codeset & SVPD_ID_CODESET_MASK) ==
		    SVPD_ID_CODESET_ASCII) {
			if (idd->length < len) {
				for (l = 0; l < idd->length; l++)
					buf[l] = idd->identifier[l] ?
					    idd->identifier[l] : ' ';
				buf[l] = 0;
			} else
				ret = EFAULT;
			break;
		}
		if ((idd->proto_codeset & SVPD_ID_CODESET_MASK) ==
		    SVPD_ID_CODESET_UTF8) {
			l = strnlen(idd->identifier, idd->length);
			if (l < len) {
				bcopy(idd->identifier, buf, l);
				buf[l] = 0;
			} else
				ret = EFAULT;
			break;
		}
		if ((idd->id_type & SVPD_ID_TYPE_MASK) ==
		    SVPD_ID_TYPE_UUID && idd->identifier[0] == 0x10) {
			if ((idd->length - 2) * 2 + 4 >= len) {
				ret = EFAULT;
				break;
			}
			for (l = 2, o = 0; l < idd->length; l++) {
				if (l == 6 || l == 8 || l == 10 || l == 12)
				    o += sprintf(buf + o, "-");
				o += sprintf(buf + o, "%02x",
				    idd->identifier[l]);
			}
			break;
		}
		if (idd->length * 2 < len) {
			for (l = 0; l < idd->length; l++)
				sprintf(buf + l * 2, "%02x",
				    idd->identifier[l]);
		} else
				ret = EFAULT;
		break;
	default:
		if (cdai.provsiz < len) {
			cdai.buf[cdai.provsiz] = 0;
			ret = 0;
		} else
			ret = EFAULT;
		break;
	}

out:
	if ((char *)cdai.buf != buf)
		free(cdai.buf, M_CAMXPT);
	return ret;
}