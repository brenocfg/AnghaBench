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
struct ahc_softc {int msgout_len; int /*<<< orphan*/  msgout_index; scalar_t__* msgout_buf; } ;
struct ahc_devinfo {int channel; int target; int lun; } ;

/* Variables and functions */
 scalar_t__ AHC_ASYNC_XFER_PERIOD ; 
 scalar_t__ MSG_EXTENDED ; 
 scalar_t__ MSG_EXT_SDTR ; 
 scalar_t__ MSG_EXT_SDTR_LEN ; 
 char* ahc_name (struct ahc_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahc_construct_sdtr(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		   u_int period, u_int offset)
{
	if (offset == 0)
		period = AHC_ASYNC_XFER_PERIOD;
	ahc->msgout_buf[ahc->msgout_index++] = MSG_EXTENDED;
	ahc->msgout_buf[ahc->msgout_index++] = MSG_EXT_SDTR_LEN;
	ahc->msgout_buf[ahc->msgout_index++] = MSG_EXT_SDTR;
	ahc->msgout_buf[ahc->msgout_index++] = period;
	ahc->msgout_buf[ahc->msgout_index++] = offset;
	ahc->msgout_len += 5;
	if (bootverbose) {
		printf("(%s:%c:%d:%d): Sending SDTR period %x, offset %x\n",
		       ahc_name(ahc), devinfo->channel, devinfo->target,
		       devinfo->lun, period, offset);
	}
}