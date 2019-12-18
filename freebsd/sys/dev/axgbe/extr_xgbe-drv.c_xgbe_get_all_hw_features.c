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
struct xgbe_hw_features {int dma_width; int hash_table_size; void* tc_cnt; void* tx_ch_cnt; void* rx_ch_cnt; void* tx_q_cnt; void* rx_q_cnt; void* aux_snap_num; void* pps_out_num; void* l3l4_filter_num; void* rss; void* dma_debug; void* tso; void* sph; void* dcb; void* adv_ts_hi; void* tx_fifo_size; void* rx_fifo_size; void* sa_vlan_ins; void* ts_src; void* addn_mac; void* rx_coe; void* tx_coe; void* eee; void* ts; void* aoe; void* mmc; void* mgk; void* rwk; void* sma; void* vlhash; void* gmii; void* version; } ;
struct xgbe_prv_data {struct xgbe_hw_features hw_feat; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDMACADRSEL ; 
 int /*<<< orphan*/  ADDR64 ; 
 int /*<<< orphan*/  ADVTHWORD ; 
 int /*<<< orphan*/  ARPOFFSEL ; 
 int /*<<< orphan*/  AUXSNAPNUM ; 
 int /*<<< orphan*/  DBGMEMA ; 
 int /*<<< orphan*/  DBGPR (char*) ; 
 int /*<<< orphan*/  DCBEN ; 
 int /*<<< orphan*/  EEESEL ; 
 int /*<<< orphan*/  GMIISEL ; 
 int /*<<< orphan*/  HASHTBLSZ ; 
 int /*<<< orphan*/  L3L4FNUM ; 
 int /*<<< orphan*/  MAC_HWF0R ; 
 int /*<<< orphan*/  MAC_HWF1R ; 
 int /*<<< orphan*/  MAC_HWF2R ; 
 int /*<<< orphan*/  MAC_VR ; 
 int /*<<< orphan*/  MGKSEL ; 
 int /*<<< orphan*/  MMCSEL ; 
 int /*<<< orphan*/  NUMTC ; 
 int /*<<< orphan*/  PPSOUTNUM ; 
 int /*<<< orphan*/  RSSEN ; 
 int /*<<< orphan*/  RWKSEL ; 
 int /*<<< orphan*/  RXCHCNT ; 
 int /*<<< orphan*/  RXCOESEL ; 
 int /*<<< orphan*/  RXFIFOSIZE ; 
 int /*<<< orphan*/  RXQCNT ; 
 int /*<<< orphan*/  SAVLANINS ; 
 int /*<<< orphan*/  SMASEL ; 
 int /*<<< orphan*/  SPHEN ; 
 int /*<<< orphan*/  TSOEN ; 
 int /*<<< orphan*/  TSSEL ; 
 int /*<<< orphan*/  TSSTSSEL ; 
 int /*<<< orphan*/  TXCHCNT ; 
 int /*<<< orphan*/  TXCOESEL ; 
 int /*<<< orphan*/  TXFIFOSIZE ; 
 int /*<<< orphan*/  TXQCNT ; 
 int /*<<< orphan*/  VLHASH ; 
 void* XGMAC_GET_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* XGMAC_IOREAD (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct xgbe_hw_features*,int /*<<< orphan*/ ,int) ; 

void xgbe_get_all_hw_features(struct xgbe_prv_data *pdata)
{
	unsigned int mac_hfr0, mac_hfr1, mac_hfr2;
	struct xgbe_hw_features *hw_feat = &pdata->hw_feat;

	DBGPR("-->xgbe_get_all_hw_features\n");

	mac_hfr0 = XGMAC_IOREAD(pdata, MAC_HWF0R);
	mac_hfr1 = XGMAC_IOREAD(pdata, MAC_HWF1R);
	mac_hfr2 = XGMAC_IOREAD(pdata, MAC_HWF2R);

	memset(hw_feat, 0, sizeof(*hw_feat));

	hw_feat->version = XGMAC_IOREAD(pdata, MAC_VR);

	/* Hardware feature register 0 */
	hw_feat->gmii        = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, GMIISEL);
	hw_feat->vlhash      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, VLHASH);
	hw_feat->sma         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SMASEL);
	hw_feat->rwk         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RWKSEL);
	hw_feat->mgk         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MGKSEL);
	hw_feat->mmc         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, MMCSEL);
	hw_feat->aoe         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, ARPOFFSEL);
	hw_feat->ts          = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSEL);
	hw_feat->eee         = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, EEESEL);
	hw_feat->tx_coe      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TXCOESEL);
	hw_feat->rx_coe      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, RXCOESEL);
	hw_feat->addn_mac    = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R,
					      ADDMACADRSEL);
	hw_feat->ts_src      = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, TSSTSSEL);
	hw_feat->sa_vlan_ins = XGMAC_GET_BITS(mac_hfr0, MAC_HWF0R, SAVLANINS);

	/* Hardware feature register 1 */
	hw_feat->rx_fifo_size  = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						RXFIFOSIZE);
	hw_feat->tx_fifo_size  = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						TXFIFOSIZE);
	hw_feat->adv_ts_hi     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, ADVTHWORD);
	hw_feat->dma_width     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, ADDR64);
	hw_feat->dcb           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DCBEN);
	hw_feat->sph           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, SPHEN);
	hw_feat->tso           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, TSOEN);
	hw_feat->dma_debug     = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, DBGMEMA);
	hw_feat->rss           = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, RSSEN);
	hw_feat->tc_cnt	       = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R, NUMTC);
	hw_feat->hash_table_size = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  HASHTBLSZ);
	hw_feat->l3l4_filter_num = XGMAC_GET_BITS(mac_hfr1, MAC_HWF1R,
						  L3L4FNUM);

	/* Hardware feature register 2 */
	hw_feat->rx_q_cnt     = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXQCNT);
	hw_feat->tx_q_cnt     = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXQCNT);
	hw_feat->rx_ch_cnt    = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, RXCHCNT);
	hw_feat->tx_ch_cnt    = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, TXCHCNT);
	hw_feat->pps_out_num  = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, PPSOUTNUM);
	hw_feat->aux_snap_num = XGMAC_GET_BITS(mac_hfr2, MAC_HWF2R, AUXSNAPNUM);

	/* Translate the Hash Table size into actual number */
	switch (hw_feat->hash_table_size) {
	case 0:
		break;
	case 1:
		hw_feat->hash_table_size = 64;
		break;
	case 2:
		hw_feat->hash_table_size = 128;
		break;
	case 3:
		hw_feat->hash_table_size = 256;
		break;
	}

	/* Translate the address width setting into actual number */
	switch (hw_feat->dma_width) {
	case 0:
		hw_feat->dma_width = 32;
		break;
	case 1:
		hw_feat->dma_width = 40;
		break;
	case 2:
		hw_feat->dma_width = 48;
		break;
	default:
		hw_feat->dma_width = 32;
	}

	/* The Queue, Channel and TC counts are zero based so increment them
	 * to get the actual number
	 */
	hw_feat->rx_q_cnt++;
	hw_feat->tx_q_cnt++;
	hw_feat->rx_ch_cnt++;
	hw_feat->tx_ch_cnt++;
	hw_feat->tc_cnt++;

	DBGPR("<--xgbe_get_all_hw_features\n");
}