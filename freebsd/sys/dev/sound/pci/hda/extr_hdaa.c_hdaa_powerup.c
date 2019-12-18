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
struct hdaa_devinfo {int nid; int startnode; int endnode; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  HDA_CMD_POWER_STATE_D0 ; 
 int /*<<< orphan*/  HDA_CMD_SET_POWER_STATE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdaa_powerup(struct hdaa_devinfo *devinfo)
{
	int i;

	hda_command(devinfo->dev,
	    HDA_CMD_SET_POWER_STATE(0,
	    devinfo->nid, HDA_CMD_POWER_STATE_D0));
	DELAY(100);

	for (i = devinfo->startnode; i < devinfo->endnode; i++) {
		hda_command(devinfo->dev,
		    HDA_CMD_SET_POWER_STATE(0,
		    i, HDA_CMD_POWER_STATE_D0));
	}
	DELAY(1000);
}