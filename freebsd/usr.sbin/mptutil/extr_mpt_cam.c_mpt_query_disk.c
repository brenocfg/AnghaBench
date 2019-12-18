#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int num_matches; size_t match_buf_len; int num_patterns; size_t pattern_buf_len; scalar_t__ status; TYPE_5__* matches; TYPE_5__* patterns; } ;
struct TYPE_7__ {int status; int /*<<< orphan*/  target_lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_4__ cdm; TYPE_2__ ccb_h; } ;
struct periph_match_result {char* periph_name; int /*<<< orphan*/  unit_number; } ;
struct periph_match_pattern {int flags; scalar_t__ target_id; int /*<<< orphan*/  periph_name; int /*<<< orphan*/  path_id; } ;
struct mpt_query_disk {int /*<<< orphan*/  devname; } ;
struct dev_match_result {int dummy; } ;
struct dev_match_pattern {int dummy; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  ccb ;
typedef  scalar_t__ U8 ;
struct TYPE_8__ {struct periph_match_result periph_result; } ;
struct TYPE_6__ {struct periph_match_pattern periph_pattern; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ result; TYPE_1__ pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAMIOCOMMAND ; 
 scalar_t__ CAM_DEV_MATCH_LAST ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int /*<<< orphan*/  CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CAM_XPT_PATH_ID ; 
 scalar_t__ DEV_MATCH_PERIPH ; 
 int EIO ; 
 int ENOENT ; 
 int ENXIO ; 
 int PERIPH_MATCH_NAME ; 
 int PERIPH_MATCH_PATH ; 
 int PERIPH_MATCH_TARGET ; 
 int /*<<< orphan*/  XPT_DEV_MATCH ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 void* calloc (int,size_t) ; 
 int errno ; 
 int fetch_path_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 scalar_t__ xpt_open () ; 
 int /*<<< orphan*/  xptfd ; 

int
mpt_query_disk(U8 VolumeBus, U8 VolumeID, struct mpt_query_disk *qd)
{
	struct periph_match_pattern *p;
	struct periph_match_result *r;
	union ccb ccb;
	path_id_t path_id;
	size_t bufsize;
	int error;

	/* mpt(4) only handles devices on bus 0. */
	if (VolumeBus != 0)
		return (ENXIO);

	if (xpt_open() < 0)
		return (ENXIO);

	/* Find the path ID of bus 0. */
	error = fetch_path_id(&path_id);
	if (error)
		return (error);

	bzero(&ccb, sizeof(ccb));

	ccb.ccb_h.func_code = XPT_DEV_MATCH;
	ccb.ccb_h.path_id = CAM_XPT_PATH_ID;
	ccb.ccb_h.target_id = CAM_TARGET_WILDCARD;
	ccb.ccb_h.target_lun = CAM_LUN_WILDCARD;

	bufsize = sizeof(struct dev_match_result) * 5;
	ccb.cdm.num_matches = 0;
	ccb.cdm.match_buf_len = bufsize;
	ccb.cdm.matches = calloc(1, bufsize);

	bufsize = sizeof(struct dev_match_pattern) * 1;
	ccb.cdm.num_patterns = 1;
	ccb.cdm.pattern_buf_len = bufsize;
	ccb.cdm.patterns = calloc(1, bufsize);

	/* Look for a "da" device at the specified target and lun. */
	ccb.cdm.patterns[0].type = DEV_MATCH_PERIPH;
	p = &ccb.cdm.patterns[0].pattern.periph_pattern;
	p->path_id = path_id;
	snprintf(p->periph_name, sizeof(p->periph_name), "da");
	p->target_id = VolumeID;
	p->flags = PERIPH_MATCH_PATH | PERIPH_MATCH_NAME | PERIPH_MATCH_TARGET;

	if (ioctl(xptfd, CAMIOCOMMAND, &ccb) < 0) {
		error = errno;
		free(ccb.cdm.matches);
		free(ccb.cdm.patterns);
		return (error);
	}
	free(ccb.cdm.patterns);

	if (((ccb.ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) ||
	    (ccb.cdm.status != CAM_DEV_MATCH_LAST)) {
		warnx("mpt_query_disk got CAM error %#x, CDM error %d\n",
		    ccb.ccb_h.status, ccb.cdm.status);
		free(ccb.cdm.matches);
		return (EIO);
	}

	/*
	 * We should have exactly 1 match for the peripheral.
	 * However, if we don't get a match, don't print an error
	 * message and return ENOENT.
	 */
	if (ccb.cdm.num_matches == 0) {
		free(ccb.cdm.matches);
		return (ENOENT);
	}
	if (ccb.cdm.num_matches != 1) {
		warnx("mpt_query_disk got %d matches, expected 1",
		    ccb.cdm.num_matches);
		free(ccb.cdm.matches);
		return (EIO);
	}
	if (ccb.cdm.matches[0].type != DEV_MATCH_PERIPH) {
		warnx("mpt_query_disk got wrong CAM match");
		free(ccb.cdm.matches);
		return (EIO);
	}

	/* Copy out the data. */
	r = &ccb.cdm.matches[1].result.periph_result;
	snprintf(qd->devname, sizeof(qd->devname), "%s%d", r->periph_name,
	    r->unit_number);
	free(ccb.cdm.matches);

	return (0);
}