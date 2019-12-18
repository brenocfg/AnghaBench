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
#define  G_RAID_VOLUME_E_DOWN 131 
#define  G_RAID_VOLUME_E_START 130 
#define  G_RAID_VOLUME_E_STARTMD 129 
#define  G_RAID_VOLUME_E_UP 128 

__attribute__((used)) static const char *
g_raid_volume_event2str(int event)
{

	switch (event) {
	case G_RAID_VOLUME_E_UP:
		return ("UP");
	case G_RAID_VOLUME_E_DOWN:
		return ("DOWN");
	case G_RAID_VOLUME_E_START:
		return ("START");
	case G_RAID_VOLUME_E_STARTMD:
		return ("STARTMD");
	default:
		return ("INVALID");
	}
}