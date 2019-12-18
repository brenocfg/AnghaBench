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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct sctp_tmit_chunk {int dummy; } ;
struct sctp_tcb {int dummy; } ;
struct sctp_gap_ack_block {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct sctp_association {int /*<<< orphan*/  sent_queue; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int SCTP_FR_LOGGING_ENABLE ; 
 int /*<<< orphan*/  SCTP_FR_LOG_BIGGEST_TSNS ; 
 scalar_t__ SCTP_TSN_GT (scalar_t__,scalar_t__) ; 
 struct sctp_tmit_chunk* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_log_fr (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 
 scalar_t__ sctp_m_getptr (struct mbuf*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_process_segment_range (struct sctp_tcb*,struct sctp_tmit_chunk**,scalar_t__,scalar_t__,scalar_t__,int,int*,scalar_t__*,scalar_t__*,int*) ; 

__attribute__((used)) static int
sctp_handle_segments(struct mbuf *m, int *offset, struct sctp_tcb *stcb, struct sctp_association *asoc,
    uint32_t last_tsn, uint32_t *biggest_tsn_acked,
    uint32_t *biggest_newly_acked_tsn, uint32_t *this_sack_lowest_newack,
    int num_seg, int num_nr_seg, int *rto_ok)
{
	struct sctp_gap_ack_block *frag, block;
	struct sctp_tmit_chunk *tp1;
	int i;
	int num_frs = 0;
	int chunk_freed;
	int non_revocable;
	uint16_t frag_strt, frag_end, prev_frag_end;

	tp1 = TAILQ_FIRST(&asoc->sent_queue);
	prev_frag_end = 0;
	chunk_freed = 0;

	for (i = 0; i < (num_seg + num_nr_seg); i++) {
		if (i == num_seg) {
			prev_frag_end = 0;
			tp1 = TAILQ_FIRST(&asoc->sent_queue);
		}
		frag = (struct sctp_gap_ack_block *)sctp_m_getptr(m, *offset,
		    sizeof(struct sctp_gap_ack_block), (uint8_t *)&block);
		*offset += sizeof(block);
		if (frag == NULL) {
			return (chunk_freed);
		}
		frag_strt = ntohs(frag->start);
		frag_end = ntohs(frag->end);

		if (frag_strt > frag_end) {
			/* This gap report is malformed, skip it. */
			continue;
		}
		if (frag_strt <= prev_frag_end) {
			/* This gap report is not in order, so restart. */
			tp1 = TAILQ_FIRST(&asoc->sent_queue);
		}
		if (SCTP_TSN_GT((last_tsn + frag_end), *biggest_tsn_acked)) {
			*biggest_tsn_acked = last_tsn + frag_end;
		}
		if (i < num_seg) {
			non_revocable = 0;
		} else {
			non_revocable = 1;
		}
		if (sctp_process_segment_range(stcb, &tp1, last_tsn, frag_strt, frag_end,
		    non_revocable, &num_frs, biggest_newly_acked_tsn,
		    this_sack_lowest_newack, rto_ok)) {
			chunk_freed = 1;
		}
		prev_frag_end = frag_end;
	}
	if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_FR_LOGGING_ENABLE) {
		if (num_frs)
			sctp_log_fr(*biggest_tsn_acked,
			    *biggest_newly_acked_tsn,
			    last_tsn, SCTP_FR_LOG_BIGGEST_TSNS);
	}
	return (chunk_freed);
}