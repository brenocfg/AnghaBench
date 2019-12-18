#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union ciss_device_address {int dummy; } ciss_device_address ;
struct ciss_softc {int ciss_max_logical_bus; int /*<<< orphan*/ * ciss_controllers; struct ciss_ldrive** ciss_logical; TYPE_1__* ciss_cfg; } ;
struct ciss_lun_report {TYPE_3__* lun; int /*<<< orphan*/  list_size; } ;
struct TYPE_5__ {int /*<<< orphan*/  lun; } ;
struct TYPE_6__ {TYPE_2__ logical; } ;
struct ciss_ldrive {scalar_t__ cl_update; scalar_t__ cl_status; int /*<<< orphan*/ * cl_controller; TYPE_3__ cl_address; struct ciss_lun_report* cl_lstatus; struct ciss_lun_report* cl_ldrive; } ;
struct TYPE_4__ {int max_logical_supported; } ;

/* Variables and functions */
 scalar_t__ CISS_LD_ONLINE ; 
 int CISS_LUN_TO_BUS (int /*<<< orphan*/ ) ; 
 int CISS_LUN_TO_TARGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CISS_MALLOC_CLASS ; 
 int /*<<< orphan*/  CISS_OPCODE_REPORT_LOGICAL_LUNS ; 
 int /*<<< orphan*/  ciss_cam_rescan_target (struct ciss_softc*,int,int) ; 
 scalar_t__ ciss_identify_logical (struct ciss_softc*,struct ciss_ldrive*) ; 
 struct ciss_lun_report* ciss_report_luns (struct ciss_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct ciss_lun_report*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ciss_notify_rescan_logical(struct ciss_softc *sc)
{
    struct ciss_lun_report      *cll;
    struct ciss_ldrive		*ld;
    int                         i, j, ndrives;

    /*
     * We must rescan all logical volumes to get the right logical
     * drive address.
     */
    cll = ciss_report_luns(sc, CISS_OPCODE_REPORT_LOGICAL_LUNS,
                           sc->ciss_cfg->max_logical_supported);
    if (cll == NULL)
        return;

    ndrives = (ntohl(cll->list_size) / sizeof(union ciss_device_address));

    /*
     * Delete any of the drives which were destroyed by the
     * firmware.
     */
    for (i = 0; i < sc->ciss_max_logical_bus; i++) {
	for (j = 0; j < sc->ciss_cfg->max_logical_supported; j++) {
	    ld = &sc->ciss_logical[i][j];

	    if (ld->cl_update == 0)
		continue;

	    if (ld->cl_status != CISS_LD_ONLINE) {
		ciss_cam_rescan_target(sc, i, j);
		ld->cl_update = 0;
		if (ld->cl_ldrive)
		    free(ld->cl_ldrive, CISS_MALLOC_CLASS);
		if (ld->cl_lstatus)
		    free(ld->cl_lstatus, CISS_MALLOC_CLASS);

		ld->cl_ldrive = NULL;
		ld->cl_lstatus = NULL;
	    }
	}
    }

    /*
     * Scan for new drives.
     */
    for (i = 0; i < ndrives; i++) {
	int	bus, target;

	bus 	= CISS_LUN_TO_BUS(cll->lun[i].logical.lun);
	target	= CISS_LUN_TO_TARGET(cll->lun[i].logical.lun);
	ld	= &sc->ciss_logical[bus][target];

	if (ld->cl_update == 0)
		continue;

	ld->cl_update		= 0;
	ld->cl_address		= cll->lun[i];
	ld->cl_controller	= &sc->ciss_controllers[bus];
	if (ciss_identify_logical(sc, ld) == 0) {
	    ciss_cam_rescan_target(sc, bus, target);
	}
    }
    free(cll, CISS_MALLOC_CLASS);
}