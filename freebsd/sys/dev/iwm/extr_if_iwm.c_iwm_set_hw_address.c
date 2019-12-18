#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* cfg; } ;
struct iwm_nvm_data {int /*<<< orphan*/ * hw_addr; } ;
struct TYPE_4__ {scalar_t__ mac_addr_from_csr; } ;
struct TYPE_3__ {scalar_t__ device_family; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IWM_DEVICE_FAMILY_8000 ; 
 int IWM_HW_ADDR ; 
 TYPE_2__* cfg ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iwm_is_valid_ether_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_set_hw_address_family_8000 (struct iwm_softc*,struct iwm_nvm_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  iwm_set_hw_address_from_csr (struct iwm_softc*,struct iwm_nvm_data*) ; 

__attribute__((used)) static int
iwm_set_hw_address(struct iwm_softc *sc, struct iwm_nvm_data *data,
		   const uint16_t *nvm_hw, const uint16_t *mac_override)
{
#ifdef notyet /* for FAMILY 9000 */
	if (cfg->mac_addr_from_csr) {
		iwm_set_hw_address_from_csr(sc, data);
        } else
#endif
	if (sc->cfg->device_family < IWM_DEVICE_FAMILY_8000) {
		const uint8_t *hw_addr = (const uint8_t *)(nvm_hw + IWM_HW_ADDR);

		/* The byte order is little endian 16 bit, meaning 214365 */
		data->hw_addr[0] = hw_addr[1];
		data->hw_addr[1] = hw_addr[0];
		data->hw_addr[2] = hw_addr[3];
		data->hw_addr[3] = hw_addr[2];
		data->hw_addr[4] = hw_addr[5];
		data->hw_addr[5] = hw_addr[4];
	} else {
		iwm_set_hw_address_family_8000(sc, data, mac_override, nvm_hw);
	}

	if (!iwm_is_valid_ether_addr(data->hw_addr)) {
		device_printf(sc->sc_dev, "no valid mac address was found\n");
		return EINVAL;
	}

	return 0;
}