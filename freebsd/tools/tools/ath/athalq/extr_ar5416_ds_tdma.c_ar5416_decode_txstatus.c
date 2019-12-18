#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;
struct TYPE_6__ {int* status; } ;
struct TYPE_5__ {TYPE_3__ tx; } ;
struct ar5416_desc {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_DataFailCnt ; 
 int /*<<< orphan*/  AR_DescCfgErr ; 
 int /*<<< orphan*/  AR_ExcessiveRetries ; 
 int /*<<< orphan*/  AR_FIFOUnderrun ; 
 int /*<<< orphan*/  AR_Filtered ; 
 int /*<<< orphan*/  AR_FinalTxIdx ; 
 int /*<<< orphan*/  AR_FrmXmitOK ; 
 int /*<<< orphan*/  AR_PowerMgmt ; 
 int /*<<< orphan*/  AR_RTSFailCnt ; 
 int /*<<< orphan*/  AR_SeqNum ; 
 int /*<<< orphan*/  AR_TxBaStatus ; 
 int /*<<< orphan*/  AR_TxDataUnderrun ; 
 int /*<<< orphan*/  AR_TxDelimUnderrun ; 
 int /*<<< orphan*/  AR_TxDone ; 
 int /*<<< orphan*/  AR_TxOpExceeded ; 
 int /*<<< orphan*/  AR_TxRSSIAnt00 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt01 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt02 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt10 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt11 ; 
 int /*<<< orphan*/  AR_TxRSSIAnt12 ; 
 int /*<<< orphan*/  AR_TxRSSICombined ; 
 int /*<<< orphan*/  AR_TxTid ; 
 int /*<<< orphan*/  AR_TxTimerExpired ; 
 int /*<<< orphan*/  AR_VirtRetryCnt ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5416_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5416_decode_txstatus(struct if_ath_alq_payload *a)
{
	struct ar5416_desc txs;
	static uint64_t tx_tsf = 0;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txs, &a->payload, sizeof(struct ar5416_desc));

	if (MF(txs.u.tx.status[9], AR_TxDone) == 0)
		return;

	printf("[%u] [%llu] TXSTATUS: TxDone=%d, TS=0x%08x (delta %d)\n",
	    (unsigned int) be32toh(a->hdr.tstamp),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    MF(txs.u.tx.status[9], AR_TxDone),
	    txs.u.tx.status[2],
	    txs.u.tx.status[2] - tx_tsf);

	tx_tsf = txs.u.tx.status[2];

#if 0
	/* ds_txstatus0 */
	printf("    RX RSSI 0 [%d %d %d]\n",
	    MS(txs.u.tx.status[0], AR_TxRSSIAnt00),
	    MS(txs.u.tx.status[0], AR_TxRSSIAnt01),
	    MS(txs.u.tx.status[0], AR_TxRSSIAnt02));
	printf("    BA Valid=%d\n",
	    MF(txs.u.tx.status[0], AR_TxBaStatus));

	/* ds_txstatus1 */
	printf("    Frmok=%d, xretries=%d, fifounderrun=%d, filt=%d\n",
	    MF(txs.u.tx.status[1], AR_FrmXmitOK),
	    MF(txs.u.tx.status[1], AR_ExcessiveRetries),
	    MF(txs.u.tx.status[1], AR_FIFOUnderrun),
	    MF(txs.u.tx.status[1], AR_Filtered));
	printf("    DelimUnderrun=%d, DataUnderun=%d, DescCfgErr=%d,"
	    " TxTimerExceeded=%d\n",
	    MF(txs.u.tx.status[1], AR_TxDelimUnderrun),
	    MF(txs.u.tx.status[1], AR_TxDataUnderrun),
	    MF(txs.u.tx.status[1], AR_DescCfgErr),
	    MF(txs.u.tx.status[1], AR_TxTimerExpired));

	printf("    RTScnt=%d, FailCnt=%d, VRetryCnt=%d\n",
	    MS(txs.u.tx.status[1], AR_RTSFailCnt),
	    MS(txs.u.tx.status[1], AR_DataFailCnt),
	    MS(txs.u.tx.status[1], AR_VirtRetryCnt));

	/* ds_txstatus2 */
	printf("    TxTimestamp=0x%08x\n", txs.u.tx.status[2]);

	/* ds_txstatus3 */
	/* ds_txstatus4 */
	printf("    BALow=0x%08x\n", txs.u.tx.status[3]);
	printf("    BAHigh=0x%08x\n", txs.u.tx.status[4]);

	/* ds_txstatus5 */
	printf("    RX RSSI 1 [%d %d %d] Comb=%d\n",
	    MS(txs.u.tx.status[5], AR_TxRSSIAnt10),
	    MS(txs.u.tx.status[5], AR_TxRSSIAnt11),
	    MS(txs.u.tx.status[5], AR_TxRSSIAnt12),
	    MS(txs.u.tx.status[5], AR_TxRSSICombined));

	/* ds_txstatus6 */
	/* ds_txstatus7 */
	/* ds_txstatus8 */
	printf("    TxEVM[0]=0x%08x, TxEVM[1]=0x%08x, TxEVM[2]=0x%08x\n",
	    txs.u.tx.status[6],
	    txs.u.tx.status[7],
	    txs.u.tx.status[8]);

	/* ds_txstatus9 */
	printf("    TxDone=%d, SeqNum=0x%04x, TxOpExceeded=%d, FinalTsIdx=%d\n",
	    MF(txs.u.tx.status[9], AR_TxDone),
	    MS(txs.u.tx.status[9], AR_SeqNum),
	    MF(txs.u.tx.status[9], AR_TxOpExceeded),
	    MS(txs.u.tx.status[9], AR_FinalTxIdx));
	printf("    PowerMgmt=%d, TxTid=%d\n",
	    MF(txs.u.tx.status[9], AR_PowerMgmt),
	    MS(txs.u.tx.status[9], AR_TxTid));

	printf("\n ------\n");
#endif
}