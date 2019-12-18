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
struct ar5210_desc {int ds_link; int ds_data; int ds_status0; int ds_status1; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_CRCErr ; 
 int AR_DataLen ; 
 int /*<<< orphan*/  AR_DecryptCRCErr ; 
 int /*<<< orphan*/  AR_Done ; 
 int /*<<< orphan*/  AR_FrmRcvOK ; 
 int /*<<< orphan*/  AR_KeyCacheMiss ; 
 int /*<<< orphan*/  AR_KeyIdxValid ; 
 int /*<<< orphan*/  AR_More ; 
 int /*<<< orphan*/  AR_PHYErr ; 
 int /*<<< orphan*/  AR_RcvAntenna ; 
 int /*<<< orphan*/  AR_RcvSigStrength ; 
 int /*<<< orphan*/  AR_RcvTimestamp ; 
 int MF (int,int /*<<< orphan*/ ) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct ar5210_desc*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
ar5210_decode_rxstatus(struct if_ath_alq_payload *a)
{
	struct ar5210_desc rxs;

	/* XXX assumes rxs is smaller than PAYLOAD_LEN! */
	memcpy(&rxs, &a->payload, sizeof(struct ar5210_desc));

	printf("[%u.%06u] [%llu] RXSTATUS\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid));

	printf("  link=0x%08x, data=0x%08x\n",
	    rxs.ds_link,
	    rxs.ds_data);

	/* ds_rxstatus0 */
	printf("  DataLen=%d, ArMore=%d, RSSI=%d, RcvAntenna=0x%x\n",
	    rxs.ds_status0 & AR_DataLen,
	    MF(rxs.ds_status0, AR_More),
	    MS(rxs.ds_status0, AR_RcvSigStrength),
	    MF(rxs.ds_status0, AR_RcvAntenna));

	/* ds_rxstatus1 */
	printf("  RxDone=%d, RxFrameOk=%d, CrcErr=%d, DecryptCrcErr=%d\n",
	    MF(rxs.ds_status1, AR_Done),
	    MF(rxs.ds_status1, AR_FrmRcvOK),
	    MF(rxs.ds_status1, AR_CRCErr),
	    MF(rxs.ds_status1, AR_DecryptCRCErr));
	printf("  KeyIdxValid=%d\n",
	    MF(rxs.ds_status1, AR_KeyIdxValid));

	printf("  PhyErrCode=0x%02x\n",
	    MS(rxs.ds_status1, AR_PHYErr));

	printf("  KeyMiss=%d\n",
	    MF(rxs.ds_status1, AR_KeyCacheMiss));

	printf("  Timetamp: 0x%05x\n",
	    MS(rxs.ds_status1, AR_RcvTimestamp));

	printf("\n ------\n");
}