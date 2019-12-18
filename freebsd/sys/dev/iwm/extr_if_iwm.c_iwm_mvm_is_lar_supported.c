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
struct iwm_softc {TYPE_2__* cfg; TYPE_1__* nvm_data; } ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__ device_family; } ;
struct TYPE_3__ {int lar_enabled; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ IWM_DEVICE_FAMILY_8000 ; 
 int /*<<< orphan*/  IWM_UCODE_TLV_CAPA_LAR_SUPPORT ; 
 int iwm_fw_has_capa (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ iwm_lar_disable ; 

__attribute__((used)) static boolean_t
iwm_mvm_is_lar_supported(struct iwm_softc *sc)
{
	boolean_t nvm_lar = sc->nvm_data->lar_enabled;
	boolean_t tlv_lar = iwm_fw_has_capa(sc, IWM_UCODE_TLV_CAPA_LAR_SUPPORT);

	if (iwm_lar_disable)
		return FALSE;

	/*
	 * Enable LAR only if it is supported by the FW (TLV) &&
	 * enabled in the NVM
	 */
	if (sc->cfg->device_family >= IWM_DEVICE_FAMILY_8000)
		return nvm_lar && tlv_lar;
	else
		return tlv_lar;
}