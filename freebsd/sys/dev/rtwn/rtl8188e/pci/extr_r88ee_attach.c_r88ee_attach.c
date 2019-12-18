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
struct rtwn_softc {char* name; char* fwname; int fwsig; int ackto; int txdesc_len; int ntxchains; int nrxchains; scalar_t__ rcr; void** bcn_status_reg; int /*<<< orphan*/  temp_delta; int /*<<< orphan*/  fwsize_limit; int /*<<< orphan*/  cam_entry_limit; scalar_t__ macid_limit; int /*<<< orphan*/  rx_dma_size; int /*<<< orphan*/  efuse_maplen; int /*<<< orphan*/  efuse_maxlen; int /*<<< orphan*/  page_size; int /*<<< orphan*/  nlqpages; int /*<<< orphan*/  nnqpages; int /*<<< orphan*/  nhqpages; int /*<<< orphan*/  npubqpages; int /*<<< orphan*/  pktbuf_count; int /*<<< orphan*/  page_count; int /*<<< orphan*/ * rf_prog; void* agc_size; int /*<<< orphan*/ * agc_prog; void* bb_size; int /*<<< orphan*/ * bb_prog; void* mac_size; int /*<<< orphan*/ * mac_prog; int /*<<< orphan*/  sc_init_bcnq1_boundary; int /*<<< orphan*/  sc_post_init; void* sc_init_antsel; int /*<<< orphan*/  sc_init_rf; int /*<<< orphan*/  sc_init_bb; int /*<<< orphan*/  sc_init_edca; int /*<<< orphan*/  sc_init_intr; int /*<<< orphan*/  sc_init_ampdu; void* sc_init_rx_agg; void* sc_init_tx_agg; int /*<<< orphan*/  sc_temp_read; int /*<<< orphan*/  sc_temp_measure; int /*<<< orphan*/  sc_beacon_select; int /*<<< orphan*/  sc_beacon_set_rate; int /*<<< orphan*/  sc_beacon_enable; int /*<<< orphan*/  sc_beacon_init; int /*<<< orphan*/  sc_set_rssi; int /*<<< orphan*/  sc_set_pwrmode; int /*<<< orphan*/  sc_set_rsvd_page; int /*<<< orphan*/  sc_set_media_status; int /*<<< orphan*/  sc_detach_private; int /*<<< orphan*/  sc_postattach; int /*<<< orphan*/  sc_vap_preattach; int /*<<< orphan*/  sc_adj_devcaps; int /*<<< orphan*/  sc_read_chipid_vendor; int /*<<< orphan*/  sc_iq_calib; int /*<<< orphan*/  sc_lc_calib; int /*<<< orphan*/  sc_set_page_size; int /*<<< orphan*/  sc_llt_init; int /*<<< orphan*/  sc_fw_download_enable; int /*<<< orphan*/  sc_fw_reset; int /*<<< orphan*/  sc_power_off; int /*<<< orphan*/  sc_power_on; int /*<<< orphan*/  sc_set_led; int /*<<< orphan*/  sc_parse_rom; void* sc_efuse_postread; int /*<<< orphan*/  sc_check_condition; int /*<<< orphan*/  sc_rf_write; int /*<<< orphan*/  sc_rf_read; int /*<<< orphan*/  sc_check_frame; int /*<<< orphan*/  sc_handle_c2h_report; int /*<<< orphan*/  sc_handle_tx_report; int /*<<< orphan*/  sc_classify_intr; int /*<<< orphan*/  sc_get_rssi_ofdm; int /*<<< orphan*/  sc_get_rssi_cck; int /*<<< orphan*/  sc_get_rx_stats; int /*<<< orphan*/  sc_rx_radiotap_flags; int /*<<< orphan*/  sc_tx_radiotap_flags; int /*<<< orphan*/  sc_dump_tx_desc; int /*<<< orphan*/  sc_fill_tx_desc_null; int /*<<< orphan*/  sc_fill_tx_desc_raw; int /*<<< orphan*/  sc_fill_tx_desc; int /*<<< orphan*/  sc_set_chan; int /*<<< orphan*/  sc_start_xfers; int /*<<< orphan*/  sc_flags; } ;
struct rtwn_pci_softc {int pc_qmap; int tcr; int /*<<< orphan*/  pc_get_intr_status; int /*<<< orphan*/  pc_enable_intr; int /*<<< orphan*/  pc_copy_tx_desc; int /*<<< orphan*/  pc_tx_postsetup; int /*<<< orphan*/  pc_setup_tx_desc; struct rtwn_softc pc_sc; } ;
struct r92ce_tx_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R88EE_HPQ_NPAGES ; 
 int /*<<< orphan*/  R88EE_LPQ_NPAGES ; 
 int /*<<< orphan*/  R88EE_NPQ_NPAGES ; 
 int /*<<< orphan*/  R88EE_PUBQ_NPAGES ; 
 int /*<<< orphan*/  R88EE_TX_PAGE_COUNT ; 
 int /*<<< orphan*/  R88E_CALIB_THRESHOLD ; 
 int /*<<< orphan*/  R88E_EFUSE_MAP_LEN ; 
 int /*<<< orphan*/  R88E_EFUSE_MAX_LEN ; 
 scalar_t__ R88E_MACID_MAX ; 
 int /*<<< orphan*/  R88E_RX_DMA_BUFFER_SIZE ; 
 int /*<<< orphan*/  R88E_TXPKTBUF_COUNT ; 
 int /*<<< orphan*/  R92C_CAM_ENTRY_COUNT ; 
 int /*<<< orphan*/  R92C_MAX_FW_SIZE ; 
 void* R92C_TDECTRL ; 
 int /*<<< orphan*/  R92C_TX_PAGE_SIZE ; 
 int /*<<< orphan*/  RTWN_FLAG_EXT_HDR ; 
 void* nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r88e_beacon_enable ; 
 int /*<<< orphan*/  r88e_classify_intr ; 
 int /*<<< orphan*/  r88e_fw_download_enable ; 
 int /*<<< orphan*/  r88e_fw_reset ; 
 int /*<<< orphan*/  r88e_get_rssi_cck ; 
 int /*<<< orphan*/  r88e_get_rssi_ofdm ; 
 int /*<<< orphan*/  r88e_get_rx_stats ; 
 int /*<<< orphan*/  r88e_handle_c2h_report ; 
 int /*<<< orphan*/  r88e_iq_calib ; 
 int /*<<< orphan*/  r88e_parse_rom ; 
 int /*<<< orphan*/  r88e_ratectl_tx_complete ; 
 int /*<<< orphan*/  r88e_rf_write ; 
 int /*<<< orphan*/  r88e_set_led ; 
 int /*<<< orphan*/  r88e_set_media_status ; 
 int /*<<< orphan*/  r88e_set_pwrmode ; 
 int /*<<< orphan*/  r88e_set_rsvd_page ; 
 int /*<<< orphan*/  r88e_temp_measure ; 
 int /*<<< orphan*/  r88e_temp_read ; 
 int /*<<< orphan*/  r88ee_adj_devcaps ; 
 int /*<<< orphan*/  r88ee_attach_private (struct rtwn_softc*) ; 
 int /*<<< orphan*/  r88ee_enable_intr ; 
 int /*<<< orphan*/  r88ee_get_intr_status ; 
 int /*<<< orphan*/  r88ee_init_bb ; 
 int /*<<< orphan*/  r88ee_init_intr ; 
 int /*<<< orphan*/  r88ee_post_init ; 
 int /*<<< orphan*/  r88ee_postattach ; 
 int /*<<< orphan*/  r88ee_power_off ; 
 int /*<<< orphan*/  r88ee_power_on ; 
 int /*<<< orphan*/  r88ee_start_xfers ; 
 int /*<<< orphan*/  r92c_beacon_init ; 
 int /*<<< orphan*/  r92c_check_condition ; 
 int /*<<< orphan*/  r92c_detach_private ; 
 int /*<<< orphan*/  r92c_fill_tx_desc ; 
 int /*<<< orphan*/  r92c_fill_tx_desc_null ; 
 int /*<<< orphan*/  r92c_fill_tx_desc_raw ; 
 int /*<<< orphan*/  r92c_init_rf ; 
 int /*<<< orphan*/  r92c_lc_calib ; 
 int /*<<< orphan*/  r92c_llt_init ; 
 int /*<<< orphan*/  r92c_rf_read ; 
 int /*<<< orphan*/  r92c_rx_radiotap_flags ; 
 int /*<<< orphan*/  r92c_set_chan ; 
 int /*<<< orphan*/  r92c_set_page_size ; 
 int /*<<< orphan*/  r92c_set_rssi ; 
 int /*<<< orphan*/  r92c_tx_radiotap_flags ; 
 int /*<<< orphan*/  r92ce_copy_tx_desc ; 
 int /*<<< orphan*/  r92ce_dump_tx_desc ; 
 int /*<<< orphan*/  r92ce_init_ampdu ; 
 int /*<<< orphan*/  r92ce_init_edca ; 
 int /*<<< orphan*/  r92ce_setup_tx_desc ; 
 int /*<<< orphan*/  r92ce_tx_postsetup ; 
 int /*<<< orphan*/ * rtl8188e_agc ; 
 int /*<<< orphan*/ * rtl8188e_bb ; 
 int /*<<< orphan*/ * rtl8188e_mac ; 
 int /*<<< orphan*/ * rtl8188e_rf ; 
 int /*<<< orphan*/  rtwn_nop_int_softc ; 
 int /*<<< orphan*/  rtwn_nop_int_softc_mbuf ; 
 void* rtwn_nop_softc ; 
 int /*<<< orphan*/  rtwn_nop_softc_int ; 
 int /*<<< orphan*/  rtwn_nop_softc_uint32 ; 
 int /*<<< orphan*/  rtwn_nop_softc_vap ; 
 int /*<<< orphan*/  rtwn_nop_void_int ; 

