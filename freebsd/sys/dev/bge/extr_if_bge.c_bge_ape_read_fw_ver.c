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
struct bge_softc {int /*<<< orphan*/  bge_dev; int /*<<< orphan*/  bge_mfw_flags; } ;

/* Variables and functions */
 int APE_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_APE_FW_FEATURES ; 
 int BGE_APE_FW_FEATURE_DASH ; 
 int BGE_APE_FW_FEATURE_NCSI ; 
 int /*<<< orphan*/  BGE_APE_FW_STATUS ; 
 int BGE_APE_FW_STATUS_READY ; 
 int /*<<< orphan*/  BGE_APE_FW_VERSION ; 
 int BGE_APE_FW_VERSION_BLDMSK ; 
 int BGE_APE_FW_VERSION_MAJMSK ; 
 int BGE_APE_FW_VERSION_MAJSFT ; 
 int BGE_APE_FW_VERSION_MINMSK ; 
 int BGE_APE_FW_VERSION_MINSFT ; 
 int BGE_APE_FW_VERSION_REVMSK ; 
 int BGE_APE_FW_VERSION_REVSFT ; 
 int /*<<< orphan*/  BGE_APE_SEG_SIG ; 
 int BGE_APE_SEG_SIG_MAGIC ; 
 int /*<<< orphan*/  BGE_MFW_ON_APE ; 
 int /*<<< orphan*/  BGE_MFW_TYPE_DASH ; 
 int /*<<< orphan*/  BGE_MFW_TYPE_NCSI ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
bge_ape_read_fw_ver(struct bge_softc *sc)
{
	const char *fwtype;
	uint32_t apedata, features;

	/* Check for a valid APE signature in shared memory. */
	apedata = APE_READ_4(sc, BGE_APE_SEG_SIG);
	if (apedata != BGE_APE_SEG_SIG_MAGIC) {
		sc->bge_mfw_flags &= ~ BGE_MFW_ON_APE;
		return;
	}

	/* Check if APE firmware is running. */
	apedata = APE_READ_4(sc, BGE_APE_FW_STATUS);
	if ((apedata & BGE_APE_FW_STATUS_READY) == 0) {
		device_printf(sc->bge_dev, "APE signature found "
		    "but FW status not ready! 0x%08x\n", apedata);
		return;
	}

	sc->bge_mfw_flags |= BGE_MFW_ON_APE;

	/* Fetch the APE firwmare type and version. */
	apedata = APE_READ_4(sc, BGE_APE_FW_VERSION);
	features = APE_READ_4(sc, BGE_APE_FW_FEATURES);
	if ((features & BGE_APE_FW_FEATURE_NCSI) != 0) {
		sc->bge_mfw_flags |= BGE_MFW_TYPE_NCSI;
		fwtype = "NCSI";
	} else if ((features & BGE_APE_FW_FEATURE_DASH) != 0) {
		sc->bge_mfw_flags |= BGE_MFW_TYPE_DASH;
		fwtype = "DASH";
	} else
		fwtype = "UNKN";

	/* Print the APE firmware version. */
	device_printf(sc->bge_dev, "APE FW version: %s v%d.%d.%d.%d\n",
	    fwtype,
	    (apedata & BGE_APE_FW_VERSION_MAJMSK) >> BGE_APE_FW_VERSION_MAJSFT,
	    (apedata & BGE_APE_FW_VERSION_MINMSK) >> BGE_APE_FW_VERSION_MINSFT,
	    (apedata & BGE_APE_FW_VERSION_REVMSK) >> BGE_APE_FW_VERSION_REVSFT,
	    (apedata & BGE_APE_FW_VERSION_BLDMSK));
}