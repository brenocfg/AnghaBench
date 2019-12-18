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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct sctp_tmit_chunk {int dummy; } ;
struct sctp_association {int str_reset_seq_in; int local_strreset_support; int streamoutcnt; void** last_reset_action; scalar_t__ stream_reset_outstanding; } ;
struct sctp_tcb {struct sctp_association asoc; } ;
struct sctp_stream_reset_add_strm {int /*<<< orphan*/  number_of_streams; int /*<<< orphan*/  request_seq; } ;

/* Variables and functions */
 int SCTP_ENABLE_CHANGE_ASSOC_REQ ; 
 void* SCTP_STREAM_RESET_RESULT_DENIED ; 
 void* SCTP_STREAM_RESET_RESULT_ERR_BAD_SEQNO ; 
 void* SCTP_STREAM_RESET_RESULT_ERR_IN_PROGRESS ; 
 void* SCTP_STREAM_RESET_RESULT_PERFORMED ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_add_stream_reset_result (struct sctp_tmit_chunk*,int,void*) ; 
 scalar_t__ sctp_send_str_reset_req (struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
sctp_handle_str_reset_add_out_strm(struct sctp_tcb *stcb, struct sctp_tmit_chunk *chk,
    struct sctp_stream_reset_add_strm *str_add)
{
	/*
	 * Peer is requesting to add more streams. If its within our
	 * max-streams we will allow it.
	 */
	uint16_t num_stream;
	uint32_t seq;
	struct sctp_association *asoc = &stcb->asoc;

	/* Get the number. */
	seq = ntohl(str_add->request_seq);
	num_stream = ntohs(str_add->number_of_streams);
	/* Now what would be the new total? */
	if (asoc->str_reset_seq_in == seq) {
		stcb->asoc.last_reset_action[1] = stcb->asoc.last_reset_action[0];
		if (!(asoc->local_strreset_support & SCTP_ENABLE_CHANGE_ASSOC_REQ)) {
			asoc->last_reset_action[0] = SCTP_STREAM_RESET_RESULT_DENIED;
		} else if (stcb->asoc.stream_reset_outstanding) {
			/* We must reject it we have something pending */
			stcb->asoc.last_reset_action[0] = SCTP_STREAM_RESET_RESULT_ERR_IN_PROGRESS;
		} else {
			/* Ok, we can do that :-) */
			int mychk;

			mychk = stcb->asoc.streamoutcnt;
			mychk += num_stream;
			if (mychk < 0x10000) {
				stcb->asoc.last_reset_action[0] = SCTP_STREAM_RESET_RESULT_PERFORMED;
				if (sctp_send_str_reset_req(stcb, 0, NULL, 0, 0, 1, num_stream, 0, 1)) {
					stcb->asoc.last_reset_action[0] = SCTP_STREAM_RESET_RESULT_DENIED;
				}
			} else {
				stcb->asoc.last_reset_action[0] = SCTP_STREAM_RESET_RESULT_DENIED;
			}
		}
		sctp_add_stream_reset_result(chk, seq, stcb->asoc.last_reset_action[0]);
		asoc->str_reset_seq_in++;
	} else if ((asoc->str_reset_seq_in - 1) == seq) {
		/*
		 * one seq back, just echo back last action since my
		 * response was lost.
		 */
		sctp_add_stream_reset_result(chk, seq, asoc->last_reset_action[0]);
	} else if ((asoc->str_reset_seq_in - 2) == seq) {
		/*
		 * two seq back, just echo back last action since my
		 * response was lost.
		 */
		sctp_add_stream_reset_result(chk, seq, asoc->last_reset_action[1]);
	} else {
		sctp_add_stream_reset_result(chk, seq, SCTP_STREAM_RESET_RESULT_ERR_BAD_SEQNO);
	}
}