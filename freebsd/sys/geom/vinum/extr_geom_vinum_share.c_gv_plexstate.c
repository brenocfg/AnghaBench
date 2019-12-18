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
#define  GV_PLEX_DEGRADED 132 
#define  GV_PLEX_DOWN 131 
#define  GV_PLEX_GROWABLE 130 
#define  GV_PLEX_INITIALIZING 129 
#define  GV_PLEX_UP 128 

const char *
gv_plexstate(int state)
{
	switch (state) {
	case GV_PLEX_DOWN:
		return "down";
	case GV_PLEX_INITIALIZING:
		return "initializing";
	case GV_PLEX_DEGRADED:
		return "degraded";
	case GV_PLEX_GROWABLE:
		return "growable";
	case GV_PLEX_UP:
		return "up";
	default:
		return "??";
	}
}