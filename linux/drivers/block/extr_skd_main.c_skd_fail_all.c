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
struct skd_device {int state; } ;
struct request_queue {struct skd_device* queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  SKD_ASSERT (int) ; 
#define  SKD_DRVR_STATE_BUSY 140 
#define  SKD_DRVR_STATE_BUSY_ERASE 139 
#define  SKD_DRVR_STATE_BUSY_IMMINENT 138 
#define  SKD_DRVR_STATE_BUSY_SANITIZE 137 
#define  SKD_DRVR_STATE_DISAPPEARED 136 
#define  SKD_DRVR_STATE_FAULT 135 
 int SKD_DRVR_STATE_ONLINE ; 
#define  SKD_DRVR_STATE_PAUSED 134 
#define  SKD_DRVR_STATE_PAUSING 133 
#define  SKD_DRVR_STATE_RESTARTING 132 
#define  SKD_DRVR_STATE_STARTING 131 
#define  SKD_DRVR_STATE_STOPPING 130 
#define  SKD_DRVR_STATE_SYNCING 129 
#define  SKD_DRVR_STATE_WAIT_BOOT 128 
 int /*<<< orphan*/  skd_log_skdev (struct skd_device*,char*) ; 

__attribute__((used)) static bool skd_fail_all(struct request_queue *q)
{
	struct skd_device *skdev = q->queuedata;

	SKD_ASSERT(skdev->state != SKD_DRVR_STATE_ONLINE);

	skd_log_skdev(skdev, "req_not_online");
	switch (skdev->state) {
	case SKD_DRVR_STATE_PAUSING:
	case SKD_DRVR_STATE_PAUSED:
	case SKD_DRVR_STATE_STARTING:
	case SKD_DRVR_STATE_RESTARTING:
	case SKD_DRVR_STATE_WAIT_BOOT:
	/* In case of starting, we haven't started the queue,
	 * so we can't get here... but requests are
	 * possibly hanging out waiting for us because we
	 * reported the dev/skd0 already.  They'll wait
	 * forever if connect doesn't complete.
	 * What to do??? delay dev/skd0 ??
	 */
	case SKD_DRVR_STATE_BUSY:
	case SKD_DRVR_STATE_BUSY_IMMINENT:
	case SKD_DRVR_STATE_BUSY_ERASE:
		return false;

	case SKD_DRVR_STATE_BUSY_SANITIZE:
	case SKD_DRVR_STATE_STOPPING:
	case SKD_DRVR_STATE_SYNCING:
	case SKD_DRVR_STATE_FAULT:
	case SKD_DRVR_STATE_DISAPPEARED:
	default:
		return true;
	}
}