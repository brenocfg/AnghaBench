#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* data; int size; int /*<<< orphan*/  name; struct firmware* fp; } ;
struct TYPE_7__ {char const* data; int size; int /*<<< orphan*/  name; TYPE_1__* fp; } ;
struct iwi_softc {int fw_mode; TYPE_3__ fw_fw; TYPE_2__ fw_uc; TYPE_3__ fw_boot; int /*<<< orphan*/  sc_dev; } ;
struct iwi_firmware_hdr {int /*<<< orphan*/  fsize; int /*<<< orphan*/  usize; int /*<<< orphan*/  bsize; } ;
struct firmware {int version; int datasize; int /*<<< orphan*/  name; scalar_t__ data; } ;
typedef  enum ieee80211_opmode { ____Placeholder_ieee80211_opmode } ieee80211_opmode ;
struct TYPE_6__ {scalar_t__ version; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IEEE80211_M_IBSS 130 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct firmware* firmware_get (char*) ; 
 int /*<<< orphan*/  iwi_getfw (TYPE_3__*,char*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  iwi_put_firmware (struct iwi_softc*) ; 
 int /*<<< orphan*/ * iwi_setup_ofw (struct iwi_softc*,TYPE_3__*) ; 
 int /*<<< orphan*/ * iwi_setup_oucode (struct iwi_softc*,TYPE_2__*) ; 
 int le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwi_get_firmware(struct iwi_softc *sc, enum ieee80211_opmode opmode)
{
	const struct iwi_firmware_hdr *hdr;
	const struct firmware *fp;

	/* invalidate cached firmware on mode change */
	if (sc->fw_mode != opmode)
		iwi_put_firmware(sc);

	switch (opmode) {
	case IEEE80211_M_STA:
		iwi_getfw(&sc->fw_fw, "iwi_bss", &sc->fw_uc, "iwi_ucode_bss");
		break;
	case IEEE80211_M_IBSS:
		iwi_getfw(&sc->fw_fw, "iwi_ibss", &sc->fw_uc, "iwi_ucode_ibss");
		break;
	case IEEE80211_M_MONITOR:
		iwi_getfw(&sc->fw_fw, "iwi_monitor",
			  &sc->fw_uc, "iwi_ucode_monitor");
		break;
	default:
		device_printf(sc->sc_dev, "unknown opmode %d\n", opmode);
		return EINVAL;
	}
	fp = sc->fw_fw.fp;
	if (fp == NULL) {
		device_printf(sc->sc_dev, "could not load firmware\n");
		goto bad;
	}
	if (fp->version < 300) {
		/*
		 * Firmware prior to 3.0 was packaged as separate
		 * boot, firmware, and ucode images.  Verify the
		 * ucode image was read in, retrieve the boot image
		 * if needed, and check version stamps for consistency.
		 * The version stamps in the data are also checked
		 * above; this is a bit paranoid but is a cheap
		 * safeguard against mis-packaging.
		 */
		if (sc->fw_uc.fp == NULL) {
			device_printf(sc->sc_dev, "could not load ucode\n");
			goto bad;
		}
		if (sc->fw_boot.fp == NULL) {
			sc->fw_boot.fp = firmware_get("iwi_boot");
			if (sc->fw_boot.fp == NULL) {
				device_printf(sc->sc_dev,
					"could not load boot firmware\n");
				goto bad;
			}
		}
		if (sc->fw_boot.fp->version != sc->fw_fw.fp->version ||
		    sc->fw_boot.fp->version != sc->fw_uc.fp->version) {
			device_printf(sc->sc_dev,
			    "firmware version mismatch: "
			    "'%s' is %d, '%s' is %d, '%s' is %d\n",
			    sc->fw_boot.fp->name, sc->fw_boot.fp->version,
			    sc->fw_uc.fp->name, sc->fw_uc.fp->version,
			    sc->fw_fw.fp->name, sc->fw_fw.fp->version
			);
			goto bad;
		}
		/*
		 * Check and setup each image.
		 */
		if (iwi_setup_oucode(sc, &sc->fw_uc) == NULL ||
		    iwi_setup_ofw(sc, &sc->fw_boot) == NULL ||
		    iwi_setup_ofw(sc, &sc->fw_fw) == NULL)
			goto bad;
	} else {
		/*
		 * Check and setup combined image.
		 */
		if (fp->datasize < sizeof(struct iwi_firmware_hdr)) {
			device_printf(sc->sc_dev, "image '%s' too small\n",
			    fp->name);
			goto bad;
		}
		hdr = (const struct iwi_firmware_hdr *)fp->data;
		if (fp->datasize < sizeof(*hdr) + le32toh(hdr->bsize) + le32toh(hdr->usize)
				+ le32toh(hdr->fsize)) {
			device_printf(sc->sc_dev, "image '%s' too small (2)\n",
			    fp->name);
			goto bad;
		}
		sc->fw_boot.data = ((const char *) fp->data) + sizeof(*hdr);
		sc->fw_boot.size = le32toh(hdr->bsize);
		sc->fw_boot.name = fp->name;
		sc->fw_uc.data = sc->fw_boot.data + sc->fw_boot.size;
		sc->fw_uc.size = le32toh(hdr->usize);
		sc->fw_uc.name = fp->name;
		sc->fw_fw.data = sc->fw_uc.data + sc->fw_uc.size;
		sc->fw_fw.size = le32toh(hdr->fsize);
		sc->fw_fw.name = fp->name;
	}
#if 0
	device_printf(sc->sc_dev, "boot %d ucode %d fw %d bytes\n",
		sc->fw_boot.size, sc->fw_uc.size, sc->fw_fw.size);
#endif

	sc->fw_mode = opmode;
	return 0;
bad:
	iwi_put_firmware(sc);
	return 1;
}