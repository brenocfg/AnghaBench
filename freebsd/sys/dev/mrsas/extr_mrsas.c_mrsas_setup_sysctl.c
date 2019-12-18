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
typedef  int /*<<< orphan*/  tmpstr2 ;
typedef  int /*<<< orphan*/  tmpstr ;
struct sysctl_oid {int dummy; } ;
struct sysctl_ctx_list {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  val_rdonly; } ;
struct TYPE_5__ {int /*<<< orphan*/  val_rdonly; } ;
struct TYPE_4__ {int /*<<< orphan*/  val_rdonly; } ;
struct mrsas_softc {TYPE_3__ sge_holes; TYPE_2__ prp_count; int /*<<< orphan*/  drv_stream_detection; int /*<<< orphan*/  block_sync_cache; int /*<<< orphan*/  reset_in_progress; int /*<<< orphan*/  mrsas_fw_fault_check_delay; int /*<<< orphan*/  mrsas_io_timeout; int /*<<< orphan*/  mrsas_debug; int /*<<< orphan*/  io_cmds_highwater; TYPE_1__ fw_outstanding; int /*<<< orphan*/  reset_count; int /*<<< orphan*/  disableOnlineCtrlReset; struct sysctl_oid* sysctl_tree; struct sysctl_ctx_list sysctl_ctx; int /*<<< orphan*/  mrsas_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int /*<<< orphan*/  CTLFLAG_RW ; 
 int /*<<< orphan*/  MRSAS_VERSION ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 struct sysctl_oid* SYSCTL_ADD_NODE (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_STRING (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (struct sysctl_ctx_list*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (struct sysctl_oid*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw_mrsas ; 
 struct sysctl_ctx_list* device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 struct sysctl_oid* device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_init (struct sysctl_ctx_list*) ; 

__attribute__((used)) static void
mrsas_setup_sysctl(struct mrsas_softc *sc)
{
	struct sysctl_ctx_list *sysctl_ctx = NULL;
	struct sysctl_oid *sysctl_tree = NULL;
	char tmpstr[80], tmpstr2[80];

	/*
	 * Setup the sysctl variable so the user can change the debug level
	 * on the fly.
	 */
	snprintf(tmpstr, sizeof(tmpstr), "MRSAS controller %d",
	    device_get_unit(sc->mrsas_dev));
	snprintf(tmpstr2, sizeof(tmpstr2), "%d", device_get_unit(sc->mrsas_dev));

	sysctl_ctx = device_get_sysctl_ctx(sc->mrsas_dev);
	if (sysctl_ctx != NULL)
		sysctl_tree = device_get_sysctl_tree(sc->mrsas_dev);

	if (sysctl_tree == NULL) {
		sysctl_ctx_init(&sc->sysctl_ctx);
		sc->sysctl_tree = SYSCTL_ADD_NODE(&sc->sysctl_ctx,
		    SYSCTL_STATIC_CHILDREN(_hw_mrsas), OID_AUTO, tmpstr2,
		    CTLFLAG_RD, 0, tmpstr);
		if (sc->sysctl_tree == NULL)
			return;
		sysctl_ctx = &sc->sysctl_ctx;
		sysctl_tree = sc->sysctl_tree;
	}
	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "disable_ocr", CTLFLAG_RW, &sc->disableOnlineCtrlReset, 0,
	    "Disable the use of OCR");

	SYSCTL_ADD_STRING(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "driver_version", CTLFLAG_RD, MRSAS_VERSION,
	    strlen(MRSAS_VERSION), "driver version");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "reset_count", CTLFLAG_RD,
	    &sc->reset_count, 0, "number of ocr from start of the day");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "fw_outstanding", CTLFLAG_RD,
	    &sc->fw_outstanding.val_rdonly, 0, "FW outstanding commands");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "io_cmds_highwater", CTLFLAG_RD,
	    &sc->io_cmds_highwater, 0, "Max FW outstanding commands");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "mrsas_debug", CTLFLAG_RW, &sc->mrsas_debug, 0,
	    "Driver debug level");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "mrsas_io_timeout", CTLFLAG_RW, &sc->mrsas_io_timeout,
	    0, "Driver IO timeout value in mili-second.");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "mrsas_fw_fault_check_delay", CTLFLAG_RW,
	    &sc->mrsas_fw_fault_check_delay,
	    0, "FW fault check thread delay in seconds. <default is 1 sec>");

	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "reset_in_progress", CTLFLAG_RD,
	    &sc->reset_in_progress, 0, "ocr in progress status");

	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "block_sync_cache", CTLFLAG_RW,
	    &sc->block_sync_cache, 0,
	    "Block SYNC CACHE at driver. <default: 0, send it to FW>");
	SYSCTL_ADD_UINT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "stream detection", CTLFLAG_RW,
		&sc->drv_stream_detection, 0,
		"Disable/Enable Stream detection. <default: 1, Enable Stream Detection>");
	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "prp_count", CTLFLAG_RD,
	    &sc->prp_count.val_rdonly, 0, "Number of IOs for which PRPs are built");
	SYSCTL_ADD_INT(sysctl_ctx, SYSCTL_CHILDREN(sysctl_tree),
	    OID_AUTO, "SGE holes", CTLFLAG_RD,
	    &sc->sge_holes.val_rdonly, 0, "Number of IOs with holes in SGEs");
}