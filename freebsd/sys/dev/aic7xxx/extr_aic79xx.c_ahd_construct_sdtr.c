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
typedef  scalar_t__ u_int ;
struct ahd_softc {int msgout_len; int /*<<< orphan*/  msgout_index; scalar_t__* msgout_buf; } ;
struct ahd_devinfo {int channel; int target; int lun; } ;

/* Variables and functions */
 scalar_t__ AHD_ASYNC_XFER_PERIOD ; 
 scalar_t__ MSG_EXTENDED ; 
 scalar_t__ MSG_EXT_SDTR ; 
 scalar_t__ MSG_EXT_SDTR_LEN ; 
 char* ahd_name (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahd_construct_sdtr(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		   u_int period, u_int offset)
{
	if (offset == 0)
		period = AHD_ASYNC_XFER_PERIOD;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXTENDED;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_SDTR_LEN;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_SDTR;
	ahd->msgout_buf[ahd->msgout_index++] = period;
	ahd->msgout_buf[ahd->msgout_index++] = offset;
	ahd->msgout_len += 5;
	if (bootverbose) {
		printf("(%s:%c:%d:%d): Sending SDTR period %x, offset %x\n",
		       ahd_name(ahd), devinfo->channel, devinfo->target,
		       devinfo->lun, period, offset);
	}
}