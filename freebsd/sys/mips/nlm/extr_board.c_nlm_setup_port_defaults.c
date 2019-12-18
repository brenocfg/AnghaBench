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
struct xlp_port_ivars {int num_channels; int free_desc_sizes; int hw_parser_en; int ieee1588_inc_den; int ieee1588_inc_num; int type; int num_free_descs; int iface_fifo_size; int rxbuf_size; int pseq_fifo_size; void* tx_slots_reqd; void* rx_slots_reqd; int /*<<< orphan*/  stg2_ms_credit; int /*<<< orphan*/  stg2_frout_credit; int /*<<< orphan*/  stg2_eh_credit; int /*<<< orphan*/  stg1_2_credit; int /*<<< orphan*/  max_pmem_offset; int /*<<< orphan*/  max_ms_offset; int /*<<< orphan*/  max_frout_offset; int /*<<< orphan*/  max_eh_offset; int /*<<< orphan*/  max_stg2_offset; int /*<<< orphan*/  pktlen_fifo_size; int /*<<< orphan*/  pkt_fifo_size; int /*<<< orphan*/  ms_fifo_size; int /*<<< orphan*/  frout_fifo_size; int /*<<< orphan*/  eh_fifo_size; int /*<<< orphan*/  stg2_fifo_size; scalar_t__ ieee1588_inc_intg; scalar_t__ ieee1588_tmr3; scalar_t__ ieee1588_tmr2; scalar_t__ ieee1588_tmr1; scalar_t__ ieee1588_ptpoff; scalar_t__ ieee1588_userval; scalar_t__ vlan_pri_en; scalar_t__ loopback_mode; } ;

/* Variables and functions */
 void* IL8_CAL_SLOTS ; 
#define  ILC 130 
#define  SGMIIC 129 
 void* SGMII_CAL_SLOTS ; 
#define  XAUIC 128 
 void* XAUI_CAL_SLOTS ; 
 int /*<<< orphan*/  XLP3XX_EH_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_FROUT_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_MAX_EH_OFFSET ; 
 int /*<<< orphan*/  XLP3XX_MAX_FREE_OUT_OFFSET ; 
 int /*<<< orphan*/  XLP3XX_MAX_MS_OFFSET ; 
 int /*<<< orphan*/  XLP3XX_MAX_PMEM_OFFSET ; 
 int /*<<< orphan*/  XLP3XX_MAX_STG2_OFFSET ; 
 int /*<<< orphan*/  XLP3XX_MS_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_PKTLEN_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_PKT_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_STG1_2_CREDIT ; 
 int /*<<< orphan*/  XLP3XX_STG2_EH_CREDIT ; 
 int /*<<< orphan*/  XLP3XX_STG2_FIFO_SZ ; 
 int /*<<< orphan*/  XLP3XX_STG2_FROUT_CREDIT ; 
 int /*<<< orphan*/  XLP3XX_STG2_MS_CREDIT ; 
 int /*<<< orphan*/  XLP8XX_EH_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_FROUT_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_MAX_EH_OFFSET ; 
 int /*<<< orphan*/  XLP8XX_MAX_FREE_OUT_OFFSET ; 
 int /*<<< orphan*/  XLP8XX_MAX_MS_OFFSET ; 
 int /*<<< orphan*/  XLP8XX_MAX_PMEM_OFFSET ; 
 int /*<<< orphan*/  XLP8XX_MAX_STG2_OFFSET ; 
 int /*<<< orphan*/  XLP8XX_MS_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_PKTLEN_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_PKT_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_STG1_2_CREDIT ; 
 int /*<<< orphan*/  XLP8XX_STG2_EH_CREDIT ; 
 int /*<<< orphan*/  XLP8XX_STG2_FIFO_SZ ; 
 int /*<<< orphan*/  XLP8XX_STG2_FROUT_CREDIT ; 
 int /*<<< orphan*/  XLP8XX_STG2_MS_CREDIT ; 
 scalar_t__ nlm_is_xlp3xx () ; 

