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
struct ar5210_desc {int ds_status0; int ds_status1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_AckSigStrength ; 
 int /*<<< orphan*/  AR_Done ; 
 int /*<<< orphan*/  AR_ExcessiveRetries ; 
 int /*<<< orphan*/  AR_FIFOUnderrun ; 
 int /*<<< orphan*/  AR_Filtered ; 
 int /*<<< orphan*/  AR_FrmXmitOK ; 
 int /*<<< orphan*/  AR_LongRetryCnt ; 
 int /*<<< orphan*/  AR_SendTimestamp ; 
 int AR_SeqNum ; 
 int /*<<< orphan*/  AR_ShortRetryCnt ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5210_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5210_decode_txstatus(struct if_ath_alq_payload *a)
{
	struct ar5210_desc txs;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txs, &a->payload, sizeof(struct ar5210_desc));

	printf("[%u.%06u] [%llu] TXSTATUS\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid));

	/* ds_txstatus0 */
	printf("    Frmok=%d, xretries=%d, fifounderrun=%d, filt=%d\n",
	    MF(txs.ds_status0, AR_FrmXmitOK),
	    MF(txs.ds_status0, AR_ExcessiveRetries),
	    MF(txs.ds_status0, AR_FIFOUnderrun),
	    MF(txs.ds_status0, AR_Filtered));
	printf("    LongRetryCnt=%d, ShortRetryCnt=%d\n",
	    MS(txs.ds_status0, AR_LongRetryCnt),
	    MS(txs.ds_status0, AR_ShortRetryCnt));
	printf("    SndTimestamp=0x%04x\n",
	    MS(txs.ds_status0, AR_SendTimestamp));

	/* ds_txstatus1 */
	printf("    Done=%d, SeqNum=0x%04x, AckRSSI=%d\n",
	    MF(txs.ds_status1, AR_Done),
	    txs.ds_status1 & AR_SeqNum,
	    MS(txs.ds_status1, AR_AckSigStrength));

	printf("\n ------\n");
}