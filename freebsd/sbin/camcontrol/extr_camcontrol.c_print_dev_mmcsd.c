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
struct TYPE_2__ {int /*<<< orphan*/  func_code; int /*<<< orphan*/  flags; } ;
struct ccb_dev_advinfo {int bufsiz; int /*<<< orphan*/ * buf; int /*<<< orphan*/  buftype; int /*<<< orphan*/  flags; TYPE_1__ ccb_h; } ;
union ccb {struct ccb_dev_advinfo cdai; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct mmc_params {char* model; int card_features; } ;
struct device_match_result {int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; } ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DIR_IN ; 
 int CARD_FEATURE_SDIO ; 
 int /*<<< orphan*/  CDAI_FLAG_NONE ; 
 int /*<<< orphan*/  CDAI_TYPE_MMC_PARAMS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  XPT_DEV_ADVINFO ; 
 int /*<<< orphan*/  cam_close_device (struct cam_device*) ; 
 int /*<<< orphan*/  cam_errbuf ; 
 int /*<<< orphan*/  cam_freeccb (union ccb*) ; 
 union ccb* cam_getccb (struct cam_device*) ; 
 struct cam_device* cam_open_btl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cam_send_ccb (struct cam_device*,union ccb*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
print_dev_mmcsd(struct device_match_result *dev_result, char *tmpstr)
{
	union ccb *ccb;
	struct ccb_dev_advinfo *advi;
	struct cam_device *dev;
	struct mmc_params mmc_ident_data;

	dev = cam_open_btl(dev_result->path_id, dev_result->target_id,
	    dev_result->target_lun, O_RDWR, NULL);
	if (dev == NULL) {
		warnx("%s", cam_errbuf);
		return (1);
	}

	ccb = cam_getccb(dev);
	if (ccb == NULL) {
		warnx("couldn't allocate CCB");
		cam_close_device(dev);
		return (1);
	}

	advi = &ccb->cdai;
	advi->ccb_h.flags = CAM_DIR_IN;
	advi->ccb_h.func_code = XPT_DEV_ADVINFO;
	advi->flags = CDAI_FLAG_NONE;
	advi->buftype = CDAI_TYPE_MMC_PARAMS;
	advi->bufsiz = sizeof(struct mmc_params);
	advi->buf = (uint8_t *)&mmc_ident_data;

	if (cam_send_ccb(dev, ccb) < 0) {
		warn("error sending XPT_DEV_ADVINFO CCB");
		cam_freeccb(ccb);
		cam_close_device(dev);
		return (1);
	}

	if (strlen(mmc_ident_data.model) > 0) {
		sprintf(tmpstr, "<%s>", mmc_ident_data.model);
	} else {
		sprintf(tmpstr, "<%s card>",
		    mmc_ident_data.card_features &
		    CARD_FEATURE_SDIO ? "SDIO" : "unknown");
	}

	cam_freeccb(ccb);
	cam_close_device(dev);
	return (0);
}