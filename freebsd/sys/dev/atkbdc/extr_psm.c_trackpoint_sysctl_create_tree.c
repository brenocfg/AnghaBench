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
struct TYPE_2__ {int sensitivity; int inertia; int uplateau; int reach; int draghys; int mindrag; int upthresh; int threshold; int jenks; int ztime; int pts; int skipback; int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; } ;
struct psm_softc {TYPE_1__ tpinfo; } ;

/* Variables and functions */
 int CTLFLAG_ANYBODY ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/ * SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct psm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_BACKUP_RANGE ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_DRAG_HYSTERESIS ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_JENKS_CURVATURE ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_MINIMUM_DRAG ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_NEGATIVE_INERTIA ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_PRESS_TO_SELECT ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_SENSITIVITY ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_SKIP_BACKUPS ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_THRESHOLD ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_UPPER_PLATEAU ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_UP_THRESHOLD ; 
 int /*<<< orphan*/  TRACKPOINT_SYSCTL_Z_TIME ; 
 int /*<<< orphan*/  _hw_psm ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trackpoint_sysctl ; 

__attribute__((used)) static void
trackpoint_sysctl_create_tree(struct psm_softc *sc)
{

	if (sc->tpinfo.sysctl_tree != NULL)
		return;

	/* Attach extra trackpoint sysctl nodes under hw.psm.trackpoint */
	sysctl_ctx_init(&sc->tpinfo.sysctl_ctx);
	sc->tpinfo.sysctl_tree = SYSCTL_ADD_NODE(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_STATIC_CHILDREN(_hw_psm), OID_AUTO, "trackpoint", CTLFLAG_RD,
	    0, "IBM/Lenovo TrackPoint");

	/* hw.psm.trackpoint.sensitivity */
	sc->tpinfo.sensitivity = 0x80;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "sensitivity", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_SENSITIVITY,
	    trackpoint_sysctl, "I",
	    "Sensitivity");

	/* hw.psm.trackpoint.negative_inertia */
	sc->tpinfo.inertia = 0x06;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "negative_inertia", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_NEGATIVE_INERTIA,
	    trackpoint_sysctl, "I",
	    "Negative inertia factor");

	/* hw.psm.trackpoint.upper_plateau */
	sc->tpinfo.uplateau = 0x61;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "upper_plateau", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_UPPER_PLATEAU,
	    trackpoint_sysctl, "I",
	    "Transfer function upper plateau speed");

	/* hw.psm.trackpoint.backup_range */
	sc->tpinfo.reach = 0x0a;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "backup_range", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_BACKUP_RANGE,
	    trackpoint_sysctl, "I",
	    "Backup range");

	/* hw.psm.trackpoint.drag_hysteresis */
	sc->tpinfo.draghys = 0xff;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "drag_hysteresis", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_DRAG_HYSTERESIS,
	    trackpoint_sysctl, "I",
	    "Drag hysteresis");

	/* hw.psm.trackpoint.minimum_drag */
	sc->tpinfo.mindrag = 0x14;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "minimum_drag", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_MINIMUM_DRAG,
	    trackpoint_sysctl, "I",
	    "Minimum drag");

	/* hw.psm.trackpoint.up_threshold */
	sc->tpinfo.upthresh = 0xff;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "up_threshold", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_UP_THRESHOLD,
	    trackpoint_sysctl, "I",
	    "Up threshold for release");

	/* hw.psm.trackpoint.threshold */
	sc->tpinfo.threshold = 0x08;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "threshold", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_THRESHOLD,
	    trackpoint_sysctl, "I",
	    "Threshold");

	/* hw.psm.trackpoint.jenks_curvature */
	sc->tpinfo.jenks = 0x87;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "jenks_curvature", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_JENKS_CURVATURE,
	    trackpoint_sysctl, "I",
	    "Jenks curvature");

	/* hw.psm.trackpoint.z_time */
	sc->tpinfo.ztime = 0x26;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "z_time", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_Z_TIME,
	    trackpoint_sysctl, "I",
	    "Z time constant");

	/* hw.psm.trackpoint.press_to_select */
	sc->tpinfo.pts = 0x00;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "press_to_select", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_PRESS_TO_SELECT,
	    trackpoint_sysctl, "I",
	    "Press to Select");

	/* hw.psm.trackpoint.skip_backups */
	sc->tpinfo.skipback = 0x00;
	SYSCTL_ADD_PROC(&sc->tpinfo.sysctl_ctx,
	    SYSCTL_CHILDREN(sc->tpinfo.sysctl_tree), OID_AUTO,
	    "skip_backups", CTLTYPE_INT|CTLFLAG_RW|CTLFLAG_ANYBODY,
	    sc, TRACKPOINT_SYSCTL_SKIP_BACKUPS,
	    trackpoint_sysctl, "I",
	    "Skip backups from drags");
}