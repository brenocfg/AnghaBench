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
struct ar5416_desc {int ds_link; int ds_data; int ds_ctl0; int ds_ctl1; int ds_ctl2; int ds_ctl3; int ds_ctl4; int ds_ctl5; int ds_ctl6; int ds_ctl7; int ds_ctl8; int ds_ctl9; int ds_ctl10; int ds_ctl11; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_2040_0 ; 
 int /*<<< orphan*/  AR_2040_1 ; 
 int /*<<< orphan*/  AR_2040_2 ; 
 int /*<<< orphan*/  AR_2040_3 ; 
 int /*<<< orphan*/  AR_AggrLen ; 
 int AR_AntCtl0 ; 
 int AR_AntCtl1 ; 
 int AR_AntCtl2 ; 
 int AR_AntCtl3 ; 
 int AR_BufLen ; 
 int /*<<< orphan*/  AR_BurstDur ; 
 int /*<<< orphan*/  AR_CTSEnable ; 
 int /*<<< orphan*/  AR_ChainSel0 ; 
 int /*<<< orphan*/  AR_ChainSel1 ; 
 int /*<<< orphan*/  AR_ChainSel2 ; 
 int /*<<< orphan*/  AR_ChainSel3 ; 
 int /*<<< orphan*/  AR_ClrDestMask ; 
 int /*<<< orphan*/  AR_CorruptFCS ; 
 int /*<<< orphan*/  AR_DestIdx ; 
 int /*<<< orphan*/  AR_DestIdxValid ; 
 int /*<<< orphan*/  AR_DurUpdateEn ; 
 int /*<<< orphan*/  AR_EncrType ; 
 int /*<<< orphan*/  AR_ExtAndCtl ; 
 int /*<<< orphan*/  AR_ExtOnly ; 
 int AR_FrameLen ; 
 int /*<<< orphan*/  AR_FrameType ; 
 int /*<<< orphan*/  AR_GI0 ; 
 int /*<<< orphan*/  AR_GI1 ; 
 int /*<<< orphan*/  AR_GI2 ; 
 int /*<<< orphan*/  AR_GI3 ; 
 int /*<<< orphan*/  AR_InsertTS ; 
 int /*<<< orphan*/  AR_IsAggr ; 
 int /*<<< orphan*/  AR_MoreAggr ; 
 int /*<<< orphan*/  AR_MoreRifs ; 
 int /*<<< orphan*/  AR_NoAck ; 
 int /*<<< orphan*/  AR_PacketDur0 ; 
 int /*<<< orphan*/  AR_PacketDur1 ; 
 int /*<<< orphan*/  AR_PacketDur2 ; 
 int /*<<< orphan*/  AR_PacketDur3 ; 
 int /*<<< orphan*/  AR_PadDelim ; 
 int /*<<< orphan*/  AR_RTSCTSQual0 ; 
 int /*<<< orphan*/  AR_RTSCTSQual1 ; 
 int /*<<< orphan*/  AR_RTSCTSQual2 ; 
 int /*<<< orphan*/  AR_RTSCTSQual3 ; 
 int /*<<< orphan*/  AR_RTSCTSRate ; 
 int /*<<< orphan*/  AR_RTSEnable ; 
 int /*<<< orphan*/  AR_STBC0 ; 
 int /*<<< orphan*/  AR_STBC1 ; 
 int /*<<< orphan*/  AR_STBC2 ; 
 int /*<<< orphan*/  AR_STBC3 ; 
 int /*<<< orphan*/  AR_TxIntrReq ; 
 int /*<<< orphan*/  AR_TxMore ; 
 int /*<<< orphan*/  AR_VEOL ; 
 int /*<<< orphan*/  AR_VirtMoreFrag ; 
 int /*<<< orphan*/  AR_XmitDataTries0 ; 
 int /*<<< orphan*/  AR_XmitDataTries1 ; 
 int /*<<< orphan*/  AR_XmitDataTries2 ; 
 int /*<<< orphan*/  AR_XmitDataTries3 ; 
 int /*<<< orphan*/  AR_XmitPower ; 
 int /*<<< orphan*/  AR_XmitPower1 ; 
 int /*<<< orphan*/  AR_XmitPower2 ; 
 int /*<<< orphan*/  AR_XmitPower3 ; 
 int /*<<< orphan*/  AR_XmitRate0 ; 
 int /*<<< orphan*/  AR_XmitRate1 ; 
 int /*<<< orphan*/  AR_XmitRate2 ; 
 int /*<<< orphan*/  AR_XmitRate3 ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5416_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5416_decode_txdesc(struct if_ath_alq_payload *a)
{
	struct ar5416_desc txc;

	/* XXX assumes txs is smaller than PAYLOAD_LEN! */
	memcpy(&txc, &a->payload, sizeof(struct ar5416_desc));

	printf("[%u.%06u] [%llu] TXD\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid));

	printf("  link=0x%08x, data=0x%08x\n",
	    txc.ds_link,
	    txc.ds_data);

	/* ds_ctl0 */
	printf("    Frame Len=%d, VMF=%d\n",
	     txc.ds_ctl0 & AR_FrameLen,
	    MF(txc.ds_ctl0, AR_VirtMoreFrag));
	printf("    TX power0=%d, RtsEna=%d, Veol=%d, ClrDstMask=%d\n",
	    MS(txc.ds_ctl0, AR_XmitPower),
	    MF(txc.ds_ctl0, AR_RTSEnable),
	    MF(txc.ds_ctl0, AR_VEOL),
	    MF(txc.ds_ctl0, AR_ClrDestMask));
	printf("    TxIntrReq=%d, DestIdxValid=%d, CtsEnable=%d\n",
	    MF(txc.ds_ctl0, AR_TxIntrReq),
	    MF(txc.ds_ctl0, AR_DestIdxValid),
	    MF(txc.ds_ctl0, AR_CTSEnable));

	/* ds_ctl1 */
	printf("    BufLen=%d, TxMore=%d, DestIdx=%d,"
	    " FrType=0x%x\n",
	    txc.ds_ctl1 & AR_BufLen,
	    MF(txc.ds_ctl1, AR_TxMore),
	    MS(txc.ds_ctl1, AR_DestIdx),
	    MS(txc.ds_ctl1, AR_FrameType));
	printf("    NoAck=%d, InsertTs=%d, CorruptFcs=%d, ExtOnly=%d,"
	    " ExtAndCtl=%d\n",
	    MF(txc.ds_ctl1, AR_NoAck),
	    MF(txc.ds_ctl1, AR_InsertTS),
	    MF(txc.ds_ctl1, AR_CorruptFCS),
	    MF(txc.ds_ctl1, AR_ExtOnly),
	    MF(txc.ds_ctl1, AR_ExtAndCtl));
	printf("    MoreAggr=%d, IsAggr=%d, MoreRifs=%d\n",
	    MF(txc.ds_ctl1, AR_MoreAggr),
	    MF(txc.ds_ctl1, AR_IsAggr),
	    MF(txc.ds_ctl1, AR_MoreRifs));

	/* ds_ctl2 */
	printf("    DurUpEna=%d, Burstdur=0x%04x\n",
	    MF(txc.ds_ctl2, AR_DurUpdateEn),
	    MS(txc.ds_ctl2, AR_BurstDur));
	printf("    Try0=%d, Try1=%d, Try2=%d, Try3=%d\n",
	    MS(txc.ds_ctl2, AR_XmitDataTries0),
	    MS(txc.ds_ctl2, AR_XmitDataTries1),
	    MS(txc.ds_ctl2, AR_XmitDataTries2),
	    MS(txc.ds_ctl2, AR_XmitDataTries3));

	/* ds_ctl3, 4 */
	printf("    try 0: Rate=0x%02x, PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl3, AR_XmitRate0),
	    MS(txc.ds_ctl4, AR_PacketDur0),
	    MF(txc.ds_ctl4, AR_RTSCTSQual0));
	printf("    try 1: Rate=0x%02x, PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl3, AR_XmitRate1),
	    MS(txc.ds_ctl4, AR_PacketDur1),
	    MF(txc.ds_ctl4, AR_RTSCTSQual1));

	/* ds_ctl3, 5 */
	printf("    try 2: Rate=0x%02x, PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl3, AR_XmitRate2),
	    MS(txc.ds_ctl5, AR_PacketDur2),
	    MF(txc.ds_ctl5, AR_RTSCTSQual2));
	printf("    try 3: Rate=0x%02x, PktDur=%d, RTS/CTS ena=%d\n",
	    MS(txc.ds_ctl3, AR_XmitRate3),
	    MS(txc.ds_ctl5, AR_PacketDur3),
	    MF(txc.ds_ctl5, AR_RTSCTSQual3));

	/* ds_ctl6 */
	printf("    AggrLen=%d, PadDelim=%d, EncrType=%d\n",
	    MS(txc.ds_ctl6, AR_AggrLen),
	    MS(txc.ds_ctl6, AR_PadDelim),
	    MS(txc.ds_ctl6, AR_EncrType));

	/* ds_ctl7 */
	printf("    try 0: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl7, AR_ChainSel0),
	    MF(txc.ds_ctl7, AR_GI0),
	    MF(txc.ds_ctl7, AR_2040_0),
	    MF(txc.ds_ctl7, AR_STBC0));
	printf("    try 1: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl7, AR_ChainSel1),
	    MF(txc.ds_ctl7, AR_GI1),
	    MF(txc.ds_ctl7, AR_2040_1),
	    MF(txc.ds_ctl7, AR_STBC1));
	printf("    try 2: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl7, AR_ChainSel2),
	    MF(txc.ds_ctl7, AR_GI2),
	    MF(txc.ds_ctl7, AR_2040_2),
	    MF(txc.ds_ctl7, AR_STBC2));
	printf("    try 3: chainMask=0x%x, GI=%d, 2040=%d, STBC=%d\n",
	    MS(txc.ds_ctl7, AR_ChainSel3),
	    MF(txc.ds_ctl7, AR_GI3),
	    MF(txc.ds_ctl7, AR_2040_3),
	    MF(txc.ds_ctl7, AR_STBC3));

	printf("    RTSCtsRate=0x%02x\n", MS(txc.ds_ctl7, AR_RTSCTSRate));

	/* ds_ctl8 */
	printf("    try 0: ant=0x%08x\n", txc.ds_ctl8 &  AR_AntCtl0);

	/* ds_ctl9 */
	printf("    try 1: TxPower=%d, ant=0x%08x\n",
	    MS(txc.ds_ctl9, AR_XmitPower1),
	    txc.ds_ctl9 & AR_AntCtl1);

	/* ds_ctl10 */
	printf("    try 2: TxPower=%d, ant=0x%08x\n",
	    MS(txc.ds_ctl10, AR_XmitPower2),
	    txc.ds_ctl10 & AR_AntCtl2);

	/* ds_ctl11 */
	printf("    try 3: TxPower=%d, ant=0x%08x\n",
	    MS(txc.ds_ctl11, AR_XmitPower3),
	    txc.ds_ctl11 & AR_AntCtl3);

	printf("\n ------ \n");
}