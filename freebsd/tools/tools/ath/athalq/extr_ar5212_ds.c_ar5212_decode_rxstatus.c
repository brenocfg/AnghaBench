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
struct ar5212_desc {int ds_rxstatus1; int ds_link; int ds_data; int ds_ctl0; int ds_ctl1; int ds_rxstatus0; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CRCErr ; 
 int AR_DataLen ; 
 int /*<<< orphan*/  AR_DecompCRCErr ; 
 int /*<<< orphan*/  AR_DecryptCRCErr ; 
 int /*<<< orphan*/  AR_Done ; 
 int /*<<< orphan*/  AR_FrmRcvOK ; 
 int /*<<< orphan*/  AR_KeyCacheMiss ; 
 int /*<<< orphan*/  AR_KeyIdx ; 
 int /*<<< orphan*/  AR_KeyIdxValid ; 
 int /*<<< orphan*/  AR_MichaelErr ; 
 int /*<<< orphan*/  AR_More ; 
 int /*<<< orphan*/  AR_PHYErr ; 
 int /*<<< orphan*/  AR_PHYErrCode ; 
 int /*<<< orphan*/  AR_RcvAntenna ; 
 int /*<<< orphan*/  AR_RcvRate ; 
 int /*<<< orphan*/  AR_RcvSigStrength ; 
 int /*<<< orphan*/  AR_RcvTimestamp ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5212_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5212_decode_rxstatus(struct if_ath_alq_payload *a)
{
	struct ar5212_desc rxs;

	/* XXX assumes rxs is smaller than PAYLOAD_LEN! */
	memcpy(&rxs, &a->payload, sizeof(struct ar5212_desc));

	printf("[%u.%06u] [%llu] RXSTATUS: RxOK=%d TS=0x%08x\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    MF(rxs.ds_rxstatus1, AR_Done),
	    MS(rxs.ds_rxstatus1, AR_RcvTimestamp));

	printf("  link=0x%08x, data=0x%08x, ctl0=0x%08x, ctl2=0x%08x\n",
	    rxs.ds_link,
	    rxs.ds_data,
	    rxs.ds_ctl0,
	    rxs.ds_ctl1);

	/* ds_rxstatus0 */
	printf("  DataLen=%d, ArMore=%d, DecompCrcError=%d, RcvRate=0x%02x\n",
	    rxs.ds_rxstatus0 & AR_DataLen,
	    MF(rxs.ds_rxstatus0, AR_More),
	    MF(rxs.ds_rxstatus0, AR_DecompCRCErr),
	    MS(rxs.ds_rxstatus0, AR_RcvRate));
	printf("  RSSI=%d, RcvAntenna=0x%x\n",
	    MS(rxs.ds_rxstatus0, AR_RcvSigStrength),
	    MS(rxs.ds_rxstatus0, AR_RcvAntenna));

	/* ds_rxstatus1 */
	printf("  RxDone=%d, RxFrameOk=%d, CrcErr=%d, DecryptCrcErr=%d\n",
	    MF(rxs.ds_rxstatus1, AR_Done),
	    MF(rxs.ds_rxstatus1, AR_FrmRcvOK),
	    MF(rxs.ds_rxstatus1, AR_CRCErr),
	    MF(rxs.ds_rxstatus1, AR_DecryptCRCErr));
	printf("  PhyErr=%d, MichaelErr=%d, KeyIdxValid=%d\n",
	    MF(rxs.ds_rxstatus1, AR_PHYErr),
	    MF(rxs.ds_rxstatus1, AR_MichaelErr),
	    MF(rxs.ds_rxstatus1, AR_KeyIdxValid));

	/* If PHY error, print that out. Otherwise, the key index */
	if (MF(rxs.ds_rxstatus1, AR_PHYErr))
		printf("  PhyErrCode=0x%02x\n",
		    MS(rxs.ds_rxstatus1, AR_PHYErrCode));
	else
		printf("  KeyIdx=0x%02x\n",
		    MS(rxs.ds_rxstatus1, AR_KeyIdx));

	printf("  KeyMiss=%d\n",
	    MF(rxs.ds_rxstatus1, AR_KeyCacheMiss));

	printf("  Timetamp: 0x%05x\n",
	    MS(rxs.ds_rxstatus1, AR_RcvTimestamp));

	printf("\n ------\n");
}