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
struct ahc_softc {int dummy; } ;
struct ahc_devinfo {int dummy; } ;

/* Variables and functions */
#define  AC_LOST_DEVICE 128 
 int AHC_TRANS_CUR ; 
 int AHC_TRANS_GOAL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 int /*<<< orphan*/  SIM_CHANNEL (struct ahc_softc*,struct cam_sim*) ; 
 int /*<<< orphan*/  SIM_SCSI_ID (struct ahc_softc*,struct cam_sim*) ; 
 int /*<<< orphan*/  ahc_compile_devinfo (struct ahc_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_syncrate (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_set_width (struct ahc_softc*,struct ahc_devinfo*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  xpt_path_lun_id (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_target_id (struct cam_path*) ; 

__attribute__((used)) static void
ahc_async(void *callback_arg, uint32_t code, struct cam_path *path, void *arg)
{
	struct ahc_softc *ahc;
	struct cam_sim *sim;

	sim = (struct cam_sim *)callback_arg;
	ahc = (struct ahc_softc *)cam_sim_softc(sim);
	switch (code) {
	case AC_LOST_DEVICE:
	{
		struct	ahc_devinfo devinfo;

		ahc_compile_devinfo(&devinfo, SIM_SCSI_ID(ahc, sim),
				    xpt_path_target_id(path),
				    xpt_path_lun_id(path),
				    SIM_CHANNEL(ahc, sim),
				    ROLE_UNKNOWN);

		/*
		 * Revert to async/narrow transfers
		 * for the next device.
		 */
		ahc_set_width(ahc, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHC_TRANS_GOAL|AHC_TRANS_CUR, /*paused*/FALSE);
		ahc_set_syncrate(ahc, &devinfo, /*syncrate*/NULL,
				 /*period*/0, /*offset*/0, /*ppr_options*/0,
				 AHC_TRANS_GOAL|AHC_TRANS_CUR,
				 /*paused*/FALSE);
		break;
	}
	default:
		break;
	}
}