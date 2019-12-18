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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwm_softc {int dummy; } ;
struct ieee80211vap {int dummy; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_4__ {int /*<<< orphan*/  trans; } ;
struct TYPE_3__ {int /*<<< orphan*/  tfd_queue_msk; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IWM_CMD_SYNC ; 
 int /*<<< orphan*/  IWM_VAP (struct ieee80211vap*) ; 
 int /*<<< orphan*/  TRUE ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int iwl_trans_wait_tx_queue_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* iwm_mvm_ac_to_tx_fifo ; 
 int iwm_mvm_drain_sta (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwm_mvm_flush_tx_path (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iwm_mvm_rm_sta_common (struct iwm_softc*) ; 
 TYPE_2__* mvm ; 
 TYPE_1__* mvm_sta ; 

int
iwm_mvm_rm_sta(struct iwm_softc *sc, struct ieee80211vap *vap,
	boolean_t is_assoc)
{
	uint32_t tfd_queue_msk = 0;
	int ret;
	int ac;

	ret = iwm_mvm_drain_sta(sc, IWM_VAP(vap), TRUE);
	if (ret)
		return ret;
	for (ac = 0; ac < WME_NUM_AC; ac++) {
		tfd_queue_msk |= htole32(1 << iwm_mvm_ac_to_tx_fifo[ac]);
	}
	ret = iwm_mvm_flush_tx_path(sc, tfd_queue_msk, IWM_CMD_SYNC);
	if (ret)
		return ret;
#ifdef notyet /* function not yet implemented */
	ret = iwl_trans_wait_tx_queue_empty(mvm->trans,
					    mvm_sta->tfd_queue_msk);
	if (ret)
		return ret;
#endif
	ret = iwm_mvm_drain_sta(sc, IWM_VAP(vap), FALSE);

	/* if we are associated - we can't remove the AP STA now */
	if (is_assoc)
		return ret;

	/* XXX wait until STA is drained */

	ret = iwm_mvm_rm_sta_common(sc);

	return ret;
}