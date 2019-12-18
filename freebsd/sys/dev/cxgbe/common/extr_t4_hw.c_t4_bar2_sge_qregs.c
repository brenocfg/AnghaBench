#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u64 ;
struct TYPE_3__ {unsigned int page_shift; unsigned int eq_s_qpp; unsigned int iq_s_qpp; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;
typedef  enum t4_bar2_qtype { ____Placeholder_t4_bar2_qtype } t4_bar2_qtype ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SGE_UDB_SIZE ; 
 int T4_BAR2_QTYPE_EGRESS ; 
 scalar_t__ is_t4 (struct adapter*) ; 

int t4_bar2_sge_qregs(struct adapter *adapter,
		      unsigned int qid,
		      enum t4_bar2_qtype qtype,
		      int user,
		      u64 *pbar2_qoffset,
		      unsigned int *pbar2_qid)
{
	unsigned int page_shift, page_size, qpp_shift, qpp_mask;
	u64 bar2_page_offset, bar2_qoffset;
	unsigned int bar2_qid, bar2_qid_offset, bar2_qinferred;

	/* T4 doesn't support BAR2 SGE Queue registers for kernel
	 * mode queues.
	 */
	if (!user && is_t4(adapter))
		return -EINVAL;

	/* Get our SGE Page Size parameters.
	 */
	page_shift = adapter->params.sge.page_shift;
	page_size = 1 << page_shift;

	/* Get the right Queues per Page parameters for our Queue.
	 */
	qpp_shift = (qtype == T4_BAR2_QTYPE_EGRESS
		     ? adapter->params.sge.eq_s_qpp
		     : adapter->params.sge.iq_s_qpp);
	qpp_mask = (1 << qpp_shift) - 1;

	/* Calculate the basics of the BAR2 SGE Queue register area:
	 *  o The BAR2 page the Queue registers will be in.
	 *  o The BAR2 Queue ID.
	 *  o The BAR2 Queue ID Offset into the BAR2 page.
	 */
	bar2_page_offset = ((u64)(qid >> qpp_shift) << page_shift);
	bar2_qid = qid & qpp_mask;
	bar2_qid_offset = bar2_qid * SGE_UDB_SIZE;

	/* If the BAR2 Queue ID Offset is less than the Page Size, then the
	 * hardware will infer the Absolute Queue ID simply from the writes to
	 * the BAR2 Queue ID Offset within the BAR2 Page (and we need to use a
	 * BAR2 Queue ID of 0 for those writes).  Otherwise, we'll simply
	 * write to the first BAR2 SGE Queue Area within the BAR2 Page with
	 * the BAR2 Queue ID and the hardware will infer the Absolute Queue ID
	 * from the BAR2 Page and BAR2 Queue ID.
	 *
	 * One important censequence of this is that some BAR2 SGE registers
	 * have a "Queue ID" field and we can write the BAR2 SGE Queue ID
	 * there.  But other registers synthesize the SGE Queue ID purely
	 * from the writes to the registers -- the Write Combined Doorbell
	 * Buffer is a good example.  These BAR2 SGE Registers are only
	 * available for those BAR2 SGE Register areas where the SGE Absolute
	 * Queue ID can be inferred from simple writes.
	 */
	bar2_qoffset = bar2_page_offset;
	bar2_qinferred = (bar2_qid_offset < page_size);
	if (bar2_qinferred) {
		bar2_qoffset += bar2_qid_offset;
		bar2_qid = 0;
	}

	*pbar2_qoffset = bar2_qoffset;
	*pbar2_qid = bar2_qid;
	return 0;
}