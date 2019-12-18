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
 int GV_DRIVE_DOWN ; 
 int GV_DRIVE_UP ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

int
gv_drivestatei(char *buf)
{
	if (!strcmp(buf, "up"))
		return (GV_DRIVE_UP);
	else
		return (GV_DRIVE_DOWN);
}