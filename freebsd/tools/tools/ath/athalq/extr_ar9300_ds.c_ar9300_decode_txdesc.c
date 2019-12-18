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
struct TYPE_2__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;
struct ar9300_txc {int ds_ctl10; int ds_info; int ds_link; int ds_data0; int ds_ctl3; int ds_data1; int ds_ctl5; int ds_data2; int ds_ctl7; int ds_data3; int ds_ctl9; int ds_ctl11; int ds_ctl12; int ds_ctl13; int ds_ctl14; int ds_ctl15; int ds_ctl16; int ds_ctl17; int ds_ctl18; int ds_ctl19; int ds_ctl20; int ds_ctl21; int ds_ctl22; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_2040_0 ; 
 int /*<<< orphan*/  AR_2040_1 ; 
 int /*<<< orphan*/  AR_2040_2 ; 
 int /*<<< orphan*/  AR_2040_3 ; 
 int /*<<< orphan*/  AR_aggr_len ; 
 int /*<<< orphan*/  AR_buf_len ; 
 int /*<<< orphan*/  AR_burst_dur ; 
 int /*<<< orphan*/  AR_calibrating ; 
 int /*<<< orphan*/  AR_chain_sel0 ; 
 int /*<<< orphan*/  AR_chain_sel1 ; 
 int /*<<< orphan*/  AR_chain_sel2 ; 
 int /*<<< orphan*/  AR_chain_sel3 ; 
 int /*<<< orphan*/  AR_clr_dest_mask ; 
 int /*<<< orphan*/  AR_corrupt_fcs ; 
 int /*<<< orphan*/  AR_ctrl_stat ; 
 int /*<<< orphan*/  AR_cts_enable ; 
 int /*<<< orphan*/  AR_desc_id ; 
 int /*<<< orphan*/  AR_dest_idx ; 
 int /*<<< orphan*/  AR_dest_idx_valid ; 
 int /*<<< orphan*/  AR_dur_update_ena ; 
 int /*<<< orphan*/  AR_encr_type ; 
 int /*<<< orphan*/  AR_ext_and_ctl ; 
 int /*<<< orphan*/  AR_ext_only ; 
 int AR_frame_len ; 
 int /*<<< orphan*/  AR_frame_type ; 
 int /*<<< orphan*/  AR_gi0 ; 
 int /*<<< orphan*/  AR_gi1 ; 
 int /*<<< orphan*/  AR_gi2 ; 
 int /*<<< orphan*/  AR_gi3 ; 
 int /*<<< orphan*/  AR_insert_ts ; 
 int /*<<< orphan*/  AR_is_aggr ; 
 int /*<<< orphan*/  AR_ldpc ; 
 int /*<<< orphan*/  AR_loc_mode ; 
 int /*<<< orphan*/  AR_low_rx_chain ; 
 int /*<<< orphan*/  AR_more_rifs ; 
 int /*<<< orphan*/  AR_ness ; 
 int /*<<< orphan*/  AR_ness1 ; 
 int /*<<< orphan*/  AR_ness2 ; 
 int /*<<< orphan*/  AR_ness3 ; 
 int /*<<< orphan*/  AR_no_ack ; 
 int /*<<< orphan*/  AR_not_sounding ; 
 int /*<<< orphan*/  AR_packet_dur0 ; 
 int /*<<< orphan*/  AR_packet_dur1 ; 
 int /*<<< orphan*/  AR_packet_dur2 ; 
 int /*<<< orphan*/  AR_packet_dur3 ; 
 int /*<<< orphan*/  AR_pad_delim ; 
 int /*<<< orphan*/  AR_paprd_chain_mask ; 
 int /*<<< orphan*/  AR_rts_cts_qual0 ; 
 int /*<<< orphan*/  AR_rts_cts_qual1 ; 
 int /*<<< orphan*/  AR_rts_cts_qual2 ; 
 int /*<<< orphan*/  AR_rts_cts_qual3 ; 
 int /*<<< orphan*/  AR_rts_enable ; 
 int /*<<< orphan*/  AR_stbc0 ; 
 int /*<<< orphan*/  AR_stbc1 ; 
 int /*<<< orphan*/  AR_stbc2 ; 
 int /*<<< orphan*/  AR_stbc3 ; 
 int AR_tx_ant0 ; 
 int AR_tx_ant1 ; 
 int AR_tx_ant2 ; 
 int AR_tx_ant3 ; 
 int /*<<< orphan*/  AR_tx_ant_sel0 ; 
 int /*<<< orphan*/  AR_tx_ant_sel1 ; 
 int /*<<< orphan*/  AR_tx_ant_sel2 ; 
 int /*<<< orphan*/  AR_tx_ant_sel3 ; 
 int /*<<< orphan*/  AR_tx_clear_retry ; 
 int /*<<< orphan*/  AR_tx_dc_ap_sta_sel ; 
 int /*<<< orphan*/  AR_tx_desc_id ; 
 int /*<<< orphan*/  AR_tx_intr_req ; 
 int /*<<< orphan*/  AR_tx_more ; 
 int AR_tx_ptr_chk_sum ; 
 int /*<<< orphan*/  AR_tx_qcu_num ; 
 int /*<<< orphan*/  AR_veol ; 
 int /*<<< orphan*/  AR_virt_more_frag ; 
 int /*<<< orphan*/  AR_xmit_data_tries0 ; 
 int /*<<< orphan*/  AR_xmit_data_tries1 ; 
 int /*<<< orphan*/  AR_xmit_data_tries2 ; 
 int /*<<< orphan*/  AR_xmit_data_tries3 ; 
 int /*<<< orphan*/  AR_xmit_power0 ; 
 int /*<<< orphan*/  AR_xmit_power1 ; 
 int /*<<< orphan*/  AR_xmit_power2 ; 
 int /*<<< orphan*/  AR_xmit_power3 ; 
 int /*<<< orphan*/  AR_xmit_rate0 ; 
 int /*<<< orphan*/  AR_xmit_rate1 ; 
 int /*<<< orphan*/  AR_xmit_rate2 ; 
 int /*<<< orphan*/  AR_xmit_rate3 ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar9300_txc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar9300_decode_txdesc(struct if_ath_alq_payload *a)
{
	struct ar9300_txc txc;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txc, &a->payload, 96);

