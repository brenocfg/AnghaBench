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
struct iwi_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwi_fw {int /*<<< orphan*/  name; } ;
struct iwi_firmware_ohdr {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ IWI_FW_MODE_UCODE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct iwi_firmware_ohdr* iwi_setup_ofw (struct iwi_softc*,struct iwi_fw*) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct iwi_firmware_ohdr *
iwi_setup_oucode(struct iwi_softc *sc, struct iwi_fw *fw)
{
	const struct iwi_firmware_ohdr *hdr;

	hdr = iwi_setup_ofw(sc, fw);
	if (hdr != NULL && le32toh(hdr->mode) != IWI_FW_MODE_UCODE) {
		device_printf(sc->sc_dev, "%s is not a ucode image\n",
		    fw->name);
		hdr = NULL;
	}
	return hdr;
}