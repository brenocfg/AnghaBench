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
typedef  void* uint16_t ;
struct mprs_btdh_mapping {void* DevHandle; void* TargetID; void* Bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTIOCTL_BTDH_MAPPING ; 
 int errno ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mprs_btdh_mapping*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
mps_map_btdh(int fd, uint16_t *devhandle, uint16_t *bus, uint16_t *target)
{
	int error;
	struct mprs_btdh_mapping map;

	map.Bus = *bus;
	map.TargetID = *target;
	map.DevHandle = *devhandle;

	if ((error = ioctl(fd, MPTIOCTL_BTDH_MAPPING, &map)) != 0) {
		error = errno;
		warn("Failed to map bus/target/device");
		return (error);
	}

	*bus = map.Bus;
	*target = map.TargetID;
	*devhandle = map.DevHandle;

	return (0);
}