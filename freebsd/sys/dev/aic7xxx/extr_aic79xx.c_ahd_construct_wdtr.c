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
typedef  int u_int ;
struct ahd_softc {int* msgout_buf; int msgout_len; int /*<<< orphan*/  msgout_index; } ;
struct ahd_devinfo {int channel; int target; int lun; } ;

/* Variables and functions */
 int MSG_EXTENDED ; 
 int MSG_EXT_WDTR ; 
 int MSG_EXT_WDTR_LEN ; 
 char* ahd_name (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,int) ; 

__attribute__((used)) static void
ahd_construct_wdtr(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		   u_int bus_width)
{
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXTENDED;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_WDTR_LEN;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_WDTR;
	ahd->msgout_buf[ahd->msgout_index++] = bus_width;
	ahd->msgout_len += 4;
	if (bootverbose) {
		printf("(%s:%c:%d:%d): Sending WDTR %x\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       devinfo->lun, bus_width);
	}
}