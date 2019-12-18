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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ device_family; } ;

/* Variables and functions */
 scalar_t__ IWM_DEVICE_FAMILY_8000 ; 
 int IWM_SKU ; 
 int IWM_SKU_8000 ; 
 int le16_to_cpup (int /*<<< orphan*/  const*) ; 
 int le32_to_cpup (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
iwm_get_sku(const struct iwm_softc *sc, const uint16_t *nvm_sw,
	    const uint16_t *phy_sku)
{
	if (sc->cfg->device_family < IWM_DEVICE_FAMILY_8000)
		return le16_to_cpup(nvm_sw + IWM_SKU);

	return le32_to_cpup((const uint32_t *)(phy_sku + IWM_SKU_8000));
}