void
r88ee_attach(struct rtwn_pci_softc *pc)
{
	struct rtwn_softc *sc		= &pc->pc_sc;

	/* PCIe part. */
	pc->pc_setup_tx_desc		= r92ce_setup_tx_desc;
	pc->pc_tx_postsetup		= r92ce_tx_postsetup;
	pc->pc_copy_tx_desc		= r92ce_copy_tx_desc;
	pc->pc_enable_intr		= r88ee_enable_intr;
	pc->pc_get_intr_status		= r88ee_get_intr_status;

	pc->pc_qmap			= 0xe771;
	pc->tcr				= 0x8200;

	/* Common part. */
	sc->sc_flags			= RTWN_FLAG_EXT_HDR;

	sc->sc_start_xfers		= r88ee_start_xfers;
	sc->sc_set_chan			= r92c_set_chan;
	sc->sc_fill_tx_desc		= r92c_fill_tx_desc;
	sc->sc_fill_tx_desc_raw		= r92c_fill_tx_desc_raw;
	sc->sc_fill_tx_desc_null	= r92c_fill_tx_desc_null; /* XXX recheck */
	sc->sc_dump_tx_desc		= r92ce_dump_tx_desc;
	sc->sc_tx_radiotap_flags	= r92c_tx_radiotap_flags;
	sc->sc_rx_radiotap_flags	= r92c_rx_radiotap_flags;
	sc->sc_get_rx_stats		= r88e_get_rx_stats;
	sc->sc_get_rssi_cck		= r88e_get_rssi_cck;
	sc->sc_get_rssi_ofdm		= r88e_get_rssi_ofdm;
	sc->sc_classify_intr		= r88e_classify_intr;
	sc->sc_handle_tx_report		= r88e_ratectl_tx_complete;
	sc->sc_handle_c2h_report	= r88e_handle_c2h_report;
	sc->sc_check_frame		= rtwn_nop_int_softc_mbuf;
	sc->sc_rf_read			= r92c_rf_read;
	sc->sc_rf_write			= r88e_rf_write;
	sc->sc_check_condition		= r92c_check_condition;
	sc->sc_efuse_postread		= rtwn_nop_softc;
	sc->sc_parse_rom		= r88e_parse_rom;
	sc->sc_set_led			= r88e_set_led;
	sc->sc_power_on			= r88ee_power_on;
	sc->sc_power_off		= r88ee_power_off;
#ifndef RTWN_WITHOUT_UCODE
	sc->sc_fw_reset			= r88e_fw_reset;
	sc->sc_fw_download_enable	= r88e_fw_download_enable;
#endif
	sc->sc_llt_init			= r92c_llt_init;
	sc->sc_set_page_size		= r92c_set_page_size;
	sc->sc_lc_calib			= r92c_lc_calib;
	sc->sc_iq_calib			= r88e_iq_calib;
	sc->sc_read_chipid_vendor	= rtwn_nop_softc_uint32;
	sc->sc_adj_devcaps		= r88ee_adj_devcaps;
	sc->sc_vap_preattach		= rtwn_nop_softc_vap;
	sc->sc_postattach		= r88ee_postattach;
	sc->sc_detach_private		= r92c_detach_private;
	sc->sc_set_media_status		= r88e_set_media_status;
#ifndef RTWN_WITHOUT_UCODE
	sc->sc_set_rsvd_page		= r88e_set_rsvd_page;
	sc->sc_set_pwrmode		= r88e_set_pwrmode;
	sc->sc_set_rssi			= r92c_set_rssi;
#endif
	sc->sc_beacon_init		= r92c_beacon_init;
	sc->sc_beacon_enable		= r88e_beacon_enable;
	sc->sc_beacon_set_rate		= rtwn_nop_void_int;
	sc->sc_beacon_select		= rtwn_nop_softc_int;
	sc->sc_temp_measure		= r88e_temp_measure;
	sc->sc_temp_read		= r88e_temp_read;
	sc->sc_init_tx_agg		= rtwn_nop_softc;
	sc->sc_init_rx_agg		= rtwn_nop_softc;
	sc->sc_init_ampdu		= r92ce_init_ampdu;
	sc->sc_init_intr		= r88ee_init_intr;
	sc->sc_init_edca		= r92ce_init_edca;
	sc->sc_init_bb			= r88ee_init_bb;
	sc->sc_init_rf			= r92c_init_rf;
	sc->sc_init_antsel		= rtwn_nop_softc;
	sc->sc_post_init		= r88ee_post_init;
	sc->sc_init_bcnq1_boundary	= rtwn_nop_int_softc;

	sc->mac_prog			= &rtl8188e_mac[0];
	sc->mac_size			= nitems(rtl8188e_mac);
	sc->bb_prog			= &rtl8188e_bb[0];
	sc->bb_size			= nitems(rtl8188e_bb);
	sc->agc_prog			= &rtl8188e_agc[0];
	sc->agc_size			= nitems(rtl8188e_agc);
	sc->rf_prog			= &rtl8188e_rf[0];

	sc->name			= "RTL8188EE";
	sc->fwname			= "rtwn-rtl8188eefw";
	sc->fwsig			= 0x88e;

	sc->page_count			= R88EE_TX_PAGE_COUNT;
	sc->pktbuf_count		= R88E_TXPKTBUF_COUNT;

	sc->ackto			= 0x40;
	sc->npubqpages			= R88EE_PUBQ_NPAGES;
	sc->nhqpages			= R88EE_HPQ_NPAGES;
	sc->nnqpages			= R88EE_NPQ_NPAGES;
	sc->nlqpages			= R88EE_LPQ_NPAGES;
	sc->page_size			= R92C_TX_PAGE_SIZE;

	sc->txdesc_len			= sizeof(struct r92ce_tx_desc);
	sc->efuse_maxlen		= R88E_EFUSE_MAX_LEN;
	sc->efuse_maplen		= R88E_EFUSE_MAP_LEN;
	sc->rx_dma_size			= R88E_RX_DMA_BUFFER_SIZE;

	sc->macid_limit			= R88E_MACID_MAX + 1;
	sc->cam_entry_limit		= R92C_CAM_ENTRY_COUNT;
	sc->fwsize_limit		= R92C_MAX_FW_SIZE;
	sc->temp_delta			= R88E_CALIB_THRESHOLD;

	sc->bcn_status_reg[0]		= R92C_TDECTRL;
	/*
	 * TODO: some additional setup is required
	 * to maintain few beacons at the same time.
	 *
	 * XXX BCNQ1 mechanism is not needed here; move it to the USB module.
	 */
	sc->bcn_status_reg[1]		= R92C_TDECTRL;
	sc->rcr				= 0;

	sc->ntxchains			= 1;
	sc->nrxchains			= 1;

	r88ee_attach_private(sc);
}