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
struct TYPE_2__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  len; int /*<<< orphan*/  op; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; } ;

/* Variables and functions */
#define  ATH_ALQ_EDMA_RXSTATUS 130 
#define  ATH_ALQ_EDMA_TXDESC 129 
#define  ATH_ALQ_EDMA_TXSTATUS 128 
 int /*<<< orphan*/  ar5212_decode_rxstatus (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ar5212_decode_txdesc (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ar5212_decode_txstatus (struct if_ath_alq_payload*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ,int,int) ; 

void
ar5212_alq_payload(struct if_ath_alq_payload *a)
{

		switch (be16toh(a->hdr.op)) {
			case ATH_ALQ_EDMA_TXSTATUS:	/* TXSTATUS */
				ar5212_decode_txstatus(a);
				break;
			case ATH_ALQ_EDMA_RXSTATUS:	/* RXSTATUS */
				ar5212_decode_rxstatus(a);
				break;
			case ATH_ALQ_EDMA_TXDESC:	/* TXDESC */
				ar5212_decode_txdesc(a);
				break;
			default:
				printf("[%d.%06d] [%lld] op: %d; len %d\n",
				    be32toh(a->hdr.tstamp_sec),
				    be32toh(a->hdr.tstamp_usec),
				    be64toh(a->hdr.threadid),
				    be16toh(a->hdr.op), be16toh(a->hdr.len));
		}
}