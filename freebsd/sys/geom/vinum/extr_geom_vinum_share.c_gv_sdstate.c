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
#define  GV_SD_DOWN 132 
#define  GV_SD_INITIALIZING 131 
#define  GV_SD_REVIVING 130 
#define  GV_SD_STALE 129 
#define  GV_SD_UP 128 

const char *
gv_sdstate(int state)
{
	switch (state) {
	case GV_SD_INITIALIZING:
		return "initializing";
	case GV_SD_STALE:
		return "stale";
	case GV_SD_DOWN:
		return "down";
	case GV_SD_REVIVING:
		return "reviving";
	case GV_SD_UP:
		return "up";
	default:
		return "??";
	}
}