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
struct hdacc_fg {uintptr_t nid; uintptr_t type; uintptr_t subsystem_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_READ_IVAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
#define  HDA_IVAR_NODE_ID 130 
#define  HDA_IVAR_NODE_TYPE 129 
#define  HDA_IVAR_SUBSYSTEM_ID 128 
 struct hdacc_fg* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hdacc_read_ivar(device_t dev, device_t child, int which, uintptr_t *result)
{
	struct hdacc_fg *fg = device_get_ivars(child);

	switch (which) {
	case HDA_IVAR_NODE_ID:
		*result = fg->nid;
		break;
	case HDA_IVAR_NODE_TYPE:
		*result = fg->type;
		break;
	case HDA_IVAR_SUBSYSTEM_ID:
		*result = fg->subsystem_id;
		break;
	default:
		return(BUS_READ_IVAR(device_get_parent(dev), dev,
		    which, result));
	}
	return (0);
}