#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  path; scalar_t__ ppriv_ptr1; } ;
union ccb {TYPE_1__ ccb_h; } ;
struct mpssas_softc {int /*<<< orphan*/  sc; } ;
struct cam_periph {int dummy; } ;
typedef  int /*<<< orphan*/  path_str ;

/* Variables and functions */
 int /*<<< orphan*/  MPS_INFO ; 
 int /*<<< orphan*/  mps_dprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_path_string (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
mpssas_stop_unit_done(struct cam_periph *periph, union ccb *done_ccb)
{
	struct mpssas_softc *sassc;
	char path_str[64];

	if (done_ccb == NULL)
		return;

	sassc = (struct mpssas_softc *)done_ccb->ccb_h.ppriv_ptr1;

	xpt_path_string(done_ccb->ccb_h.path, path_str, sizeof(path_str));
	mps_dprint(sassc->sc, MPS_INFO, "Completing stop unit for %s\n",
	    path_str);

	/*
	 * Nothing more to do except free the CCB and path.  If the command
	 * timed out, an abort reset, then target reset will be issued during
	 * the SCSI Command process.
	 */
	xpt_free_path(done_ccb->ccb_h.path);
	xpt_free_ccb(done_ccb);
}