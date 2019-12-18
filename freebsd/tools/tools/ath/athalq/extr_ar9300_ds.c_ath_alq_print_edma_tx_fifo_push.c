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
struct if_ath_alq_tx_fifo_push {int /*<<< orphan*/  frame_cnt; int /*<<< orphan*/  fifo_depth; int /*<<< orphan*/  nframes; int /*<<< orphan*/  txq; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstamp_usec; int /*<<< orphan*/  tstamp_sec; int /*<<< orphan*/  threadid; } ;
struct if_ath_alq_payload {TYPE_1__ hdr; int /*<<< orphan*/  payload; } ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 scalar_t__ be32toh (int /*<<< orphan*/ ) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct if_ath_alq_tx_fifo_push*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int,unsigned long long,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void
ath_alq_print_edma_tx_fifo_push(struct if_ath_alq_payload *a)
{
	struct if_ath_alq_tx_fifo_push p;

	memcpy(&p, &a->payload, sizeof(p));
	printf("[%u.%06u] [%llu] TXPUSH txq=%d, nframes=%d, fifodepth=%d, frmcount=%d\n",
	    (unsigned int) be32toh(a->hdr.tstamp_sec),
	    (unsigned int) be32toh(a->hdr.tstamp_usec),
	    (unsigned long long) be64toh(a->hdr.threadid),
	    be32toh(p.txq),
	    be32toh(p.nframes),
	    be32toh(p.fifo_depth),
	    be32toh(p.frame_cnt));
}