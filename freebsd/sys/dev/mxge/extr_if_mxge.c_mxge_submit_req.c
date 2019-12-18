#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int req; int mask; TYPE_2__* lanai; } ;
typedef  TYPE_1__ mxge_tx_ring_t ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ mcp_kreq_ether_send_t ;

/* Variables and functions */
 int /*<<< orphan*/  mxge_pio_copy (TYPE_2__ volatile*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  mxge_submit_req_backwards (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void
mxge_submit_req(mxge_tx_ring_t *tx, mcp_kreq_ether_send_t *src,
		  int cnt)
{
	int idx, i;
	uint32_t *src_ints;
	volatile uint32_t *dst_ints;
	mcp_kreq_ether_send_t *srcp;
	volatile mcp_kreq_ether_send_t *dstp, *dst;
	uint8_t last_flags;
	
	idx = tx->req & tx->mask;

	last_flags = src->flags;
	src->flags = 0;
	wmb();
	dst = dstp = &tx->lanai[idx];
	srcp = src;

	if ((idx + cnt) < tx->mask) {
		for (i = 0; i < (cnt - 1); i += 2) {
			mxge_pio_copy(dstp, srcp, 2 * sizeof(*src));
			wmb(); /* force write every 32 bytes */
			srcp += 2;
			dstp += 2;
		}
	} else {
		/* submit all but the first request, and ensure
		   that it is submitted below */
		mxge_submit_req_backwards(tx, src, cnt);
		i = 0;
	}
	if (i < cnt) {
		/* submit the first request */
		mxge_pio_copy(dstp, srcp, sizeof(*src));
		wmb(); /* barrier before setting valid flag */
	}

	/* re-write the last 32-bits with the valid flags */
	src->flags = last_flags;
	src_ints = (uint32_t *)src;
	src_ints+=3;
	dst_ints = (volatile uint32_t *)dst;
	dst_ints+=3;
	*dst_ints =  *src_ints;
	tx->req += cnt;
	wmb();
}