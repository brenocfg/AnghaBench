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
struct fw_hdr {int /*<<< orphan*/  fw_ver; } ;
struct fw_h {int /*<<< orphan*/  fw_ver; } ;
struct firmware {struct fw_h const* data; int /*<<< orphan*/  datasize; } ;
struct adapter {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  mbox; } ;
typedef  int /*<<< orphan*/  bundled_fw ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ERESTART ; 
 int FW_OK ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_BUILD (int const) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MAJOR (int const) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MICRO (int const) ; 
 int /*<<< orphan*/  G_FW_HDR_FW_VER_MINOR (int const) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 void* be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  fw_compatible (struct fw_h*,struct fw_h*) ; 
 int load_fw_module (struct adapter*,struct firmware const**,struct firmware const**) ; 
 int /*<<< orphan*/  memcpy (struct fw_h*,struct fw_h const*,int) ; 
 int t4_fw_install ; 
 int t4_fw_upgrade (struct adapter*,int /*<<< orphan*/ ,struct fw_h const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_fw_module (struct adapter*,struct firmware const*,struct firmware const*) ; 

__attribute__((used)) static int
install_kld_firmware(struct adapter *sc, struct fw_h *card_fw,
    const struct fw_h *drv_fw, const char *reason, int *already)
{
	const struct firmware *cfg, *fw;
	const uint32_t c = be32toh(card_fw->fw_ver);
	uint32_t d, k;
	int rc, fw_install;
	struct fw_h bundled_fw;
	bool load_attempted;

	cfg = fw = NULL;
	load_attempted = false;
	fw_install = t4_fw_install < 0 ? -t4_fw_install : t4_fw_install;

	memcpy(&bundled_fw, drv_fw, sizeof(bundled_fw));
	if (t4_fw_install < 0) {
		rc = load_fw_module(sc, &cfg, &fw);
		if (rc != 0 || fw == NULL) {
			device_printf(sc->dev,
			    "failed to load firmware module: %d. cfg %p, fw %p;"
			    " will use compiled-in firmware version for"
			    "hw.cxgbe.fw_install checks.\n",
			    rc, cfg, fw);
		} else {
			memcpy(&bundled_fw, fw->data, sizeof(bundled_fw));
		}
		load_attempted = true;
	}
	d = be32toh(bundled_fw.fw_ver);

	if (reason != NULL)
		goto install;

	if ((sc->flags & FW_OK) == 0) {

		if (c == 0xffffffff) {
			reason = "missing";
			goto install;
		}

		rc = 0;
		goto done;
	}

	if (!fw_compatible(card_fw, &bundled_fw)) {
		reason = "incompatible or unusable";
		goto install;
	}

	if (d > c) {
		reason = "older than the version bundled with this driver";
		goto install;
	}

	if (fw_install == 2 && d != c) {
		reason = "different than the version bundled with this driver";
		goto install;
	}

	/* No reason to do anything to the firmware already on the card. */
	rc = 0;
	goto done;

install:
	rc = 0;
	if ((*already)++)
		goto done;

	if (fw_install == 0) {
		device_printf(sc->dev, "firmware on card (%u.%u.%u.%u) is %s, "
		    "but the driver is prohibited from installing a firmware "
		    "on the card.\n",
		    G_FW_HDR_FW_VER_MAJOR(c), G_FW_HDR_FW_VER_MINOR(c),
		    G_FW_HDR_FW_VER_MICRO(c), G_FW_HDR_FW_VER_BUILD(c), reason);

		goto done;
	}

	/*
	 * We'll attempt to install a firmware.  Load the module first (if it
	 * hasn't been loaded already).
	 */
	if (!load_attempted) {
		rc = load_fw_module(sc, &cfg, &fw);
		if (rc != 0 || fw == NULL) {
			device_printf(sc->dev,
			    "failed to load firmware module: %d. cfg %p, fw %p\n",
			    rc, cfg, fw);
			/* carry on */
		}
	}
	if (fw == NULL) {
		device_printf(sc->dev, "firmware on card (%u.%u.%u.%u) is %s, "
		    "but the driver cannot take corrective action because it "
		    "is unable to load the firmware module.\n",
		    G_FW_HDR_FW_VER_MAJOR(c), G_FW_HDR_FW_VER_MINOR(c),
		    G_FW_HDR_FW_VER_MICRO(c), G_FW_HDR_FW_VER_BUILD(c), reason);
		rc = sc->flags & FW_OK ? 0 : ENOENT;
		goto done;
	}
	k = be32toh(((const struct fw_hdr *)fw->data)->fw_ver);
	if (k != d) {
		MPASS(t4_fw_install > 0);
		device_printf(sc->dev,
		    "firmware in KLD (%u.%u.%u.%u) is not what the driver was "
		    "expecting (%u.%u.%u.%u) and will not be used.\n",
		    G_FW_HDR_FW_VER_MAJOR(k), G_FW_HDR_FW_VER_MINOR(k),
		    G_FW_HDR_FW_VER_MICRO(k), G_FW_HDR_FW_VER_BUILD(k),
		    G_FW_HDR_FW_VER_MAJOR(d), G_FW_HDR_FW_VER_MINOR(d),
		    G_FW_HDR_FW_VER_MICRO(d), G_FW_HDR_FW_VER_BUILD(d));
		rc = sc->flags & FW_OK ? 0 : EINVAL;
		goto done;
	}

	device_printf(sc->dev, "firmware on card (%u.%u.%u.%u) is %s, "
	    "installing firmware %u.%u.%u.%u on card.\n",
	    G_FW_HDR_FW_VER_MAJOR(c), G_FW_HDR_FW_VER_MINOR(c),
	    G_FW_HDR_FW_VER_MICRO(c), G_FW_HDR_FW_VER_BUILD(c), reason,
	    G_FW_HDR_FW_VER_MAJOR(d), G_FW_HDR_FW_VER_MINOR(d),
	    G_FW_HDR_FW_VER_MICRO(d), G_FW_HDR_FW_VER_BUILD(d));

	rc = -t4_fw_upgrade(sc, sc->mbox, fw->data, fw->datasize, 0);
	if (rc != 0) {
		device_printf(sc->dev, "failed to install firmware: %d\n", rc);
	} else {
		/* Installed successfully, update the cached header too. */
		rc = ERESTART;
		memcpy(card_fw, fw->data, sizeof(*card_fw));
	}
done:
	unload_fw_module(sc, cfg, fw);

	return (rc);
}