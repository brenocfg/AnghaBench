#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int num_matches; size_t match_buf_len; int num_patterns; size_t pattern_buf_len; scalar_t__ status; TYPE_6__* matches; TYPE_6__* patterns; } ;
struct TYPE_8__ {int status; int /*<<< orphan*/  func_code; } ;
union ccb {TYPE_5__ cdm; TYPE_2__ ccb_h; } ;
struct dev_match_result {int dummy; } ;
struct dev_match_pattern {int dummy; } ;
struct bus_match_pattern {int flags; scalar_t__ bus_id; int /*<<< orphan*/  unit_number; int /*<<< orphan*/  dev_name; } ;
typedef  int /*<<< orphan*/  path_id_t ;
typedef  int /*<<< orphan*/  ccb ;
struct TYPE_9__ {int /*<<< orphan*/  path_id; } ;
struct TYPE_10__ {TYPE_3__ bus_result; } ;
struct TYPE_7__ {struct bus_match_pattern bus_pattern; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_4__ result; TYPE_1__ pattern; } ;

/* Variables and functions */
 int BUS_MATCH_BUS_ID ; 
 int BUS_MATCH_NAME ; 
 int BUS_MATCH_UNIT ; 
 int /*<<< orphan*/  CAMIOCOMMAND ; 
 scalar_t__ CAM_DEV_MATCH_LAST ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 scalar_t__ DEV_MATCH_BUS ; 
 int EIO ; 
 int ENOENT ; 
 int ENXIO ; 
 int /*<<< orphan*/  XPT_DEV_MATCH ; 
 int /*<<< orphan*/  bzero (union ccb*,int) ; 
 void* calloc (int,size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_6__*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  mpt_unit ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  warnx (char*,int,scalar_t__) ; 
 scalar_t__ xpt_open () ; 
 int /*<<< orphan*/  xptfd ; 

__attribute__((used)) static int
fetch_path_id(path_id_t *path_id)
{
	struct bus_match_pattern *b;
	union ccb ccb;
	size_t bufsize;
	int error;

	if (xpt_open() < 0)
		return (ENXIO);

	/* First, find the path id of bus 0 for this mpt controller. */
	bzero(&ccb, sizeof(ccb));

	ccb.ccb_h.func_code = XPT_DEV_MATCH;

	bufsize = sizeof(struct dev_match_result) * 1;
	ccb.cdm.num_matches = 0;
	ccb.cdm.match_buf_len = bufsize;
	ccb.cdm.matches = calloc(1, bufsize);

	bufsize = sizeof(struct dev_match_pattern) * 1;
	ccb.cdm.num_patterns = 1;
	ccb.cdm.pattern_buf_len = bufsize;
	ccb.cdm.patterns = calloc(1, bufsize);

	/* Match mptX bus 0. */
	ccb.cdm.patterns[0].type = DEV_MATCH_BUS;
	b = &ccb.cdm.patterns[0].pattern.bus_pattern;
	snprintf(b->dev_name, sizeof(b->dev_name), "mpt");
	b->unit_number = mpt_unit;
	b->bus_id = 0;
	b->flags = BUS_MATCH_NAME | BUS_MATCH_UNIT | BUS_MATCH_BUS_ID;

	if (ioctl(xptfd, CAMIOCOMMAND, &ccb) < 0) {
		error = errno;
		free(ccb.cdm.matches);
		free(ccb.cdm.patterns);
		return (error);
	}
	free(ccb.cdm.patterns);

	if (((ccb.ccb_h.status & CAM_STATUS_MASK) != CAM_REQ_CMP) ||
	    (ccb.cdm.status != CAM_DEV_MATCH_LAST)) {
		warnx("fetch_path_id got CAM error %#x, CDM error %d\n",
		    ccb.ccb_h.status, ccb.cdm.status);
		free(ccb.cdm.matches);
		return (EIO);
	}

	/* We should have exactly 1 match for the bus. */
	if (ccb.cdm.num_matches != 1 ||
	    ccb.cdm.matches[0].type != DEV_MATCH_BUS) {
		free(ccb.cdm.matches);
		return (ENOENT);
	}
	*path_id = ccb.cdm.matches[0].result.bus_result.path_id;
	free(ccb.cdm.matches);
	return (0);
}