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
struct fw_h {int dummy; } ;
struct fw_info {struct fw_h fw_h; } ;
struct fw_hdr {int /*<<< orphan*/  flags; } ;
struct adapter {int flags; int pf; int /*<<< orphan*/  mbox; scalar_t__ cfcsum; int /*<<< orphan*/  cfg_file; int /*<<< orphan*/  dev; } ;
typedef  enum dev_state { ____Placeholder_dev_state } dev_state ;

/* Variables and functions */
 int /*<<< orphan*/  A_PCIE_FW ; 
 int DEV_STATE_ERR ; 
 int DEV_STATE_UNINIT ; 
 int EINVAL ; 
 int EPROTO ; 
 int ERESTART ; 
 int FW_HDR_FLAGS_RESET_HALT ; 
 int FW_OK ; 
 int /*<<< orphan*/  MASTER_MAY ; 
 int MASTER_PF ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_CXGBE ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip_id (struct adapter*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 struct fw_info* find_fw_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct fw_hdr*,int /*<<< orphan*/ ) ; 
 int install_kld_firmware (struct adapter*,struct fw_h*,struct fw_h const*,char*,int*) ; 
 struct fw_hdr* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  t4_fw_bye (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_fw_hello (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int t4_get_fw_hdr (struct adapter*,struct fw_hdr*) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
contact_firmware(struct adapter *sc)
{
	int rc, already = 0;
	enum dev_state state;
	struct fw_info *fw_info;
	struct fw_hdr *card_fw;		/* fw on the card */
	const struct fw_h *drv_fw;

	fw_info = find_fw_info(chip_id(sc));
	if (fw_info == NULL) {
		device_printf(sc->dev,
		    "unable to look up firmware information for chip %d.\n",
		    chip_id(sc));
		return (EINVAL);
	}
	drv_fw = &fw_info->fw_h;

	/* Read the header of the firmware on the card */
	card_fw = malloc(sizeof(*card_fw), M_CXGBE, M_ZERO | M_WAITOK);
restart:
	rc = -t4_get_fw_hdr(sc, card_fw);
	if (rc != 0) {
		device_printf(sc->dev,
		    "unable to read firmware header from card's flash: %d\n",
		    rc);
		goto done;
	}

	rc = install_kld_firmware(sc, (struct fw_h *)card_fw, drv_fw, NULL,
	    &already);
	if (rc == ERESTART)
		goto restart;
	if (rc != 0)
		goto done;

	rc = t4_fw_hello(sc, sc->mbox, sc->mbox, MASTER_MAY, &state);
	if (rc < 0 || state == DEV_STATE_ERR) {
		rc = -rc;
		device_printf(sc->dev,
		    "failed to connect to the firmware: %d, %d.  "
		    "PCIE_FW 0x%08x\n", rc, state, t4_read_reg(sc, A_PCIE_FW));
#if 0
		if (install_kld_firmware(sc, (struct fw_h *)card_fw, drv_fw,
		    "not responding properly to HELLO", &already) == ERESTART)
			goto restart;
#endif
		goto done;
	}
	MPASS(be32toh(card_fw->flags) & FW_HDR_FLAGS_RESET_HALT);
	sc->flags |= FW_OK;	/* The firmware responded to the FW_HELLO. */

	if (rc == sc->pf) {
		sc->flags |= MASTER_PF;
		rc = install_kld_firmware(sc, (struct fw_h *)card_fw, drv_fw,
		    NULL, &already);
		if (rc == ERESTART)
			rc = 0;
		else if (rc != 0)
			goto done;
	} else if (state == DEV_STATE_UNINIT) {
		/*
		 * We didn't get to be the master so we definitely won't be
		 * configuring the chip.  It's a bug if someone else hasn't
		 * configured it already.
		 */
		device_printf(sc->dev, "couldn't be master(%d), "
		    "device not already initialized either(%d).  "
		    "PCIE_FW 0x%08x\n", rc, state, t4_read_reg(sc, A_PCIE_FW));
		rc = EPROTO;
		goto done;
	} else {
		/*
		 * Some other PF is the master and has configured the chip.
		 * This is allowed but untested.
		 */
		device_printf(sc->dev, "PF%d is master, device state %d.  "
		    "PCIE_FW 0x%08x\n", rc, state, t4_read_reg(sc, A_PCIE_FW));
		snprintf(sc->cfg_file, sizeof(sc->cfg_file), "pf%d", rc);
		sc->cfcsum = 0;
		rc = 0;
	}
done:
	if (rc != 0 && sc->flags & FW_OK) {
		t4_fw_bye(sc, sc->mbox);
		sc->flags &= ~FW_OK;
	}
	free(card_fw, M_CXGBE);
	return (rc);
}