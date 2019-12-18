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
struct ar9300_txs {int status4; int status1; int ds_info; int status8; int status3; int status2; int status7; int status5; int status6; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_TXBFStatus ; 
 int /*<<< orphan*/  AR_ctrl_stat ; 
 int /*<<< orphan*/  AR_data_fail_cnt ; 
 int /*<<< orphan*/  AR_desc_cfg_err ; 
 int /*<<< orphan*/  AR_desc_id ; 
 int /*<<< orphan*/  AR_excessive_retries ; 
 int /*<<< orphan*/  AR_fifounderrun ; 
 int /*<<< orphan*/  AR_filtered ; 
 int /*<<< orphan*/  AR_final_tx_idx ; 
 int /*<<< orphan*/  AR_frm_xmit_ok ; 
 int /*<<< orphan*/  AR_power_mgmt ; 
 int /*<<< orphan*/  AR_rts_fail_cnt ; 
 int /*<<< orphan*/  AR_seq_num ; 
 int /*<<< orphan*/  AR_tx_ba_status ; 
 int /*<<< orphan*/  AR_tx_bf_bw_mismatch ; 
 int /*<<< orphan*/  AR_tx_bf_dest_miss ; 
 int /*<<< orphan*/  AR_tx_bf_expired ; 
 int /*<<< orphan*/  AR_tx_bf_stream_miss ; 
 int /*<<< orphan*/  AR_tx_data_underrun ; 
 int /*<<< orphan*/  AR_tx_delim_underrun ; 
 int /*<<< orphan*/  AR_tx_desc_id ; 
 int /*<<< orphan*/  AR_tx_done ; 
 int /*<<< orphan*/  AR_tx_fast_ts ; 
 int /*<<< orphan*/  AR_tx_op_exceeded ; 
 int /*<<< orphan*/  AR_tx_qcu_num ; 
 int /*<<< orphan*/  AR_tx_rssi_ant00 ; 
 int /*<<< orphan*/  AR_tx_rssi_ant01 ; 
 int /*<<< orphan*/  AR_tx_rssi_ant02 ; 
 int /*<<< orphan*/  AR_tx_rssi_ant10 ; 
 int /*<<< orphan*/  AR_tx_rssi_ant11 ; 
 int /*<<< orphan*/  AR_tx_rssi_ant12 ; 
 int /*<<< orphan*/  AR_tx_rssi_combined ; 
 int /*<<< orphan*/  AR_tx_tid ; 
 int /*<<< orphan*/  AR_tx_timer_expired ; 
 int /*<<< orphan*/  AR_virt_retry_cnt ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int last_ts ; 
 int /*<<< orphan*/  memcpy (struct ar9300_txs*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar9300_decode_txstatus(struct if_ath_alq_payload *a)
{
	struct ar9300_txs txs;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txs, &a->payload, sizeof(struct ar9300_txs));

	printf("[%u.%06u] [%llu] TXSTATUS TxTimestamp=%u (%u), DescId=0x%04x, QCU=%d\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    txs.status4,
	    txs.status4 - last_ts,
	    (unsigned int) MS(txs.status1, AR_tx_desc_id),
	    (unsigned int) MS(txs.ds_info, AR_tx_qcu_num));
	printf("    DescId=0x%08x\n", txs.status1);

	last_ts = txs.status4;

	printf("    DescLen=%d, TxQcuNum=%d, CtrlStat=%d, DescId=0x%04x\n",
	    txs.ds_info & 0xff,
	    MS(txs.ds_info, AR_tx_qcu_num),
	    MS(txs.ds_info, AR_ctrl_stat),
	    MS(txs.ds_info, AR_desc_id));

	printf("    TxTimestamp: %u\n", txs.status4);

	printf("    TxDone=%d, SeqNo=%d, TxOpExceed=%d, TXBFStatus=%d\n",
	    MF(txs.status8, AR_tx_done),
	    MS(txs.status8, AR_seq_num),
	    MF(txs.status8, AR_tx_op_exceeded),
	    MS(txs.status8, AR_TXBFStatus));

	printf("    TXBfMismatch=%d, BFStreamMiss=%d, FinalTxIdx=%d\n",
	    MF(txs.status8, AR_tx_bf_bw_mismatch),
	    MF(txs.status8, AR_tx_bf_stream_miss),
	    MS(txs.status8, AR_final_tx_idx));

	printf("    TxBfDestMiss=%d, TxBfExpired=%d, PwrMgmt=%d, Tid=%d,"
	    " FastTsBit=%d\n",
	    MF(txs.status8, AR_tx_bf_dest_miss),
	    MF(txs.status8, AR_tx_bf_expired),
	    MF(txs.status8, AR_power_mgmt),
	    MS(txs.status8, AR_tx_tid),
	    MF(txs.status8, AR_tx_fast_ts));

	printf("    Frmok=%d, xretries=%d, fifounderrun=%d, filt=%d\n",
	    MF(txs.status3, AR_frm_xmit_ok),
	    MF(txs.status3, AR_excessive_retries),
	    MF(txs.status3, AR_fifounderrun),
	    MF(txs.status3, AR_filtered));
	printf("    DelimUnderrun=%d, DataUnderun=%d, DescCfgErr=%d,"
	    " TxTimerExceeded=%d\n",
	    MF(txs.status3, AR_tx_delim_underrun),
	    MF(txs.status3, AR_tx_data_underrun),
	    MF(txs.status3, AR_desc_cfg_err),
	    MF(txs.status3, AR_tx_timer_expired));

	printf("    RTScnt=%d, FailCnt=%d, VRetryCnt=%d\n",
	    MS(txs.status3, AR_rts_fail_cnt),
	    MS(txs.status3, AR_data_fail_cnt),
	    MS(txs.status3, AR_virt_retry_cnt));



	printf("    RX RSSI 0 [%d %d %d]\n",
	    MS(txs.status2, AR_tx_rssi_ant00),
	    MS(txs.status2, AR_tx_rssi_ant01),
	    MS(txs.status2, AR_tx_rssi_ant02));

	printf("    RX RSSI 1 [%d %d %d] Comb=%d\n",
	    MS(txs.status7, AR_tx_rssi_ant10),
	    MS(txs.status7, AR_tx_rssi_ant11),
	    MS(txs.status7, AR_tx_rssi_ant12),
	    MS(txs.status7, AR_tx_rssi_combined));

	printf("    BA Valid=%d\n",
	    MF(txs.status2, AR_tx_ba_status));

	printf("    BALow=0x%08x\n", txs.status5);
	printf("    BAHigh=0x%08x\n", txs.status6);

	printf("\n ------ \n");
}