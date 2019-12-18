#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {struct ciss_ldrive** ciss_logical; } ;
struct TYPE_15__ {int logical_drive; } ;
struct TYPE_14__ {int /*<<< orphan*/  failure_drive; int /*<<< orphan*/  failure_bus; int /*<<< orphan*/  logical_drive; } ;
struct TYPE_13__ {int /*<<< orphan*/  logical_drive; } ;
struct TYPE_12__ {int logical_drive; int /*<<< orphan*/  new_state; int /*<<< orphan*/  previous_state; int /*<<< orphan*/  spare_state; } ;
struct TYPE_16__ {TYPE_7__ consistency_completed; TYPE_6__ io_error; TYPE_5__ rebuild_aborted; TYPE_4__ logical_status; } ;
struct TYPE_9__ {int bus; } ;
struct TYPE_10__ {TYPE_1__ physical; } ;
struct ciss_notify {int subclass; int detail; TYPE_8__ data; TYPE_2__ device; } ;
struct ciss_ldrive {int cl_status; int cl_update; int /*<<< orphan*/  cl_name; TYPE_3__* cl_lstatus; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  CISS_NOTIFY_LOGICAL_ERROR 130 
#define  CISS_NOTIFY_LOGICAL_STATUS 129 
#define  CISS_NOTIFY_LOGICAL_SURFACE 128 
 int /*<<< orphan*/  ciss_accept_media (struct ciss_softc*,struct ciss_ldrive*) ; 
 void* ciss_decode_ldrive_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ciss_name_device (struct ciss_softc*,int,int) ; 
 int /*<<< orphan*/  ciss_name_ldrive_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ciss_notify_rescan_logical (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
ciss_notify_logical(struct ciss_softc *sc, struct ciss_notify *cn)
{
    struct ciss_ldrive	*ld;
    int			ostatus, bus, target;

    debug_called(2);

    bus		= cn->device.physical.bus;
    target	= cn->data.logical_status.logical_drive;
    ld		= &sc->ciss_logical[bus][target];

    switch (cn->subclass) {
    case CISS_NOTIFY_LOGICAL_STATUS:
	switch (cn->detail) {
	case 0:
	    ciss_name_device(sc, bus, target);
	    ciss_printf(sc, "logical drive %d (%s) changed status %s->%s, spare status 0x%b\n",
			cn->data.logical_status.logical_drive, ld->cl_name,
			ciss_name_ldrive_status(cn->data.logical_status.previous_state),
			ciss_name_ldrive_status(cn->data.logical_status.new_state),
			cn->data.logical_status.spare_state,
			"\20\1configured\2rebuilding\3failed\4in use\5available\n");

	    /*
	     * Update our idea of the drive's status.
	     */
	    ostatus = ciss_decode_ldrive_status(cn->data.logical_status.previous_state);
	    ld->cl_status = ciss_decode_ldrive_status(cn->data.logical_status.new_state);
	    if (ld->cl_lstatus != NULL)
		ld->cl_lstatus->status = cn->data.logical_status.new_state;

	    /*
	     * Have CAM rescan the drive if its status has changed.
	     */
	    if (ostatus != ld->cl_status) {
		ld->cl_update = 1;
		ciss_notify_rescan_logical(sc);
	    }

	    break;

	case 1:	/* logical drive has recognised new media, needs Accept Media Exchange */
	    ciss_name_device(sc, bus, target);
	    ciss_printf(sc, "logical drive %d (%s) media exchanged, ready to go online\n",
			cn->data.logical_status.logical_drive, ld->cl_name);
	    ciss_accept_media(sc, ld);

	    ld->cl_update = 1;
	    ld->cl_status = ciss_decode_ldrive_status(cn->data.logical_status.new_state);
	    ciss_notify_rescan_logical(sc);
	    break;

	case 2:
	case 3:
	    ciss_printf(sc, "rebuild of logical drive %d (%s) failed due to %s error\n",
			cn->data.rebuild_aborted.logical_drive,
			ld->cl_name,
			(cn->detail == 2) ? "read" : "write");
	    break;
	}
	break;

    case CISS_NOTIFY_LOGICAL_ERROR:
	if (cn->detail == 0) {
	    ciss_printf(sc, "FATAL I/O ERROR on logical drive %d (%s), SCSI port %d ID %d\n",
			cn->data.io_error.logical_drive,
			ld->cl_name,
			cn->data.io_error.failure_bus,
			cn->data.io_error.failure_drive);
	    /* XXX should we take the drive down at this point, or will we be told? */
	}
	break;

    case CISS_NOTIFY_LOGICAL_SURFACE:
	if (cn->detail == 0)
	    ciss_printf(sc, "logical drive %d (%s) completed consistency initialisation\n",
			cn->data.consistency_completed.logical_drive,
			ld->cl_name);
	break;
    }
}