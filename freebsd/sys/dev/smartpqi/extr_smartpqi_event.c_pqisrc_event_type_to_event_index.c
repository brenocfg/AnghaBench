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

/* Variables and functions */
 int PQI_EVENT_AIO_CONFIG_CHANGE ; 
 int PQI_EVENT_AIO_STATE_CHANGE ; 
 int PQI_EVENT_HARDWARE ; 
 int PQI_EVENT_HOTPLUG ; 
 int PQI_EVENT_LOGICAL_DEVICE ; 
 int PQI_EVENT_PHYSICAL_DEVICE ; 
#define  PQI_EVENT_TYPE_AIO_CONFIG_CHANGE 133 
#define  PQI_EVENT_TYPE_AIO_STATE_CHANGE 132 
#define  PQI_EVENT_TYPE_HARDWARE 131 
#define  PQI_EVENT_TYPE_HOTPLUG 130 
#define  PQI_EVENT_TYPE_LOGICAL_DEVICE 129 
#define  PQI_EVENT_TYPE_PHYSICAL_DEVICE 128 

__attribute__((used)) static int 
pqisrc_event_type_to_event_index(unsigned event_type)
{
	int index;

	switch (event_type) {
	case PQI_EVENT_TYPE_HOTPLUG:
		index = PQI_EVENT_HOTPLUG;
		break;
	case PQI_EVENT_TYPE_HARDWARE:
		index = PQI_EVENT_HARDWARE;
		break;
	case PQI_EVENT_TYPE_PHYSICAL_DEVICE:
		index = PQI_EVENT_PHYSICAL_DEVICE;
		break;
	case PQI_EVENT_TYPE_LOGICAL_DEVICE:
		index = PQI_EVENT_LOGICAL_DEVICE;
		break;
	case PQI_EVENT_TYPE_AIO_STATE_CHANGE:
		index = PQI_EVENT_AIO_STATE_CHANGE;
		break;
	case PQI_EVENT_TYPE_AIO_CONFIG_CHANGE:
		index = PQI_EVENT_AIO_CONFIG_CHANGE;
		break;
	default:
		index = -1;
		break;
	}

	return index;
}