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
struct ar5212_desc {int ds_link; int ds_data; int ds_ctl0; int ds_ctl1; int ds_ctl2; int ds_ctl3; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_AntModeXmit ; 
 int AR_BufLen ; 
 int /*<<< orphan*/  AR_CTSEnable ; 
 int /*<<< orphan*/  AR_ClearDestMask ; 
 int /*<<< orphan*/  AR_CompICVLen ; 
 int /*<<< orphan*/  AR_CompIVLen ; 
 int /*<<< orphan*/  AR_CompProc ; 
 int /*<<< orphan*/  AR_DestIdx ; 
 int /*<<< orphan*/  AR_DestIdxValid ; 
 int /*<<< orphan*/  AR_DurUpdateEna ; 
 int AR_FrameLen ; 
 int /*<<< orphan*/  AR_FrmType ; 
 int /*<<< orphan*/  AR_More ; 
 int /*<<< orphan*/  AR_NoAck ; 
 int /*<<< orphan*/  AR_RTSCTSDuration ; 
 int /*<<< orphan*/  AR_RTSCTSEnable ; 
 int /*<<< orphan*/  AR_RTSCTSRate ; 
 int /*<<< orphan*/  AR_TxInterReq ; 
 int /*<<< orphan*/  AR_VEOL ; 
 int /*<<< orphan*/  AR_XmitDataTries0 ; 
 int /*<<< orphan*/  AR_XmitDataTries1 ; 
 int /*<<< orphan*/  AR_XmitDataTries2 ; 
 int /*<<< orphan*/  AR_XmitDataTries3 ; 
 int /*<<< orphan*/  AR_XmitPower ; 
 int /*<<< orphan*/  AR_XmitRate0 ; 
 int /*<<< orphan*/  AR_XmitRate1 ; 
 int /*<<< orphan*/  AR_XmitRate2 ; 
 int /*<<< orphan*/  AR_XmitRate3 ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5212_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5212_decode_txdesc(struct if_ath_alq_payload *a)
{
	struct ar5212_desc txc;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txc, &a->payload, sizeof(struct ar5212_desc));

	printf("[%u.%06u] [%llu] TXD\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid));

	printf("  link=0x%08x, data=0x%08x\n",
	    txc.ds_link,
	    txc.ds_data);

	/* ds_ctl0 */
	printf("    Frame Len=%d\n", txc.ds_ctl0 & AR_FrameLen);
	printf("    TX power0=%d, RtsEna=%d, Veol=%d, ClrDstMask=%d AntModeXmit=0x%02x\n",
	    MS(txc.ds_ctl0, AR_XmitPower),
	    MF(txc.ds_ctl0, AR_RTSCTSEnable),
	    MF(txc.ds_ctl0, AR_VEOL),
	    MF(txc.ds_ctl0, AR_ClearDestMask),
	    MF(txc.ds_ctl0, AR_AntModeXmit));
	printf("    TxIntrReq=%d, DestIdxValid=%d, CtsEnable=%d\n",
	    MF(txc.ds_ctl0, AR_TxInterReq),
	    MF(txc.ds_ctl0, AR_DestIdxValid),
	    MF(txc.ds_ctl0, AR_CTSEnable));

	/* ds_ctl1 */
	printf("    BufLen=%d, TxMore=%d, DestIdx=%d,"
	    " FrType=0x%x\n",
	    txc.ds_ctl1 & AR_BufLen,
	    MF(txc.ds_ctl1, AR_More),
	    MS(txc.ds_ctl1, AR_DestIdx),
	    MS(txc.ds_ctl1, AR_FrmType));
	printf("    NoAck=%d, CompProc=%d, CompIVLen=%d, CompICVLen=%d\n",
	    MF(txc.ds_ctl1, AR_NoAck),
	    MS(txc.ds_ctl1, AR_CompProc),
	    MS(txc.ds_ctl1, AR_CompIVLen),
	    MS(txc.ds_ctl1, AR_CompICVLen));

	/* ds_ctl2 */
	printf("    DurUpEna=%d, Burstdur=0x%04x\n",
	    MF(txc.ds_ctl2, AR_DurUpdateEna),
	    MS(txc.ds_ctl2, AR_RTSCTSDuration));
	printf("    Try0=%d, Try1=%d, Try2=%d, Try3=%d\n",
	    MS(txc.ds_ctl2, AR_XmitDataTries0),
	    MS(txc.ds_ctl2, AR_XmitDataTries1),
	    MS(txc.ds_ctl2, AR_XmitDataTries2),
	    MS(txc.ds_ctl2, AR_XmitDataTries3));

	/* ds_ctl3 */
	printf("    rate0=0x%02x, rate1=0x%02x, rate2=0x%02x, rate3=0x%02x\n",
	    MS(txc.ds_ctl3, AR_XmitRate0),
	    MS(txc.ds_ctl3, AR_XmitRate1),
	    MS(txc.ds_ctl3, AR_XmitRate2),
	    MS(txc.ds_ctl3, AR_XmitRate3));
	printf("    RtsCtsRate=0x%02x\n",
	    MS(txc.ds_ctl3, AR_RTSCTSRate));

	printf("\n ------ \n");
}