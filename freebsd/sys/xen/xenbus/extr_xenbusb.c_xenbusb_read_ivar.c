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
struct xenbus_device_ivars {int /*<<< orphan*/  xd_otherend_path; int /*<<< orphan*/  xd_otherend_id; int /*<<< orphan*/  xd_state; int /*<<< orphan*/  xd_type; int /*<<< orphan*/  xd_node; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOENT ; 
#define  XENBUS_IVAR_NODE 132 
#define  XENBUS_IVAR_OTHEREND_ID 131 
#define  XENBUS_IVAR_OTHEREND_PATH 130 
#define  XENBUS_IVAR_STATE 129 
#define  XENBUS_IVAR_TYPE 128 
 struct xenbus_device_ivars* device_get_ivars (int /*<<< orphan*/ ) ; 

int
xenbusb_read_ivar(device_t dev, device_t child, int index, uintptr_t *result)
{
	struct xenbus_device_ivars *ivars = device_get_ivars(child);

	switch (index) {
	case XENBUS_IVAR_NODE:
		*result = (uintptr_t) ivars->xd_node;
		return (0);

	case XENBUS_IVAR_TYPE:
		*result = (uintptr_t) ivars->xd_type;
		return (0);

	case XENBUS_IVAR_STATE:
		*result = (uintptr_t) ivars->xd_state;
		return (0);

	case XENBUS_IVAR_OTHEREND_ID:
		*result = (uintptr_t) ivars->xd_otherend_id;
		return (0);

	case XENBUS_IVAR_OTHEREND_PATH:
		*result = (uintptr_t) ivars->xd_otherend_path;
		return (0);
	}

	return (ENOENT);
}