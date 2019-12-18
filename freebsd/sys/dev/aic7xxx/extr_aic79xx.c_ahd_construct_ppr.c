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
 scalar_t__ AHD_SYNCRATE_PACED ; 
 scalar_t__ MSG_EXTENDED ; 
 scalar_t__ MSG_EXT_PPR ; 
 scalar_t__ MSG_EXT_PPR_LEN ; 
 scalar_t__ MSG_EXT_PPR_PCOMP_EN ; 
 char* ahd_name (struct ahd_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
ahd_construct_ppr(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		  u_int period, u_int offset, u_int bus_width,
		  u_int ppr_options)
{
	/*
	 * Always request precompensation from
	 * the other target if we are running
	 * at paced syncrates.
	 */
	if (period <= AHD_SYNCRATE_PACED)
		ppr_options |= MSG_EXT_PPR_PCOMP_EN;
	if (offset == 0)
		period = AHD_ASYNC_XFER_PERIOD;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXTENDED;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_PPR_LEN;
	ahd->msgout_buf[ahd->msgout_index++] = MSG_EXT_PPR;
	ahd->msgout_buf[ahd->msgout_index++] = period;
	ahd->msgout_buf[ahd->msgout_index++] = 0;
	ahd->msgout_buf[ahd->msgout_index++] = offset;
	ahd->msgout_buf[ahd->msgout_index++] = bus_width;
	ahd->msgout_buf[ahd->msgout_index++] = ppr_options;
	ahd->msgout_len += 8;
	if (bootverbose) {
		printf("(%s:%c:%d:%d): Sending PPR bus_width %x, period %x, "
		       "offset %x, ppr_options %x\n", ahd_name(ahd),
		       devinfo->channel, devinfo->target, devinfo->lun,
		       bus_width, period, offset, ppr_options);
	}
}