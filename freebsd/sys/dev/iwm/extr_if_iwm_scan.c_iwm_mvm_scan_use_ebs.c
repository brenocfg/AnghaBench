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
struct iwm_ucode_capabilities {int flags; } ;
struct TYPE_2__ {struct iwm_ucode_capabilities ucode_capa; } ;
struct iwm_softc {scalar_t__ last_ebs_successful; TYPE_1__ sc_fw; } ;
typedef  int boolean_t ;

/* Variables and functions */
 int IWM_UCODE_TLV_FLAGS_EBS_SUPPORT ; 

__attribute__((used)) static boolean_t
iwm_mvm_scan_use_ebs(struct iwm_softc *sc)
{
	const struct iwm_ucode_capabilities *capa = &sc->sc_fw.ucode_capa;

	/* We can only use EBS if:
	 *	1. the feature is supported;
	 *	2. the last EBS was successful;
	 *	3. if only single scan, the single scan EBS API is supported;
	 *	4. it's not a p2p find operation.
	 */
	return ((capa->flags & IWM_UCODE_TLV_FLAGS_EBS_SUPPORT) &&
		sc->last_ebs_successful);
}