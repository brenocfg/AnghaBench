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
struct ar5416_desc {int ds_rxstatus8; int ds_rxstatus0; int ds_rxstatus2; int ds_link; int ds_data; int ds_ctl0; int ds_ctl1; int ds_rxstatus4; int ds_rxstatus1; int ds_rxstatus3; int ds_rxstatus5; int ds_rxstatus6; int ds_rxstatus7; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_2040 ; 
 int /*<<< orphan*/  AR_CRCErr ; 
 int AR_DataLen ; 
 int /*<<< orphan*/  AR_DecryptCRCErr ; 
 int /*<<< orphan*/  AR_DupFrame ; 
 int /*<<< orphan*/  AR_GI ; 
 int /*<<< orphan*/  AR_HiRxChain ; 
 int /*<<< orphan*/  AR_KeyIdx ; 
 int /*<<< orphan*/  AR_KeyMiss ; 
 int /*<<< orphan*/  AR_MichaelErr ; 
 int /*<<< orphan*/  AR_NumDelim ; 
 int /*<<< orphan*/  AR_PHYErr ; 
 int /*<<< orphan*/  AR_PHYErrCode ; 
 int /*<<< orphan*/  AR_PostDelimCRCErr ; 
 int /*<<< orphan*/  AR_PreDelimCRCErr ; 
 int /*<<< orphan*/  AR_RxAggr ; 
 int /*<<< orphan*/  AR_RxAntenna ; 
 int /*<<< orphan*/  AR_RxDone ; 
 int /*<<< orphan*/  AR_RxFrameOK ; 
 int /*<<< orphan*/  AR_RxKeyIdxValid ; 
 int /*<<< orphan*/  AR_RxMore ; 
 int /*<<< orphan*/  AR_RxMoreAggr ; 
 int /*<<< orphan*/  AR_RxRSSIAnt00 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt01 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt02 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt10 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt11 ; 
 int /*<<< orphan*/  AR_RxRSSIAnt12 ; 
 int /*<<< orphan*/  AR_RxRSSICombined ; 
 int /*<<< orphan*/  AR_RxRate ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5416_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5416_decode_rxstatus(struct if_ath_alq_payload *a)
{
	struct ar5416_desc rxs;

	/* XXX assumes rxs is smaller than PAYLOAD_LEN! */
	memcpy(&rxs, &a->payload, sizeof(struct ar5416_desc));

	printf("[%u.%06u] [%llu] RXSTATUS: RxDone=%d, RxRate=0x%02x, TS=0x%08x\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    MF(rxs.ds_rxstatus8, AR_RxDone),
	    MS(rxs.ds_rxstatus0, AR_RxRate),
	    rxs.ds_rxstatus2);

	printf("  link=0x%08x, data=0x%08x, ctl0=0x%08x, ctl2=0x%08x\n",
	    rxs.ds_link,
	    rxs.ds_data,
	    rxs.ds_ctl0,
	    rxs.ds_ctl1);

	/* status0 */
	/*
	 * XXX TODO: For AR9285, the chain 1 and chain 2 RSSI values
	 * acutally contain the RX mixer configuration
	 */
	printf("  RSSICtl[0]=%d, RSSICtl[1]=%d, RSSICtl[2]=%d\n",
	    MS(rxs.ds_rxstatus0, AR_RxRSSIAnt00),
	    MS(rxs.ds_rxstatus0, AR_RxRSSIAnt01),
	    MS(rxs.ds_rxstatus0, AR_RxRSSIAnt02));

	/* status4 */
	printf("  RSSIExt[0]=%d, RSSIExt[1]=%d, RSSIExt[2]=%d, RSSIComb=%d\n",
	    MS(rxs.ds_rxstatus4, AR_RxRSSIAnt10),
	    MS(rxs.ds_rxstatus4, AR_RxRSSIAnt11),
	    MS(rxs.ds_rxstatus4, AR_RxRSSIAnt12),
	    MS(rxs.ds_rxstatus4, AR_RxRSSICombined));

	/* status2 */
	printf("  RxTimestamp=0x%08x,", rxs.ds_rxstatus2);

	/* status1 */
	printf(" DataLen=%d, RxMore=%d, NumDelim=%d\n",
	    rxs.ds_rxstatus1 & AR_DataLen,
	    MF(rxs.ds_rxstatus1, AR_RxMore),
	    MS(rxs.ds_rxstatus1, AR_NumDelim));

	/* status3 - RxRate however is for Owl 2.0 */
	printf("  GI=%d, 2040=%d, RxRate=0x%02x, DupFrame=%d, RxAnt=0x%08x\n",
	    MF(rxs.ds_rxstatus3, AR_GI),
	    MF(rxs.ds_rxstatus3, AR_2040),
	    MS(rxs.ds_rxstatus0, AR_RxRate),
	    MF(rxs.ds_rxstatus3, AR_DupFrame),
	    MS(rxs.ds_rxstatus3, AR_RxAntenna));

	/* status5 */
	/* status6 */
	/* status7 */
	printf("  RxEvm0=0x%08x, RxEvm1=0x%08x, RxEvm2=0x%08x\n",
	    rxs.ds_rxstatus5,
	    rxs.ds_rxstatus6,
	    rxs.ds_rxstatus7);
	
	/* status8 */
	printf("  RxDone=%d, RxFrameOk=%d, CrcErr=%d, DecryptCrcErr=%d\n",
	    MF(rxs.ds_rxstatus8, AR_RxDone),
	    MF(rxs.ds_rxstatus8, AR_RxFrameOK),
	    MF(rxs.ds_rxstatus8, AR_CRCErr),
	    MF(rxs.ds_rxstatus8, AR_DecryptCRCErr));
	printf("  PhyErr=%d, MichaelErr=%d, PreDelimCRCErr=%d, KeyIdxValid=%d\n",
	    MF(rxs.ds_rxstatus8, AR_PHYErr),
	    MF(rxs.ds_rxstatus8, AR_MichaelErr),
	    MF(rxs.ds_rxstatus8, AR_PreDelimCRCErr),
	    MF(rxs.ds_rxstatus8, AR_RxKeyIdxValid));

	printf("  RxMoreAggr=%d, RxAggr=%d, PostDelimCRCErr=%d, HiRxChain=%d\n",
	    MF(rxs.ds_rxstatus8, AR_RxMoreAggr),
	    MF(rxs.ds_rxstatus8, AR_RxAggr),
	    MF(rxs.ds_rxstatus8, AR_PostDelimCRCErr),
	    MF(rxs.ds_rxstatus8, AR_HiRxChain));

	/* If PHY error, print that out. Otherwise, the key index */
	if (MF(rxs.ds_rxstatus8, AR_PHYErr))
		printf("  PhyErrCode=0x%02x",
		    MS(rxs.ds_rxstatus8, AR_PHYErrCode));
	else
		printf("  KeyIdx=0x%02x",
		    MS(rxs.ds_rxstatus8, AR_KeyIdx));
	printf(", KeyMiss=%d\n",
	    MF(rxs.ds_rxstatus8, AR_KeyMiss));

	printf("\n ------\n");
}