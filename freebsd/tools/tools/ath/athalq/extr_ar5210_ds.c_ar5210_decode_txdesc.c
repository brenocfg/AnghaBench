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
struct ar5210_desc {int ds_link; int ds_data; int ds_ctl0; int ds_ctl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_AntModeXmit ; 
 int AR_BufLen ; 
 int /*<<< orphan*/  AR_ClearDestMask ; 
 int /*<<< orphan*/  AR_EncryptKeyIdx ; 
 int AR_FrameLen ; 
 int /*<<< orphan*/  AR_FrmType ; 
 int /*<<< orphan*/  AR_LongPkt ; 
 int /*<<< orphan*/  AR_More ; 
 int /*<<< orphan*/  AR_RTSCTSEnable ; 
 int /*<<< orphan*/  AR_RTSDuration ; 
 int /*<<< orphan*/  AR_TxInterReq ; 
 int /*<<< orphan*/  AR_XmitRate ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5210_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5210_decode_txdesc(struct if_ath_alq_payload *a)
{
	struct ar5210_desc txc;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txc, &a->payload, sizeof(struct ar5210_desc));

	printf("[%u.%06u] [%llu] TXD\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid));

	printf("  link=0x%08x, data=0x%08x\n",
	    txc.ds_link,
	    txc.ds_data);

	/* ds_ctl0 */
	printf("    Frame Len=%d\n", txc.ds_ctl0 & AR_FrameLen);
	printf("    TX Rate=0x%02x, RtsEna=%d, ClrDstMask=%d AntModeXmit=0x%02x\n",
	    MS(txc.ds_ctl0, AR_XmitRate),
	    MF(txc.ds_ctl0, AR_RTSCTSEnable),
	    MF(txc.ds_ctl0, AR_ClearDestMask),
	    MF(txc.ds_ctl0, AR_AntModeXmit));
	printf("    FrmType=0x%02x, TxIntrReq=%d\n",
	    MS(txc.ds_ctl0, AR_FrmType),
	    MF(txc.ds_ctl0, AR_TxInterReq));
	printf("    LongPkt=%d\n", MF(txc.ds_ctl0, AR_LongPkt));

	/* ds_ctl1 */
	printf("    BufLen=%d, TxMore=%d, EncryptKeyIdx=%d, RtsDuration=%d\n",
	    txc.ds_ctl1 & AR_BufLen,
	    MF(txc.ds_ctl1, AR_More),
	    MS(txc.ds_ctl1, AR_EncryptKeyIdx),
	    MS(txc.ds_ctl1, AR_RTSDuration));

	printf("\n ------ \n");
}