	printf("[%u.%06u] [%llu] TXD DescId=0x%04x\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    (unsigned int) MS(txc.ds_ctl10, AR_tx_desc_id));

	printf("  DescLen=%d, TxQcuNum=%d, CtrlStat=%d, DescId=0x%04x\n",
	    txc.ds_info & 0xff,
	    MS(txc.ds_info, AR_tx_qcu_num),
	    MS(txc.ds_info, AR_ctrl_stat),
	    MS(txc.ds_info, AR_desc_id));

	/* link */
	printf("    Link 0x%08x\n", txc.ds_link);

	/* data0 */
	printf("    Data0 0x%08x Len %d\n",
	    txc.ds_data0,
	    MS(txc.ds_ctl3, AR_buf_len));

	/* data1 */
	printf("    Data1 0x%08x Len %d\n",
	    txc.ds_data1,
	    MS(txc.ds_ctl5, AR_buf_len));

	/* data2 */
	printf("    Data2 0x%08x Len %d\n",
	    txc.ds_data2,
	    MS(txc.ds_ctl7, AR_buf_len));

	/* data3 */
	printf("    Data3 0x%08x Len %d\n",
	    txc.ds_data3,
	    MS(txc.ds_ctl9, AR_buf_len));
	

	/* ctl10 */
	printf("    Desc ID=0x%04x, Chksum=0x%04x (ctl10=0x%08x)\n",
	    MS(txc.ds_ctl10, AR_tx_desc_id),
	    txc.ds_ctl10 & AR_tx_ptr_chk_sum,
	    txc.ds_ctl10);

	/* ctl11 */
	printf("    Frame Len=%d, VMF=%d, LowRxChain=%d, TxClrRetry=%d\n",
	     txc.ds_ctl11 & AR_frame_len,
	    MF(txc.ds_ctl11, AR_virt_more_frag),
	    MF(txc.ds_ctl11, AR_low_rx_chain),
	    MF(txc.ds_ctl11, AR_tx_clear_retry));
	printf("    TX power 0 = %d, RtsEna=%d, Veol=%d, ClrDstMask=%d\n",
	    MS(txc.ds_ctl11, AR_xmit_power0),
	    MF(txc.ds_ctl11, AR_rts_enable),
	    MF(txc.ds_ctl11, AR_veol),
	    MF(txc.ds_ctl11, AR_clr_dest_mask));
	printf("    TxIntrReq=%d, DestIdxValid=%d, CtsEnable=%d\n",
	    MF(txc.ds_ctl11, AR_tx_intr_req),
	    MF(txc.ds_ctl11, AR_dest_idx_valid),
	    MF(txc.ds_ctl11, AR_cts_enable));

	/* ctl12 */
	printf("    Paprd Chain Mask=0x%x, TxMore=%d, DestIdx=%d,"
	    " FrType=0x%x\n",
	    MS(txc.ds_ctl12, AR_paprd_chain_mask),
	    MF(txc.ds_ctl12, AR_tx_more),
	    MS(txc.ds_ctl12, AR_dest_idx),
	    MS(txc.ds_ctl12, AR_frame_type));
	printf("    NoAck=%d, InsertTs=%d, CorruptFcs=%d, ExtOnly=%d,"
	    " ExtAndCtl=%d\n",
	    MF(txc.ds_ctl12, AR_no_ack),
	    MF(txc.ds_ctl12, AR_insert_ts),
	    MF(txc.ds_ctl12, AR_corrupt_fcs),
	    MF(txc.ds_ctl12, AR_ext_only),
	    MF(txc.ds_ctl12, AR_ext_and_ctl));
	printf("    IsAggr=%d, MoreRifs=%d, LocMode=%d\n",
	    MF(txc.ds_ctl12, AR_is_aggr),
	    MF(txc.ds_ctl12, AR_more_rifs),
	    MF(txc.ds_ctl12, AR_loc_mode));


	/* ctl13 */
	printf("    DurUpEna=%d, Burstdur=0x%04x\n",
	    MF(txc.ds_ctl13, AR_dur_update_ena),
	    MS(txc.ds_ctl13, AR_burst_dur));
	printf("    Try0=%d, Try1=%d, Try2=%d, Try3=%d\n",
	    MS(txc.ds_ctl13, AR_xmit_data_tries0),
	    MS(txc.ds_ctl13, AR_xmit_data_tries1),
	    MS(txc.ds_ctl13, AR_xmit_data_tries2),
	    MS(txc.ds_ctl13, AR_xmit_data_tries3));

	/* ctl14 */
	printf("    rate0=0x%02x, rate1=0x%02x, rate2=0x%02x, rate3=0x%02x\n",
	    MS(txc.ds_ctl14, AR_xmit_rate0),
	    MS(txc.ds_ctl14, AR_xmit_rate1),
	    MS(txc.ds_ctl14, AR_xmit_rate2),
	    MS(txc.ds_ctl14, AR_xmit_rate3));

	/* ctl15 */
	printf("    try 0: PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl15, AR_packet_dur0),
	    MF(txc.ds_ctl15, AR_rts_cts_qual0));
	printf("    try 1: PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl15, AR_packet_dur1),
	    MF(txc.ds_ctl15, AR_rts_cts_qual1));

	/* ctl16 */
	printf("    try 2: PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl16, AR_packet_dur2),
	    MF(txc.ds_ctl16, AR_rts_cts_qual2));
	printf("    try 3: PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl16, AR_packet_dur3),
	    MF(txc.ds_ctl16, AR_rts_cts_qual3));

	/* ctl17 */
	printf("    AggrLen=%d, PadDelim=%d, EncrType=%d, TxDcApStaSel=%d\n",
	    MS(txc.ds_ctl17, AR_aggr_len),
	    MS(txc.ds_ctl17, AR_pad_delim),
	    MS(txc.ds_ctl17, AR_encr_type),
	    MF(txc.ds_ctl17, AR_tx_dc_ap_sta_sel));
	printf("    Calib=%d LDPC=%d\n",
	    MF(txc.ds_ctl17, AR_calibrating),
	    MF(txc.ds_ctl17, AR_ldpc));

	/* ctl18 */
	printf("    try 0: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl18, AR_chain_sel0),
	    MF(txc.ds_ctl18, AR_gi0),
	    MF(txc.ds_ctl18, AR_2040_0),
	    MF(txc.ds_ctl18, AR_stbc0));
	printf("    try 1: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl18, AR_chain_sel1),
	    MF(txc.ds_ctl18, AR_gi1),
	    MF(txc.ds_ctl18, AR_2040_1),
	    MF(txc.ds_ctl18, AR_stbc1));
	printf("    try 2: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl18, AR_chain_sel2),
	    MF(txc.ds_ctl18, AR_gi2),
	    MF(txc.ds_ctl18, AR_2040_2),
	    MF(txc.ds_ctl18, AR_stbc2));
	printf("    try 3: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl18, AR_chain_sel3),
	    MF(txc.ds_ctl18, AR_gi3),
	    MF(txc.ds_ctl18, AR_2040_3),
	    MF(txc.ds_ctl18, AR_stbc3));

	/* ctl19 */
	printf("    NotSounding=%d\n",
	    MF(txc.ds_ctl19, AR_not_sounding));

	printf("    try 0: ant=0x%08x, antsel=%d, ness=%d\n",
	    txc.ds_ctl19 &  AR_tx_ant0,
	    MF(txc.ds_ctl19, AR_tx_ant_sel0),
	    MS(txc.ds_ctl19, AR_ness));

	/* ctl20 */
	printf("    try 1: TxPower=%d, ant=0x%08x, antsel=%d, ness=%d\n",
	    MS(txc.ds_ctl20, AR_xmit_power1),
	    txc.ds_ctl20 &  AR_tx_ant1,
	    MF(txc.ds_ctl20, AR_tx_ant_sel1),
	    MS(txc.ds_ctl20, AR_ness1));

	/* ctl21 */
	printf("    try 2: TxPower=%d, ant=0x%08x, antsel=%d, ness=%d\n",
	    MS(txc.ds_ctl21, AR_xmit_power2),
	    txc.ds_ctl21 &  AR_tx_ant2,
	    MF(txc.ds_ctl21, AR_tx_ant_sel2),
	    MS(txc.ds_ctl21, AR_ness2));

	/* ctl22 */
	printf("    try 3: TxPower=%d, ant=0x%08x, antsel=%d, ness=%d\n",
	    MS(txc.ds_ctl22, AR_xmit_power3),
	    txc.ds_ctl22 &  AR_tx_ant3,
	    MF(txc.ds_ctl22, AR_tx_ant_sel3),
	    MS(txc.ds_ctl22, AR_ness3));

	printf("\n ------ \n");
}