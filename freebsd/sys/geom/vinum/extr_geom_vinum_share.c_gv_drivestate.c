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
#define  GV_DRIVE_DOWN 129 
#define  GV_DRIVE_UP 128 

const char *
gv_drivestate(int state)
{
	switch (state) {
	case GV_DRIVE_DOWN:
		return "down";
	case GV_DRIVE_UP:
		return "up";
	default:
		return "??";
	}
}