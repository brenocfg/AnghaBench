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
struct rtwn_softc {char* name; char* fwname; int fwsig; int ackto; int txdesc_len; int rcr; int ntxchains; int nrxchains; void** bcn_status_reg; int /*<<< orphan*/  temp_delta; int /*<<< orphan*/  fwsize_limit; int /*<<< orphan*/  cam_entry_limit; scalar_t__ macid_limit; int /*<<< orphan*/  rx_dma_size; int /*<<< orphan*/  efuse_maplen; int /*<<< orphan*/  efuse_maxlen; int /*<<< orphan*/  page_size; int /*<<< orphan*/  npubqpages; int /*<<< orphan*/  pktbuf_count; int /*<<< orphan*/  page_count; int /*<<< orphan*/ * rf_prog; void* agc_size; int /*<<< orphan*/ * agc_prog; void* bb_size; int /*<<< orphan*/ * bb_prog; void* mac_size; int /*<<< orphan*/ * mac_prog; void** chan_num_5ghz; int /*<<< orphan*/ ** chan_list_5ghz; int /*<<< orphan*/  sc_init_bcnq1_boundary; int /*<<< orphan*/  sc_post_init; int /*<<< orphan*/  sc_init_antsel; int /*<<< orphan*/  sc_init_rf; int /*<<< orphan*/  sc_init_bb; int /*<<< orphan*/  sc_init_edca; int /*<<< orphan*/  sc_init_intr; int /*<<< orphan*/  sc_init_ampdu; int /*<<< orphan*/  sc_init_rx_agg; int /*<<< orphan*/  sc_init_tx_agg; int /*<<< orphan*/  sc_temp_read; int /*<<< orphan*/  sc_temp_measure; void* sc_beacon_select; int /*<<< orphan*/  sc_beacon_set_rate; int /*<<< orphan*/  sc_beacon_enable; int /*<<< orphan*/  sc_beacon_init; void* sc_set_media_status; void* sc_set_rssi; int /*<<< orphan*/  sc_set_pwrmode; int /*<<< orphan*/  sc_set_rsvd_page; int /*<<< orphan*/  sc_detach_private; int /*<<< orphan*/  sc_postattach; int /*<<< orphan*/  sc_vap_preattach; int /*<<< orphan*/  sc_adj_devcaps; int /*<<< orphan*/  sc_read_chipid_vendor; int /*<<< orphan*/  sc_iq_calib; int /*<<< orphan*/  sc_lc_calib; int /*<<< orphan*/  sc_set_page_size; int /*<<< orphan*/  sc_llt_init; int /*<<< orphan*/  sc_fw_download_enable; int /*<<< orphan*/  sc_fw_reset; int /*<<< orphan*/  sc_power_off; int /*<<< orphan*/  sc_power_on; int /*<<< orphan*/  sc_parse_rom; void* sc_efuse_postread; int /*<<< orphan*/  sc_check_condition; int /*<<< orphan*/  sc_rf_write; int /*<<< orphan*/  sc_check_frame; int /*<<< orphan*/  sc_handle_c2h_report; int /*<<< orphan*/  sc_handle_tx_report; int /*<<< orphan*/  sc_classify_intr; int /*<<< orphan*/  sc_get_rssi_ofdm; int /*<<< orphan*/  sc_get_rssi_cck; int /*<<< orphan*/  sc_get_rx_stats; int /*<<< orphan*/  sc_rx_radiotap_flags; int /*<<< orphan*/  sc_tx_radiotap_flags; int /*<<< orphan*/  sc_dump_tx_desc; int /*<<< orphan*/  sc_fill_tx_desc_null; int /*<<< orphan*/  sc_fill_tx_desc_raw; int /*<<< orphan*/  sc_fill_tx_desc; int /*<<< orphan*/  sc_set_chan; int /*<<< orphan*/  sc_flags; } ;
struct rtwn_usb_softc {int tx_agg_desc_num; int /*<<< orphan*/  uc_align_rx; struct rtwn_softc uc_sc; } ;
struct r12au_tx_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R12A_CAM_ENTRY_COUNT ; 
 int /*<<< orphan*/  R12A_EFUSE_MAP_LEN ; 
 int /*<<< orphan*/  R12A_EFUSE_MAX_LEN ; 
 scalar_t__ R12A_MACID_MAX ; 
 int /*<<< orphan*/  R12A_MAX_FW_SIZE ; 
 int /*<<< orphan*/  R12A_PUBQ_NPAGES ; 
 int R12A_RCR_DIS_CHK_14 ; 
 int R12A_RCR_TCP_OFFLD_EN ; 
 int R12A_RCR_VHT_ACK ; 
 int /*<<< orphan*/  R12A_RX_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  R12A_TXPKTBUF_COUNT ; 
 int /*<<< orphan*/  R12A_TX_PAGE_COUNT ; 
 int /*<<< orphan*/  R12A_TX_PAGE_SIZE ; 
 int /*<<< orphan*/  R88E_CALIB_THRESHOLD ; 
 void* R92C_TDECTRL ; 
 int /*<<< orphan*/  RTWN_FLAG_EXT_HDR ; 
 void* nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r12a_attach_private (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r12a_beacon_init ; 
 int /*<<< orphan*/  r12a_beacon_set_rate ; 
 int /*<<< orphan*/ * r12a_chan_5ghz_0 ; 
 int /*<<< orphan*/ * r12a_chan_5ghz_1 ; 
 int /*<<< orphan*/ * r12a_chan_5ghz_2 ; 
 int /*<<< orphan*/  r12a_check_condition ; 
 int /*<<< orphan*/  r12a_check_frame_checksum ; 
 int /*<<< orphan*/  r12a_detach_private ; 
 int /*<<< orphan*/  r12a_fill_tx_desc ; 
 int /*<<< orphan*/  r12a_fill_tx_desc_null ; 
 int /*<<< orphan*/  r12a_fill_tx_desc_raw ; 
 int /*<<< orphan*/  r12a_fw_download_enable ; 
 int /*<<< orphan*/  r12a_fw_reset ; 
 int /*<<< orphan*/  r12a_get_rx_stats ; 
 int /*<<< orphan*/  r12a_handle_c2h_report ; 
 int /*<<< orphan*/  r12a_init_antsel ; 
 int /*<<< orphan*/  r12a_init_bb ; 
 int /*<<< orphan*/  r12a_init_edca ; 
 int /*<<< orphan*/  r12a_init_intr ; 
 int /*<<< orphan*/  r12a_init_rf ; 
 int /*<<< orphan*/  r12a_iq_calib ; 
 int /*<<< orphan*/  r12a_lc_calib ; 
 int /*<<< orphan*/  r12a_parse_rom ; 
 int /*<<< orphan*/  r12a_power_off ; 
 int /*<<< orphan*/  r12a_power_on ; 
 int /*<<< orphan*/  r12a_ratectl_tx_complete ; 
 int /*<<< orphan*/  r12a_read_chipid_vendor ; 
 int /*<<< orphan*/  r12a_rf_write ; 
 int /*<<< orphan*/  r12a_rx_radiotap_flags ; 
 int /*<<< orphan*/  r12a_set_chan ; 
 void* r12a_set_media_status ; 
 int /*<<< orphan*/  r12a_set_page_size ; 
 int /*<<< orphan*/  r12a_set_pwrmode ; 
 int /*<<< orphan*/  r12a_tx_radiotap_flags ; 
 int /*<<< orphan*/  r12a_vap_preattach ; 
 int /*<<< orphan*/  r12au_adj_devcaps ; 
 int /*<<< orphan*/  r12au_align_rx ; 
 int /*<<< orphan*/  r12au_classify_intr ; 
 int /*<<< orphan*/  r12au_dump_tx_desc ; 
 int /*<<< orphan*/  r12au_init_ampdu ; 
 int /*<<< orphan*/  r12au_init_rx_agg ; 
 int /*<<< orphan*/  r12au_post_init ; 
 int /*<<< orphan*/  r12au_postattach ; 
 int /*<<< orphan*/  r88e_get_rssi_cck ; 
 int /*<<< orphan*/  r88e_get_rssi_ofdm ; 
 int /*<<< orphan*/  r88e_set_rsvd_page ; 
 int /*<<< orphan*/  r88e_temp_measure ; 
 int /*<<< orphan*/  r88e_temp_read ; 
 int /*<<< orphan*/  r92c_beacon_enable ; 
 int /*<<< orphan*/  r92c_llt_init ; 
 int /*<<< orphan*/  r92cu_init_tx_agg ; 
 int /*<<< orphan*/ * rtl8812au_agc ; 
 int /*<<< orphan*/ * rtl8812au_bb ; 
 int /*<<< orphan*/ * rtl8812au_mac ; 
 int /*<<< orphan*/ * rtl8812au_rf ; 
 int /*<<< orphan*/  rtwn_nop_int_softc ; 
 void* rtwn_nop_softc ; 
 void* rtwn_nop_softc_int ; 

void
r12au_attach(struct rtwn_usb_softc *uc)
{
	struct rtwn_softc *sc		= &uc->uc_sc;

	/* USB part. */
	uc->uc_align_rx			= r12au_align_rx;
	uc->tx_agg_desc_num		= 1;

	/* Common part. */
	sc->sc_flags			= RTWN_FLAG_EXT_HDR;

	sc->sc_set_chan			= r12a_set_chan;
	sc->sc_fill_tx_desc		= r12a_fill_tx_desc;
	sc->sc_fill_tx_desc_raw 	= r12a_fill_tx_desc_raw;
	sc->sc_fill_tx_desc_null	= r12a_fill_tx_desc_null;
	sc->sc_dump_tx_desc		= r12au_dump_tx_desc;
	sc->sc_tx_radiotap_flags	= r12a_tx_radiotap_flags;
	sc->sc_rx_radiotap_flags	= r12a_rx_radiotap_flags;
	sc->sc_get_rx_stats		= r12a_get_rx_stats;
	sc->sc_get_rssi_cck		= r88e_get_rssi_cck;
	sc->sc_get_rssi_ofdm		= r88e_get_rssi_ofdm;
	sc->sc_classify_intr		= r12au_classify_intr;
	sc->sc_handle_tx_report		= r12a_ratectl_tx_complete;
	sc->sc_handle_c2h_report	= r12a_handle_c2h_report;
	sc->sc_check_frame		= r12a_check_frame_checksum;
	sc->sc_rf_write			= r12a_rf_write;
	sc->sc_check_condition		= r12a_check_condition;
	sc->sc_efuse_postread		= rtwn_nop_softc;
	sc->sc_parse_rom		= r12a_parse_rom;
	sc->sc_power_on			= r12a_power_on;
	sc->sc_power_off		= r12a_power_off;
#ifndef RTWN_WITHOUT_UCODE
	sc->sc_fw_reset			= r12a_fw_reset;
	sc->sc_fw_download_enable	= r12a_fw_download_enable;
#endif
	sc->sc_llt_init			= r92c_llt_init;
	sc->sc_set_page_size		= r12a_set_page_size;
	sc->sc_lc_calib			= r12a_lc_calib;
	sc->sc_iq_calib			= r12a_iq_calib;
	sc->sc_read_chipid_vendor	= r12a_read_chipid_vendor;
	sc->sc_adj_devcaps		= r12au_adj_devcaps;
	sc->sc_vap_preattach		= r12a_vap_preattach;
	sc->sc_postattach		= r12au_postattach;
	sc->sc_detach_private		= r12a_detach_private;
#ifndef RTWN_WITHOUT_UCODE
	sc->sc_set_media_status		= r12a_set_media_status;
	sc->sc_set_rsvd_page		= r88e_set_rsvd_page;
	sc->sc_set_pwrmode		= r12a_set_pwrmode;
	sc->sc_set_rssi			= rtwn_nop_softc;	/* XXX TODO */
#else
	sc->sc_set_media_status		= rtwn_nop_softc_int;
#endif
	sc->sc_beacon_init		= r12a_beacon_init;
	sc->sc_beacon_enable		= r92c_beacon_enable;
	sc->sc_beacon_set_rate		= r12a_beacon_set_rate;
	sc->sc_beacon_select		= rtwn_nop_softc_int;
	sc->sc_temp_measure		= r88e_temp_measure;
	sc->sc_temp_read		= r88e_temp_read;
	sc->sc_init_tx_agg		= r92cu_init_tx_agg;
	sc->sc_init_rx_agg		= r12au_init_rx_agg;
	sc->sc_init_ampdu		= r12au_init_ampdu;
	sc->sc_init_intr		= r12a_init_intr;
	sc->sc_init_edca		= r12a_init_edca;
	sc->sc_init_bb			= r12a_init_bb;
	sc->sc_init_rf			= r12a_init_rf;
	sc->sc_init_antsel		= r12a_init_antsel;
	sc->sc_post_init		= r12au_post_init;
	sc->sc_init_bcnq1_boundary	= rtwn_nop_int_softc;

	sc->chan_list_5ghz[0]		= r12a_chan_5ghz_0;
	sc->chan_list_5ghz[1]		= r12a_chan_5ghz_1;
	sc->chan_list_5ghz[2]		= r12a_chan_5ghz_2;
	sc->chan_num_5ghz[0]		= nitems(r12a_chan_5ghz_0);
	sc->chan_num_5ghz[1]		= nitems(r12a_chan_5ghz_1);
	sc->chan_num_5ghz[2]		= nitems(r12a_chan_5ghz_2);

	sc->mac_prog			= &rtl8812au_mac[0];
	sc->mac_size			= nitems(rtl8812au_mac);
	sc->bb_prog			= &rtl8812au_bb[0];
	sc->bb_size			= nitems(rtl8812au_bb);
	sc->agc_prog			= &rtl8812au_agc[0];
	sc->agc_size			= nitems(rtl8812au_agc);
	sc->rf_prog			= &rtl8812au_rf[0];

	sc->name			= "RTL8812AU";
	sc->fwname			= "rtwn-rtl8812aufw";
	sc->fwsig			= 0x950;

	sc->page_count			= R12A_TX_PAGE_COUNT;
	sc->pktbuf_count		= R12A_TXPKTBUF_COUNT;

	sc->ackto			= 0x80;
	sc->npubqpages			= R12A_PUBQ_NPAGES;
	sc->page_size			= R12A_TX_PAGE_SIZE;

	sc->txdesc_len			= sizeof(struct r12au_tx_desc);
	sc->efuse_maxlen		= R12A_EFUSE_MAX_LEN;
	sc->efuse_maplen		= R12A_EFUSE_MAP_LEN;
	sc->rx_dma_size			= R12A_RX_DMA_BUFFER_SIZE;

	sc->macid_limit			= R12A_MACID_MAX + 1;
	sc->cam_entry_limit		= R12A_CAM_ENTRY_COUNT;
	sc->fwsize_limit		= R12A_MAX_FW_SIZE;
	sc->temp_delta			= R88E_CALIB_THRESHOLD;

	sc->bcn_status_reg[0]		= R92C_TDECTRL;
	sc->bcn_status_reg[1]		= R92C_TDECTRL;
	sc->rcr				= R12A_RCR_DIS_CHK_14 |
					  R12A_RCR_VHT_ACK |
					  R12A_RCR_TCP_OFFLD_EN;

	sc->ntxchains			= 2;
	sc->nrxchains			= 2;

	r12a_attach_private(sc);
}