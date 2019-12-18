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
struct TYPE_2__ {int /*<<< orphan*/  tstamp; int /*<<< orphan*/  len; int /*<<< orphan*/  op; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; } ;

/* Variables and functions */
#define  ATH_ALQ_EDMA_RXSTATUS 135 
#define  ATH_ALQ_EDMA_TXDESC 134 
#define  ATH_ALQ_EDMA_TXSTATUS 133 
#define  ATH_ALQ_TDMA_BEACON_STATE 132 
#define  ATH_ALQ_TDMA_SLOT_CALC 131 
#define  ATH_ALQ_TDMA_TIMER_CONFIG 130 
#define  ATH_ALQ_TDMA_TIMER_SET 129 
#define  ATH_ALQ_TDMA_TSF_ADJUST 128 
 int /*<<< orphan*/  ar5416_decode_rxstatus (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ar5416_decode_txdesc (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ar5416_decode_txstatus (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ath_tdma_beacon_state (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ath_tdma_slot_calc (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ath_tdma_timer_config (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ath_tdma_timer_set (struct if_ath_alq_payload*) ; 
 int /*<<< orphan*/  ath_tdma_tsf_adjust (struct if_ath_alq_payload*) ; 
 int be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int,int) ; 

void
ar5416_alq_payload(struct if_ath_alq_payload *a)
{

		switch (be16toh(a->hdr.op)) {
			case ATH_ALQ_EDMA_TXSTATUS:	/* TXSTATUS */
				ar5416_decode_txstatus(a);
				break;
			case ATH_ALQ_EDMA_RXSTATUS:	/* RXSTATUS */
				ar5416_decode_rxstatus(a);
				break;
			case ATH_ALQ_EDMA_TXDESC:	/* TXDESC */
				ar5416_decode_txdesc(a);
				break;
			case ATH_ALQ_TDMA_BEACON_STATE:
				ath_tdma_beacon_state(a);
				break;
			case ATH_ALQ_TDMA_TIMER_CONFIG:
				ath_tdma_timer_config(a);
				break;
			case ATH_ALQ_TDMA_SLOT_CALC:
				ath_tdma_slot_calc(a);
				break;
			case ATH_ALQ_TDMA_TSF_ADJUST:
				ath_tdma_tsf_adjust(a);
				break;
			case ATH_ALQ_TDMA_TIMER_SET:
				ath_tdma_timer_set(a);
				break;
			default:
				printf("[%d] [%lld] op: %d; len %d\n",
				    be32toh(a->hdr.tstamp),
				    be64toh(a->hdr.threadid),
				    be16toh(a->hdr.op), be16toh(a->hdr.len));
		}
}