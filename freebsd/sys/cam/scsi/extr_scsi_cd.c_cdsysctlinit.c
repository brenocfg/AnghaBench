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
typedef  int /*<<< orphan*/  tmpstr2 ;
typedef  int /*<<< orphan*/  tmpstr ;
struct cd_softc {int /*<<< orphan*/  minimum_command_size; int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; int /*<<< orphan*/  flags; } ;
struct cam_periph {int unit_number; scalar_t__ softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_FLAG_SCTX_INIT ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE_WITH_LABEL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _kern_cam_cd ; 
 scalar_t__ cam_periph_acquire (struct cam_periph*) ; 
 int /*<<< orphan*/  cam_periph_release (struct cam_periph*) ; 
 int /*<<< orphan*/  cdcmdsizesysctl ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cdsysctlinit(void *context, int pending)
{
	struct cam_periph *periph;
	struct cd_softc *softc;
	char tmpstr[32], tmpstr2[16];

	periph = (struct cam_periph *)context;
	if (cam_periph_acquire(periph) != 0)
		return;

	softc = (struct cd_softc *)periph->softc;
	snprintf(tmpstr, sizeof(tmpstr), "CAM CD unit %d", periph->unit_number);
	snprintf(tmpstr2, sizeof(tmpstr2), "%d", periph->unit_number);

	sysctl_ctx_init(&softc->sysctl_ctx);
	softc->flags |= CD_FLAG_SCTX_INIT;
	softc->sysctl_tree = SYSCTL_ADD_NODE_WITH_LABEL(&softc->sysctl_ctx,
		SYSCTL_STATIC_CHILDREN(_kern_cam_cd), OID_AUTO,
		tmpstr2, CTLFLAG_RD, 0, tmpstr, "device_index");

	if (softc->sysctl_tree == NULL) {
		printf("cdsysctlinit: unable to allocate sysctl tree\n");
		cam_periph_release(periph);
		return;
	}

	/*
	 * Now register the sysctl handler, so the user can the value on
	 * the fly.
	 */
	SYSCTL_ADD_PROC(&softc->sysctl_ctx,SYSCTL_CHILDREN(softc->sysctl_tree),
		OID_AUTO, "minimum_cmd_size", CTLTYPE_INT | CTLFLAG_RW,
		&softc->minimum_command_size, 0, cdcmdsizesysctl, "I",
		"Minimum CDB size");

	cam_periph_release(periph);
}