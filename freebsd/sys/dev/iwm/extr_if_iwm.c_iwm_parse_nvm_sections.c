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
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {TYPE_1__* cfg; int /*<<< orphan*/  sc_dev; } ;
struct iwm_nvm_section {scalar_t__ data; } ;
struct iwm_nvm_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ device_family; size_t nvm_hw_section_num; scalar_t__ nvm_type; } ;

/* Variables and functions */
 scalar_t__ IWM_DEVICE_FAMILY_7000 ; 
 scalar_t__ IWM_DEVICE_FAMILY_8000 ; 
 scalar_t__ IWM_NVM_SDP ; 
 size_t IWM_NVM_SECTION_TYPE_CALIBRATION ; 
 size_t IWM_NVM_SECTION_TYPE_MAC_OVERRIDE ; 
 size_t IWM_NVM_SECTION_TYPE_PHY_SKU ; 
 size_t IWM_NVM_SECTION_TYPE_REGULATORY ; 
 size_t IWM_NVM_SECTION_TYPE_REGULATORY_SDP ; 
 size_t IWM_NVM_SECTION_TYPE_SW ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 struct iwm_nvm_data* iwm_parse_nvm_data (struct iwm_softc*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  panic (char*,scalar_t__) ; 

__attribute__((used)) static struct iwm_nvm_data *
iwm_parse_nvm_sections(struct iwm_softc *sc, struct iwm_nvm_section *sections)
{
	const uint16_t *hw, *sw, *calib, *regulatory, *mac_override, *phy_sku;

	/* Checking for required sections */
	if (sc->cfg->device_family == IWM_DEVICE_FAMILY_7000) {
		if (!sections[IWM_NVM_SECTION_TYPE_SW].data ||
		    !sections[sc->cfg->nvm_hw_section_num].data) {
			device_printf(sc->sc_dev,
			    "Can't parse empty OTP/NVM sections\n");
			return NULL;
		}
	} else if (sc->cfg->device_family >= IWM_DEVICE_FAMILY_8000) {
		/* SW and REGULATORY sections are mandatory */
		if (!sections[IWM_NVM_SECTION_TYPE_SW].data ||
		    !sections[IWM_NVM_SECTION_TYPE_REGULATORY].data) {
			device_printf(sc->sc_dev,
			    "Can't parse empty OTP/NVM sections\n");
			return NULL;
		}
		/* MAC_OVERRIDE or at least HW section must exist */
		if (!sections[sc->cfg->nvm_hw_section_num].data &&
		    !sections[IWM_NVM_SECTION_TYPE_MAC_OVERRIDE].data) {
			device_printf(sc->sc_dev,
			    "Can't parse mac_address, empty sections\n");
			return NULL;
		}

		/* PHY_SKU section is mandatory in B0 */
		if (!sections[IWM_NVM_SECTION_TYPE_PHY_SKU].data) {
			device_printf(sc->sc_dev,
			    "Can't parse phy_sku in B0, empty sections\n");
			return NULL;
		}
	} else {
		panic("unknown device family %d\n", sc->cfg->device_family);
	}

	hw = (const uint16_t *) sections[sc->cfg->nvm_hw_section_num].data;
	sw = (const uint16_t *)sections[IWM_NVM_SECTION_TYPE_SW].data;
	calib = (const uint16_t *)
	    sections[IWM_NVM_SECTION_TYPE_CALIBRATION].data;
	regulatory = sc->cfg->nvm_type == IWM_NVM_SDP ?
	    (const uint16_t *)sections[IWM_NVM_SECTION_TYPE_REGULATORY_SDP].data :
	    (const uint16_t *)sections[IWM_NVM_SECTION_TYPE_REGULATORY].data;
	mac_override = (const uint16_t *)
	    sections[IWM_NVM_SECTION_TYPE_MAC_OVERRIDE].data;
	phy_sku = (const uint16_t *)sections[IWM_NVM_SECTION_TYPE_PHY_SKU].data;

	return iwm_parse_nvm_data(sc, hw, sw, calib, mac_override,
	    phy_sku, regulatory);
}