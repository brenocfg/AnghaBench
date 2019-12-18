#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sge_fl {size_t pidx; int gen; size_t size; int /*<<< orphan*/  cntxt_id; int /*<<< orphan*/  credits; int /*<<< orphan*/ * sdesc; struct rx_desc* desc; } ;
struct rx_desc {void* gen2; void* len_gen; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_SG_KDOORBELL ; 
 int /*<<< orphan*/  V_EGRCNTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V_FLD_GEN1 (int) ; 
 int /*<<< orphan*/  V_FLD_GEN2 (int) ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_write_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
recycle_rx_buf(adapter_t *adap, struct sge_fl *q, unsigned int idx)
{
	struct rx_desc *from = &q->desc[idx];
	struct rx_desc *to   = &q->desc[q->pidx];

	q->sdesc[q->pidx] = q->sdesc[idx];
	to->addr_lo = from->addr_lo;        // already big endian
	to->addr_hi = from->addr_hi;        // likewise
	wmb();	/* necessary ? */
	to->len_gen = htobe32(V_FLD_GEN1(q->gen));
	to->gen2 = htobe32(V_FLD_GEN2(q->gen));
	q->credits++;

	if (++q->pidx == q->size) {
		q->pidx = 0;
		q->gen ^= 1;
	}
	t3_write_reg(adap, A_SG_KDOORBELL, V_EGRCNTX(q->cntxt_id));
}