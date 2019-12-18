#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int match_buf_len; unsigned int num_matches; int num_patterns; int pattern_buf_len; scalar_t__ status; union ccb* matches; union ccb* patterns; } ;
struct TYPE_9__ {int priority; } ;
struct TYPE_14__ {scalar_t__ path_id; int status; TYPE_2__ pinfo; void* target_lun; void* target_id; void* func_code; } ;
struct TYPE_8__ {void* flags; } ;
struct bus_match_result {scalar_t__ path_id; } ;
struct TYPE_12__ {struct bus_match_result bus_result; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct TYPE_11__ {TYPE_3__ bus_pattern; } ;
union ccb {scalar_t__ type; TYPE_6__ cdm; TYPE_7__ ccb_h; TYPE_1__ crcn; TYPE_5__ result; TYPE_4__ pattern; } ;
struct dev_match_result {scalar_t__ type; TYPE_6__ cdm; TYPE_7__ ccb_h; TYPE_1__ crcn; TYPE_5__ result; TYPE_4__ pattern; } ;
struct dev_match_pattern {scalar_t__ type; TYPE_6__ cdm; TYPE_7__ ccb_h; TYPE_1__ crcn; TYPE_5__ result; TYPE_4__ pattern; } ;
typedef  scalar_t__ path_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_MATCH_ANY ; 
 int /*<<< orphan*/  CAMIOCOMMAND ; 
 scalar_t__ CAM_BUS_WILDCARD ; 
 scalar_t__ CAM_DEV_MATCH_LAST ; 
 scalar_t__ CAM_DEV_MATCH_MORE ; 
 void* CAM_FLAG_NONE ; 
 void* CAM_LUN_WILDCARD ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 void* CAM_TARGET_WILDCARD ; 
 scalar_t__ CAM_XPT_PATH_ID ; 
 scalar_t__ DEV_MATCH_BUS ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  XPT_DEVICE ; 
 void* XPT_DEV_MATCH ; 
 void* XPT_RESET_BUS ; 
 void* XPT_SCAN_BUS ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  free (union ccb*) ; 
 int ioctl (int,int /*<<< orphan*/ ,union ccb*) ; 
 union ccb* malloc (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warn (char*,...) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
rescan_or_reset_bus(path_id_t bus, int rescan)
{
	union ccb *ccb = NULL, *matchccb = NULL;
	int fd = -1, retval;
	int bufsize;

	retval = 0;

	if ((fd = open(XPT_DEVICE, O_RDWR)) < 0) {
		warnx("error opening transport layer device %s", XPT_DEVICE);
		warn("%s", XPT_DEVICE);
		return (1);
	}

	ccb = malloc(sizeof(*ccb));
	if (ccb == NULL) {
		warn("failed to allocate CCB");
		retval = 1;
		goto bailout;
	}
	bzero(ccb, sizeof(*ccb));

	if (bus != CAM_BUS_WILDCARD) {
		ccb->ccb_h.func_code = rescan ? XPT_SCAN_BUS : XPT_RESET_BUS;
		ccb->ccb_h.path_id = bus;
		ccb->ccb_h.target_id = CAM_TARGET_WILDCARD;
		ccb->ccb_h.target_lun = CAM_LUN_WILDCARD;
		ccb->crcn.flags = CAM_FLAG_NONE;

		/* run this at a low priority */
		ccb->ccb_h.pinfo.priority = 5;

		if (ioctl(fd, CAMIOCOMMAND, ccb) == -1) {
			warn("CAMIOCOMMAND ioctl failed");
			retval = 1;
			goto bailout;
		}

		if ((ccb->ccb_h.status & CAM_STATUS_MASK) == CAM_REQ_CMP) {
			fprintf(stdout, "%s of bus %d was successful\n",
			    rescan ? "Re-scan" : "Reset", bus);
		} else {
			fprintf(stdout, "%s of bus %d returned error %#x\n",
				rescan ? "Re-scan" : "Reset", bus,
				ccb->ccb_h.status & CAM_STATUS_MASK);
			retval = 1;
		}

		goto bailout;
	}


	/*
	 * The right way to handle this is to modify the xpt so that it can
	 * handle a wildcarded bus in a rescan or reset CCB.  At the moment
	 * that isn't implemented, so instead we enumerate the buses and
	 * send the rescan or reset to those buses in the case where the
	 * given bus is -1 (wildcard).  We don't send a rescan or reset
	 * to the xpt bus; sending a rescan to the xpt bus is effectively a
	 * no-op, sending a rescan to the xpt bus would result in a status of
	 * CAM_REQ_INVALID.
	 */
	matchccb = malloc(sizeof(*matchccb));
	if (matchccb == NULL) {
		warn("failed to allocate CCB");
		retval = 1;
		goto bailout;
	}
	bzero(matchccb, sizeof(*matchccb));
	matchccb->ccb_h.func_code = XPT_DEV_MATCH;
	matchccb->ccb_h.path_id = CAM_BUS_WILDCARD;
	bufsize = sizeof(struct dev_match_result) * 20;
	matchccb->cdm.match_buf_len = bufsize;
	matchccb->cdm.matches=(struct dev_match_result *)malloc(bufsize);
	if (matchccb->cdm.matches == NULL) {
		warnx("can't malloc memory for matches");
		retval = 1;
		goto bailout;
	}
	matchccb->cdm.num_matches = 0;

	matchccb->cdm.num_patterns = 1;
	matchccb->cdm.pattern_buf_len = sizeof(struct dev_match_pattern);

	matchccb->cdm.patterns = (struct dev_match_pattern *)malloc(
		matchccb->cdm.pattern_buf_len);
	if (matchccb->cdm.patterns == NULL) {
		warnx("can't malloc memory for patterns");
		retval = 1;
		goto bailout;
	}
	matchccb->cdm.patterns[0].type = DEV_MATCH_BUS;
	matchccb->cdm.patterns[0].pattern.bus_pattern.flags = BUS_MATCH_ANY;

	do {
		unsigned int i;

		if (ioctl(fd, CAMIOCOMMAND, matchccb) == -1) {
			warn("CAMIOCOMMAND ioctl failed");
			retval = 1;
			goto bailout;
		}

		if ((matchccb->ccb_h.status != CAM_REQ_CMP)
		 || ((matchccb->cdm.status != CAM_DEV_MATCH_LAST)
		   && (matchccb->cdm.status != CAM_DEV_MATCH_MORE))) {
			warnx("got CAM error %#x, CDM error %d\n",
			      matchccb->ccb_h.status, matchccb->cdm.status);
			retval = 1;
			goto bailout;
		}

		for (i = 0; i < matchccb->cdm.num_matches; i++) {
			struct bus_match_result *bus_result;

			/* This shouldn't happen. */
			if (matchccb->cdm.matches[i].type != DEV_MATCH_BUS)
				continue;

			bus_result =&matchccb->cdm.matches[i].result.bus_result;

			/*
			 * We don't want to rescan or reset the xpt bus.
			 * See above.
			 */
			if (bus_result->path_id == CAM_XPT_PATH_ID)
				continue;

			ccb->ccb_h.func_code = rescan ? XPT_SCAN_BUS :
						       XPT_RESET_BUS;
			ccb->ccb_h.path_id = bus_result->path_id;
			ccb->ccb_h.target_id = CAM_TARGET_WILDCARD;
			ccb->ccb_h.target_lun = CAM_LUN_WILDCARD;
			ccb->crcn.flags = CAM_FLAG_NONE;

			/* run this at a low priority */
			ccb->ccb_h.pinfo.priority = 5;

			if (ioctl(fd, CAMIOCOMMAND, ccb) == -1) {
				warn("CAMIOCOMMAND ioctl failed");
				retval = 1;
				goto bailout;
			}

			if ((ccb->ccb_h.status & CAM_STATUS_MASK)==CAM_REQ_CMP){
				fprintf(stdout, "%s of bus %d was successful\n",
					rescan? "Re-scan" : "Reset",
					bus_result->path_id);
			} else {
				/*
				 * Don't bail out just yet, maybe the other
				 * rescan or reset commands will complete
				 * successfully.
				 */
				fprintf(stderr, "%s of bus %d returned error "
					"%#x\n", rescan? "Re-scan" : "Reset",
					bus_result->path_id,
					ccb->ccb_h.status & CAM_STATUS_MASK);
				retval = 1;
			}
		}
	} while ((matchccb->ccb_h.status == CAM_REQ_CMP)
		 && (matchccb->cdm.status == CAM_DEV_MATCH_MORE));

bailout:

	if (fd != -1)
		close(fd);

	if (matchccb != NULL) {
		free(matchccb->cdm.patterns);
		free(matchccb->cdm.matches);
		free(matchccb);
	}
	free(ccb);

	return (retval);
}