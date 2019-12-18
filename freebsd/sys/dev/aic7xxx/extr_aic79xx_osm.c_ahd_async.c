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
typedef  int uint32_t ;
struct cam_sim {int dummy; } ;
struct cam_path {int dummy; } ;
struct ahd_softc {int dummy; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */
#define  AC_LOST_DEVICE 128 
 int AHD_TRANS_CUR ; 
 int AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SIM_CHANNEL (struct ahd_softc*,struct cam_sim*) ; 
 int /*<<< orphan*/  SIM_SCSI_ID (struct ahd_softc*,struct cam_sim*) ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_target_id (struct cam_path*) ; 

__attribute__((used)) static void
ahd_async(void *callback_arg, uint32_t code, struct cam_path *path, void *arg)
{
	struct ahd_softc *ahd;
	struct cam_sim *sim;

	sim = (struct cam_sim *)callback_arg;
	ahd = (struct ahd_softc *)cam_sim_softc(sim);
	switch (code) {
	case AC_LOST_DEVICE:
	{
		struct	ahd_devinfo devinfo;

		ahd_compile_devinfo(&devinfo, SIM_SCSI_ID(ahd, sim),
				    xpt_path_target_id(path),
				    xpt_path_lun_id(path),
				    SIM_CHANNEL(ahd, sim),
				    ROLE_UNKNOWN);

		/*
		 * Revert to async/narrow transfers
		 * for the next device.
		 */
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_GOAL|AHD_TRANS_CUR, /*paused*/FALSE);
		ahd_set_syncrate(ahd, &devinfo, /*period*/0, /*offset*/0,
				 /*ppr_options*/0, AHD_TRANS_GOAL|AHD_TRANS_CUR,
				 /*paused*/FALSE);
		break;
	}
	default:
		break;
	}
}