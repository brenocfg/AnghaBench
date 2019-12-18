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
#define  G_RAID_SUBDISK_E_DISCONNECTED 130 
#define  G_RAID_SUBDISK_E_FAILED 129 
#define  G_RAID_SUBDISK_E_NEW 128 

__attribute__((used)) static const char *
g_raid_subdisk_event2str(int event)
{

	switch (event) {
	case G_RAID_SUBDISK_E_NEW:
		return ("NEW");
	case G_RAID_SUBDISK_E_FAILED:
		return ("FAILED");
	case G_RAID_SUBDISK_E_DISCONNECTED:
		return ("DISCONNECTED");
	default:
		return ("INVALID");
	}
}