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
struct devinfo_dev {int dd_state; } ;
typedef  enum DeviceStatus { ____Placeholder_DeviceStatus } DeviceStatus ;

/* Variables and functions */
#define  DS_ALIVE 131 
#define  DS_ATTACHED 130 
#define  DS_BUSY 129 
 int DS_DOWN ; 
#define  DS_NOTPRESENT 128 
 int DS_RUNNING ; 
 int DS_UNKNOWN ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum DeviceStatus
device_get_status(struct devinfo_dev *dev)
{

	assert(dev != NULL);

	switch (dev->dd_state) {
	case DS_ALIVE:			/* probe succeeded */
	case DS_NOTPRESENT:		/* not probed or probe failed */
		return (DS_DOWN);
	case DS_ATTACHED:		/* attach method called */
	case DS_BUSY:			/* device is open */
		return (DS_RUNNING);
	default:
		return (DS_UNKNOWN);
	}
}