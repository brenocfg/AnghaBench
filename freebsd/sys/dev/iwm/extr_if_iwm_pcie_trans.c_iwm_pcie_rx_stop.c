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
struct iwm_softc {TYPE_1__* cfg; } ;
struct TYPE_2__ {scalar_t__ mqrx_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_FH_MEM_RCSR_CHNL0_CONFIG_REG ; 
 int /*<<< orphan*/  IWM_FH_MEM_RSSR_RX_STATUS_REG ; 
 int /*<<< orphan*/  IWM_FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE ; 
 int /*<<< orphan*/  IWM_RFH_GEN_STATUS ; 
 int /*<<< orphan*/  IWM_RFH_RXF_DMA_CFG ; 
 int /*<<< orphan*/  IWM_RXF_DMA_IDLE ; 
 int /*<<< orphan*/  IWM_WRITE (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwm_nic_lock (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_nic_unlock (struct iwm_softc*) ; 
 int iwm_poll_bit (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iwm_poll_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iwm_write_prph (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
iwm_pcie_rx_stop(struct iwm_softc *sc)
{
	int ret;

	ret = 0;
	if (iwm_nic_lock(sc)) {
		if (sc->cfg->mqrx_supported) {
			iwm_write_prph(sc, IWM_RFH_RXF_DMA_CFG, 0);
			ret = iwm_poll_prph(sc, IWM_RFH_GEN_STATUS,
			    IWM_RXF_DMA_IDLE, IWM_RXF_DMA_IDLE, 1000);
		} else {
			IWM_WRITE(sc, IWM_FH_MEM_RCSR_CHNL0_CONFIG_REG, 0);
			ret = iwm_poll_bit(sc, IWM_FH_MEM_RSSR_RX_STATUS_REG,
			    IWM_FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			    IWM_FH_RSSR_CHNL0_RX_STATUS_CHNL_IDLE,
			    1000);
		}
		iwm_nic_unlock(sc);
	}
	return ret;
}