__attribute__((used)) static void
nlm_setup_port_defaults(struct xlp_port_ivars *p)
{
	p->loopback_mode = 0;
	p->num_channels = 1;
	p->free_desc_sizes = 2048;
	p->vlan_pri_en = 0;
	p->hw_parser_en = 1;
	p->ieee1588_userval = 0;
	p->ieee1588_ptpoff = 0;
	p->ieee1588_tmr1 = 0;
	p->ieee1588_tmr2 = 0;
	p->ieee1588_tmr3 = 0;
	p->ieee1588_inc_intg = 0;
	p->ieee1588_inc_den = 1;
	p->ieee1588_inc_num = 1;

	if (nlm_is_xlp3xx()) {
		p->stg2_fifo_size = XLP3XX_STG2_FIFO_SZ;
		p->eh_fifo_size = XLP3XX_EH_FIFO_SZ;
		p->frout_fifo_size = XLP3XX_FROUT_FIFO_SZ;
		p->ms_fifo_size = XLP3XX_MS_FIFO_SZ;
		p->pkt_fifo_size = XLP3XX_PKT_FIFO_SZ;
		p->pktlen_fifo_size = XLP3XX_PKTLEN_FIFO_SZ;
		p->max_stg2_offset = XLP3XX_MAX_STG2_OFFSET;
		p->max_eh_offset = XLP3XX_MAX_EH_OFFSET;
		p->max_frout_offset = XLP3XX_MAX_FREE_OUT_OFFSET;
		p->max_ms_offset = XLP3XX_MAX_MS_OFFSET;
		p->max_pmem_offset = XLP3XX_MAX_PMEM_OFFSET;
		p->stg1_2_credit = XLP3XX_STG1_2_CREDIT;
		p->stg2_eh_credit = XLP3XX_STG2_EH_CREDIT;
		p->stg2_frout_credit = XLP3XX_STG2_FROUT_CREDIT;
		p->stg2_ms_credit = XLP3XX_STG2_MS_CREDIT;
	} else {
		p->stg2_fifo_size = XLP8XX_STG2_FIFO_SZ;
		p->eh_fifo_size = XLP8XX_EH_FIFO_SZ;
		p->frout_fifo_size = XLP8XX_FROUT_FIFO_SZ;
		p->ms_fifo_size = XLP8XX_MS_FIFO_SZ;
		p->pkt_fifo_size = XLP8XX_PKT_FIFO_SZ;
		p->pktlen_fifo_size = XLP8XX_PKTLEN_FIFO_SZ;
		p->max_stg2_offset = XLP8XX_MAX_STG2_OFFSET;
		p->max_eh_offset = XLP8XX_MAX_EH_OFFSET;
		p->max_frout_offset = XLP8XX_MAX_FREE_OUT_OFFSET;
		p->max_ms_offset = XLP8XX_MAX_MS_OFFSET;
		p->max_pmem_offset = XLP8XX_MAX_PMEM_OFFSET;
		p->stg1_2_credit = XLP8XX_STG1_2_CREDIT;
		p->stg2_eh_credit = XLP8XX_STG2_EH_CREDIT;
		p->stg2_frout_credit = XLP8XX_STG2_FROUT_CREDIT;
		p->stg2_ms_credit = XLP8XX_STG2_MS_CREDIT;
	}

	switch (p->type) {
	case SGMIIC:
		p->num_free_descs = 52;
		p->iface_fifo_size = 13;
		p->rxbuf_size = 128;
		p->rx_slots_reqd = SGMII_CAL_SLOTS;
		p->tx_slots_reqd = SGMII_CAL_SLOTS;
		if (nlm_is_xlp3xx())
		    p->pseq_fifo_size = 30;
		else
		    p->pseq_fifo_size = 62;
		break;
	case ILC:
		p->num_free_descs = 150;
		p->rxbuf_size = 944;
		p->rx_slots_reqd = IL8_CAL_SLOTS;
		p->tx_slots_reqd = IL8_CAL_SLOTS;
		p->pseq_fifo_size = 225;
		p->iface_fifo_size = 55;
		break;
	case XAUIC:
	default:
		p->num_free_descs = 150;
		p->rxbuf_size = 944;
		p->rx_slots_reqd = XAUI_CAL_SLOTS;
		p->tx_slots_reqd = XAUI_CAL_SLOTS;
		if (nlm_is_xlp3xx()) {
		    p->pseq_fifo_size = 120;
		    p->iface_fifo_size = 52;
		} else {
		    p->pseq_fifo_size = 225;
		    p->iface_fifo_size = 55;
		}
		break;
	}
}