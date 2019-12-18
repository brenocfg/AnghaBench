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
struct TYPE_4__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;
struct TYPE_5__ {int /*<<< orphan*/  status1; int /*<<< orphan*/  status0; } ;
struct TYPE_6__ {TYPE_2__ tx; } ;
struct ar5212_desc {TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_AckSigStrength ; 
 int /*<<< orphan*/  AR_CompSuccess ; 
 int /*<<< orphan*/  AR_DataFailCnt ; 
 int /*<<< orphan*/  AR_Done ; 
 int /*<<< orphan*/  AR_ExcessiveRetries ; 
 int /*<<< orphan*/  AR_FIFOUnderrun ; 
 int /*<<< orphan*/  AR_Filtered ; 
 int /*<<< orphan*/  AR_FinalTSIndex ; 
 int /*<<< orphan*/  AR_FrmXmitOK ; 
 int /*<<< orphan*/  AR_RTSFailCnt ; 
 int /*<<< orphan*/  AR_SendTimestamp ; 
 int /*<<< orphan*/  AR_SeqNum ; 
 int /*<<< orphan*/  AR_VirtCollCnt ; 
 int /*<<< orphan*/  AR_XmitAtenna ; 
 int MF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5212_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5212_decode_txstatus(struct if_ath_alq_payload *a)
{
	struct ar5212_desc txs;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txs, &a->payload, sizeof(struct ar5212_desc));

	printf("[%u.%06u] [%llu] TXSTATUS: TxDone=%d, TS=0x%08x\n\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    MF(txs.u.tx.status1, AR_Done),
	    MS(txs.u.tx.status0, AR_SendTimestamp));

	/* ds_txstatus0 */
	printf("    Frmok=%d, xretries=%d, fifounderrun=%d, filt=%d\n",
	    MF(txs.u.tx.status0, AR_FrmXmitOK),
	    MF(txs.u.tx.status0, AR_ExcessiveRetries),
	    MF(txs.u.tx.status0, AR_FIFOUnderrun),
	    MF(txs.u.tx.status0, AR_Filtered));
	printf("    RTScnt=%d, FailCnt=%d, VCollCnt=%d\n",
	    MS(txs.u.tx.status0, AR_RTSFailCnt),
	    MS(txs.u.tx.status0, AR_DataFailCnt),
	    MS(txs.u.tx.status0, AR_VirtCollCnt));
	printf("    SndTimestamp=0x%04x\n",
	    MS(txs.u.tx.status0, AR_SendTimestamp));

	/* ds_txstatus1 */
	printf("    Done=%d, SeqNum=0x%04x, AckRSSI=%d, FinalTSI=%d\n",
	    MF(txs.u.tx.status1, AR_Done),
	    MS(txs.u.tx.status1, AR_SeqNum),
	    MS(txs.u.tx.status1, AR_AckSigStrength),
	    MS(txs.u.tx.status1, AR_FinalTSIndex));
	printf("    CompSuccess=%d, XmitAntenna=%d\n",
	    MF(txs.u.tx.status1, AR_CompSuccess),
	    MF(txs.u.tx.status1, AR_XmitAtenna));

	printf("\n ------\n");
}