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
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct mps_softc {int /*<<< orphan*/  use_phynum; int /*<<< orphan*/  spinup_wait_time; int /*<<< orphan*/  chain_alloc_fail; int /*<<< orphan*/  enable_ssu; int /*<<< orphan*/  max_io_pages; int /*<<< orphan*/  max_chains; int /*<<< orphan*/  chain_free_lowwater; int /*<<< orphan*/  chain_free; int /*<<< orphan*/  io_cmds_highwater; int /*<<< orphan*/  io_cmds_active; int /*<<< orphan*/  fw_version; int /*<<< orphan*/  max_evtframes; int /*<<< orphan*/  max_replyframes; int /*<<< orphan*/  max_prireqframes; int /*<<< orphan*/  max_reqframes; int /*<<< orphan*/  msi_msgs; int /*<<< orphan*/  max_msix; int /*<<< orphan*/  disable_msi; int /*<<< orphan*/  disable_msix; struct sysctl_oid* sysctl_tree; struct sysctl_ctx_list sysctl_ctx; int /*<<< orphan*/  mps_dev; } ;

/* Variables and functions */
 int CTLFLAG_MPSAFE ; 
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLFLAG_SKIP ; 
 int CTLTYPE_OPAQUE ; 
 int CTLTYPE_STRING ; 
 int /*<<< orphan*/  DEFAULT_SPINUP_WAIT ; 
 int /*<<< orphan*/  MPS_DRIVER_VERSION ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct mps_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UQUAD (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_mps ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps_debug_sysctl ; 
 int /*<<< orphan*/  mps_dump_reqs ; 
 int /*<<< orphan*/  mps_mapping_dump ; 
 int /*<<< orphan*/  mps_mapping_encl_dump ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_init (struct sysctl_ctx_list*) ; 

__attribute__((used)) static void
mps_setup_sysctl(struct mps_softc *sc)
{
	struct sysctl_ctx_list	*sysctl_ctx = NULL;
	struct sysctl_oid	*sysctl_tree = NULL;
	char tmpstr[80], tmpstr2[80];

	/*
	 * Setup the sysctl variable so the user can change the debug level
	 * on the fly.
	 */
	snprintf(tmpstr, sizeof(tmpstr), "MPS controller %d",
	    device_get_unit(sc->mps_dev));
	snprintf(tmpstr2, sizeof(tmpstr2), "%d", device_get_unit(sc->mps_dev));

	sysctl_ctx = device_get_sysctl_ctx(sc->mps_dev);
	if (sysctl_ctx != NULL)
		sysctl_tree = device_get_sysctl_tree(sc->mps_dev);

	if (sysctl_tree == NULL) {
		sysctl_ctx_init(&sc->sysctl_ctx);
		sc->sysctl_tree = SYSCTL_ADD_NODE(&sc->sysctl_ctx,
		    SYSCTL_STATIC_CHILDREN(_hw_mps), OID_AUTO, tmpstr2,
		    CTLFLAG_RD, 0, tmpstr);
		if (sc->sysctl_tree == NULL)
			return;
		sysctl_ctx = &sc->sysctl_ctx;
		sysctl_tree = sc->sysctl_tree;
	}

	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "debug_level", CTLTYPE_STRING | CTLFLAG_RW |CTLFLAG_MPSAFE,
	    sc, 0, mps_debug_sysctl, "A", "mps debug level");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "disable_msix", CTLFLAG_RD, &sc->disable_msix, 0,
	    "Disable the use of MSI-X interrupts");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "disable_msi", CTLFLAG_RD, &sc->disable_msi, 0,
	    "Disable the use of MSI interrupts");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_msix", CTLFLAG_RD, &sc->max_msix, 0,
	    "User-defined maximum number of MSIX queues");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "msix_msgs", CTLFLAG_RD, &sc->msi_msgs, 0,
	    "Negotiated number of MSIX queues");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_reqframes", CTLFLAG_RD, &sc->max_reqframes, 0,
	    "Total number of allocated request frames");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_prireqframes", CTLFLAG_RD, &sc->max_prireqframes, 0,
	    "Total number of allocated high priority request frames");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_replyframes", CTLFLAG_RD, &sc->max_replyframes, 0,
	    "Total number of allocated reply frames");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_evtframes", CTLFLAG_RD, &sc->max_evtframes, 0,
	    "Total number of event frames allocated");

	SYSCTL_ADD_STRING(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "firmware_version", CTLFLAG_RW, sc->fw_version,
	    strlen(sc->fw_version), "firmware version");

	SYSCTL_ADD_STRING(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "driver_version", CTLFLAG_RW, MPS_DRIVER_VERSION,
	    strlen(MPS_DRIVER_VERSION), "driver version");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "io_cmds_active", CTLFLAG_RD,
	    &sc->io_cmds_active, 0, "number of currently active commands");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "io_cmds_highwater", CTLFLAG_RD,
	    &sc->io_cmds_highwater, 0, "maximum active commands seen");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "chain_free", CTLFLAG_RD,
	    &sc->chain_free, 0, "number of free chain elements");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "chain_free_lowwater", CTLFLAG_RD,
	    &sc->chain_free_lowwater, 0,"lowest number of free chain elements");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_chains", CTLFLAG_RD,
	    &sc->max_chains, 0,"maximum chain frames that will be allocated");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "max_io_pages", CTLFLAG_RD,
	    &sc->max_io_pages, 0,"maximum pages to allow per I/O (if <1 use "
	    "IOCFacts)");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "enable_ssu", CTLFLAG_RW, &sc->enable_ssu, 0,
	    "enable SSU to SATA SSD/HDD at shutdown");

	SYSCTL_ADD_UQUAD(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "chain_alloc_fail", CTLFLAG_RD,
	    &sc->chain_alloc_fail, "chain allocation failures");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "spinup_wait_time", CTLFLAG_RD,
	    &sc->spinup_wait_time, DEFAULT_SPINUP_WAIT, "seconds to wait for "
	    "spinup after SATA ID error");

	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "mapping_table_dump", CTLTYPE_STRING | CTLFLAG_RD, sc, 0,
	    mps_mapping_dump, "A", "Mapping Table Dump");

	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "encl_table_dump", CTLTYPE_STRING | CTLFLAG_RD, sc, 0,
	    mps_mapping_encl_dump, "A", "Enclosure Table Dump");

	SYSCTL_ADD_PROC(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "dump_reqs", CTLTYPE_OPAQUE | CTLFLAG_RD | CTLFLAG_SKIP, sc, 0,
	    mps_dump_reqs, "I", "Dump Active Requests");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "use_phy_num", CTLFLAG_RD, &sc->use_phynum, 0,
	    "Use the phy number for enumeration");
}