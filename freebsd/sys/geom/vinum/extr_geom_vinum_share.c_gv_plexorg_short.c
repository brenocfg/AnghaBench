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
#define  GV_PLEX_CONCAT 131 
#define  GV_PLEX_DISORG 130 
#define  GV_PLEX_RAID5 129 
#define  GV_PLEX_STRIPED 128 

const char *
gv_plexorg_short(int org)
{
	switch (org) {
	case GV_PLEX_DISORG:
		return "??";
	case GV_PLEX_CONCAT:
		return "C";
	case GV_PLEX_STRIPED:
		return "S";
	case GV_PLEX_RAID5:
		return "R5";
	default:
		return "??";
	}
}