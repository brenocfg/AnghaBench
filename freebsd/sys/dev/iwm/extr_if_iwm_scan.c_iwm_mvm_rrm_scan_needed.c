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
struct iwm_softc {int dummy; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT ; 
 int /*<<< orphan*/  iwm_fw_has_capa (struct iwm_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline boolean_t
iwm_mvm_rrm_scan_needed(struct iwm_softc *sc)
{
	/* require rrm scan whenever the fw supports it */
	return iwm_fw_has_capa(sc, IWM_UCODE_TLV_CAPA_DS_PARAM_SET_IE_SUPPORT);
}