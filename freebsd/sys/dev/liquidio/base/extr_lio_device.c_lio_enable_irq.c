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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
struct octeon_device {int dummy; } ;
struct lio_instr_queue {int /*<<< orphan*/  inst_cnt_reg; int /*<<< orphan*/  lock; scalar_t__ pkt_in_done; struct octeon_device* oct_dev; } ;
struct lio_droq {int /*<<< orphan*/  pkts_sent_reg; int /*<<< orphan*/  lock; scalar_t__ pkt_count; int /*<<< orphan*/  pkts_pending; struct octeon_device* oct_dev; } ;

/* Variables and functions */
 int LIO_CN23XX_INTR_RESEND ; 
 scalar_t__ LIO_CN23XX_PF (struct octeon_device*) ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 scalar_t__ atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int lio_read_csr64 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_write_csr32 (struct octeon_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lio_write_csr64 (struct octeon_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
lio_enable_irq(struct lio_droq *droq, struct lio_instr_queue *iq)
{
	struct octeon_device *oct = NULL;
	uint64_t	instr_cnt;
	uint32_t	pkts_pend;

	/* the whole thing needs to be atomic, ideally */
	if (droq != NULL) {
		oct = droq->oct_dev;
		pkts_pend = atomic_load_acq_int(&droq->pkts_pending);
		mtx_lock(&droq->lock);
		lio_write_csr32(oct, droq->pkts_sent_reg,
				droq->pkt_count - pkts_pend);
		droq->pkt_count = pkts_pend;
		/* this write needs to be flushed before we release the lock */
		__compiler_membar();
		mtx_unlock(&droq->lock);
	}

	if (iq != NULL) {
		oct = iq->oct_dev;
		mtx_lock(&iq->lock);
		lio_write_csr32(oct, iq->inst_cnt_reg, iq->pkt_in_done);
		iq->pkt_in_done = 0;
		/* this write needs to be flushed before we release the lock */
		__compiler_membar();
		mtx_unlock(&iq->lock);
	}

	/*
	 * Implementation note:
	 *
	 * SLI_PKT(x)_CNTS[RESEND] is written separately so that if an interrupt
	 * DOES occur as a result of RESEND, the DROQ lock will NOT be held.
	 *
	 * Write resend. Writing RESEND in SLI_PKTX_CNTS should be enough
	 * to trigger tx interrupts as well, if they are pending.
	 */
	if ((oct != NULL) && (LIO_CN23XX_PF(oct))) {
		if (droq != NULL)
			lio_write_csr64(oct, droq->pkts_sent_reg,
					LIO_CN23XX_INTR_RESEND);
		/* we race with firmrware here. */
		/* read and write the IN_DONE_CNTS */
		else if (iq != NULL) {
			instr_cnt = lio_read_csr64(oct, iq->inst_cnt_reg);
			lio_write_csr64(oct, iq->inst_cnt_reg,
					((instr_cnt & 0xFFFFFFFF00000000ULL) |
					 LIO_CN23XX_INTR_RESEND));
		}
	}
}