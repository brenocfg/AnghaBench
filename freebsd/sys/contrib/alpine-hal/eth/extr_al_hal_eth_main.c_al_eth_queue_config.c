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
typedef  size_t uint32_t ;
struct al_udma_q_params {int cdesc_size; int /*<<< orphan*/  adapter_rev_id; } ;
struct al_udma {int /*<<< orphan*/ * udma_q; } ;
struct al_hal_eth_adapter {TYPE_2__* ec_regs_base; int /*<<< orphan*/  rev_id; struct al_udma rx_udma; struct al_udma tx_udma; int /*<<< orphan*/  name; } ;
typedef  enum al_udma_type { ____Placeholder_al_udma_type } al_udma_type ;
struct TYPE_3__ {int /*<<< orphan*/  out_cfg; } ;
struct TYPE_4__ {TYPE_1__ rfw; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_S2M_UDMA_COMP_COAL_TIMEOUT ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  EC_RFW_OUT_CFG_META_CNT_MASK ; 
 int UDMA_RX ; 
 int UDMA_TX ; 
 int /*<<< orphan*/  al_assert (int) ; 
 int /*<<< orphan*/  al_dbg (char*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  al_reg_write32_masked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int al_udma_q_init (struct al_udma*,size_t,struct al_udma_q_params*) ; 
 int al_udma_s2m_q_compl_coal_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int al_eth_queue_config(struct al_hal_eth_adapter *adapter, enum al_udma_type type, uint32_t qid,
			     struct al_udma_q_params *q_params)
{
	struct al_udma *udma;
	int rc;

	al_dbg("eth [%s]: config UDMA %s queue %d\n", adapter->name,
		 type == UDMA_TX ? "Tx" : "Rx", qid);

	if (type == UDMA_TX) {
		udma = &adapter->tx_udma;
	} else {
		udma = &adapter->rx_udma;
	}

	q_params->adapter_rev_id = adapter->rev_id;

	rc = al_udma_q_init(udma, qid, q_params);

	if (rc)
		return rc;

	if (type == UDMA_RX) {
		rc = al_udma_s2m_q_compl_coal_config(&udma->udma_q[qid],
				AL_TRUE, AL_ETH_S2M_UDMA_COMP_COAL_TIMEOUT);

		al_assert(q_params->cdesc_size <= 32);

		if (q_params->cdesc_size > 16)
			al_reg_write32_masked(&adapter->ec_regs_base->rfw.out_cfg,
					EC_RFW_OUT_CFG_META_CNT_MASK, 2);
	}
	return rc;
}