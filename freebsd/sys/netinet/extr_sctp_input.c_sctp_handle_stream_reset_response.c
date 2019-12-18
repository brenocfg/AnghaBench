#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct sctp_tmit_chunk {int dummy; } ;
struct sctp_association {scalar_t__ stream_reset_outstanding; scalar_t__ str_reset_seq_out; int stream_reset_out_is_outstanding; int strm_pending_add_size; int strm_realoutsize; int streamoutcnt; void* mapping_array_base_tsn; void* sending_seq; void* cumulative_tsn; void* last_acked_seq; int /*<<< orphan*/  mapping_array_size; int /*<<< orphan*/  nr_mapping_array; void* highest_tsn_inside_map; void* highest_tsn_inside_nr_map; int /*<<< orphan*/  mapping_array; void* tsn_last_delivered; int /*<<< orphan*/  streamincnt; TYPE_4__* strmout; } ;
struct sctp_tcb {struct sctp_association asoc; } ;
struct sctp_stream_reset_response_tsn {int /*<<< orphan*/  receivers_next_tsn; int /*<<< orphan*/  senders_next_tsn; } ;
struct TYPE_5__ {int /*<<< orphan*/  param_length; } ;
struct sctp_stream_reset_response {TYPE_1__ ph; } ;
struct TYPE_7__ {int /*<<< orphan*/  param_length; int /*<<< orphan*/  param_type; } ;
struct sctp_stream_reset_request {TYPE_3__ ph; } ;
struct sctp_stream_reset_out_request {scalar_t__* list_of_streams; } ;
struct sctp_stream_reset_in_request {scalar_t__* list_of_streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  chunk_type; int /*<<< orphan*/  chunk_length; } ;
struct sctp_forward_tsn_chunk {int /*<<< orphan*/  new_cumulative_tsn; TYPE_2__ ch; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ASSOC_RESET_DENIED ; 
 int /*<<< orphan*/  SCTP_ASSOC_RESET_FAILED ; 
 int SCTP_BASE_SYSCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_FORWARD_CUM_TSN ; 
 int SCTP_MAP_LOGGING_ENABLE ; 
 int /*<<< orphan*/  SCTP_MAP_SLIDE_RESULT ; 
 int /*<<< orphan*/  SCTP_NOTIFY_STR_RESET_DENIED_IN ; 
 int /*<<< orphan*/  SCTP_NOTIFY_STR_RESET_DENIED_OUT ; 
 int /*<<< orphan*/  SCTP_NOTIFY_STR_RESET_FAILED_IN ; 
 int /*<<< orphan*/  SCTP_NOTIFY_STR_RESET_FAILED_OUT ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_STREAM_CHANGE_DENIED ; 
 int /*<<< orphan*/  SCTP_STREAM_CHANGE_FAILED ; 
 int /*<<< orphan*/  SCTP_STREAM_OPEN ; 
 scalar_t__ SCTP_STREAM_RESET_RESULT_DENIED ; 
 scalar_t__ SCTP_STREAM_RESET_RESULT_IN_PROGRESS ; 
 scalar_t__ SCTP_STREAM_RESET_RESULT_PERFORMED ; 
 scalar_t__ SCTP_STR_RESET_ADD_IN_STREAMS ; 
 scalar_t__ SCTP_STR_RESET_ADD_OUT_STREAMS ; 
 scalar_t__ SCTP_STR_RESET_IN_REQUEST ; 
 scalar_t__ SCTP_STR_RESET_OUT_REQUEST ; 
 scalar_t__ SCTP_STR_RESET_TSN_REQUEST ; 
 int /*<<< orphan*/  htonl (void*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_clean_up_stream_reset (struct sctp_tcb*) ; 
 struct sctp_stream_reset_request* sctp_find_stream_reset (struct sctp_tcb*,scalar_t__,struct sctp_tmit_chunk**) ; 
 int /*<<< orphan*/  sctp_handle_forward_tsn (struct sctp_tcb*,struct sctp_forward_tsn_chunk*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_log_map (int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_logging_level ; 
 int /*<<< orphan*/  sctp_notify_stream_reset_add (struct sctp_tcb*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_notify_stream_reset_tsn (struct sctp_tcb*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_reset_clear_pending (struct sctp_tcb*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  sctp_reset_in_stream (struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  sctp_reset_out_streams (struct sctp_tcb*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  sctp_send_stream_reset_out_if_possible (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sctp_handle_stream_reset_response(struct sctp_tcb *stcb,
    uint32_t seq, uint32_t action,
    struct sctp_stream_reset_response *respin)
{
	uint16_t type;
	int lparam_len;
	struct sctp_association *asoc = &stcb->asoc;
	struct sctp_tmit_chunk *chk;
	struct sctp_stream_reset_request *req_param;
	struct sctp_stream_reset_out_request *req_out_param;
	struct sctp_stream_reset_in_request *req_in_param;
	uint32_t number_entries;

	if (asoc->stream_reset_outstanding == 0) {
		/* duplicate */
		return (0);
	}
	if (seq == stcb->asoc.str_reset_seq_out) {
		req_param = sctp_find_stream_reset(stcb, seq, &chk);
		if (req_param != NULL) {
			stcb->asoc.str_reset_seq_out++;
			type = ntohs(req_param->ph.param_type);
			lparam_len = ntohs(req_param->ph.param_length);
			if (type == SCTP_STR_RESET_OUT_REQUEST) {
				int no_clear = 0;

				req_out_param = (struct sctp_stream_reset_out_request *)req_param;
				number_entries = (lparam_len - sizeof(struct sctp_stream_reset_out_request)) / sizeof(uint16_t);
				asoc->stream_reset_out_is_outstanding = 0;
				if (asoc->stream_reset_outstanding)
					asoc->stream_reset_outstanding--;
				if (action == SCTP_STREAM_RESET_RESULT_PERFORMED) {
					/* do it */
					sctp_reset_out_streams(stcb, number_entries, req_out_param->list_of_streams);
				} else if (action == SCTP_STREAM_RESET_RESULT_DENIED) {
					sctp_ulp_notify(SCTP_NOTIFY_STR_RESET_DENIED_OUT, stcb, number_entries, req_out_param->list_of_streams, SCTP_SO_NOT_LOCKED);
				} else if (action == SCTP_STREAM_RESET_RESULT_IN_PROGRESS) {
					/*
					 * Set it up so we don't stop
					 * retransmitting
					 */
					asoc->stream_reset_outstanding++;
					stcb->asoc.str_reset_seq_out--;
					asoc->stream_reset_out_is_outstanding = 1;
					no_clear = 1;
				} else {
					sctp_ulp_notify(SCTP_NOTIFY_STR_RESET_FAILED_OUT, stcb, number_entries, req_out_param->list_of_streams, SCTP_SO_NOT_LOCKED);
				}
				if (no_clear == 0) {
					sctp_reset_clear_pending(stcb, number_entries, req_out_param->list_of_streams);
				}
			} else if (type == SCTP_STR_RESET_IN_REQUEST) {
				req_in_param = (struct sctp_stream_reset_in_request *)req_param;
				number_entries = (lparam_len - sizeof(struct sctp_stream_reset_in_request)) / sizeof(uint16_t);
				if (asoc->stream_reset_outstanding)
					asoc->stream_reset_outstanding--;
				if (action == SCTP_STREAM_RESET_RESULT_DENIED) {
					sctp_ulp_notify(SCTP_NOTIFY_STR_RESET_DENIED_IN, stcb,
					    number_entries, req_in_param->list_of_streams, SCTP_SO_NOT_LOCKED);
				} else if (action != SCTP_STREAM_RESET_RESULT_PERFORMED) {
					sctp_ulp_notify(SCTP_NOTIFY_STR_RESET_FAILED_IN, stcb,
					    number_entries, req_in_param->list_of_streams, SCTP_SO_NOT_LOCKED);
				}
			} else if (type == SCTP_STR_RESET_ADD_OUT_STREAMS) {
				/* Ok we now may have more streams */
				int num_stream;

				num_stream = stcb->asoc.strm_pending_add_size;
				if (num_stream > (stcb->asoc.strm_realoutsize - stcb->asoc.streamoutcnt)) {
					/* TSNH */
					num_stream = stcb->asoc.strm_realoutsize - stcb->asoc.streamoutcnt;
				}
				stcb->asoc.strm_pending_add_size = 0;
				if (asoc->stream_reset_outstanding)
					asoc->stream_reset_outstanding--;
				if (action == SCTP_STREAM_RESET_RESULT_PERFORMED) {
					/* Put the new streams into effect */
					int i;

					for (i = asoc->streamoutcnt; i < (asoc->streamoutcnt + num_stream); i++) {
						asoc->strmout[i].state = SCTP_STREAM_OPEN;
					}
					asoc->streamoutcnt += num_stream;
					sctp_notify_stream_reset_add(stcb, stcb->asoc.streamincnt, stcb->asoc.streamoutcnt, 0);
				} else if (action == SCTP_STREAM_RESET_RESULT_DENIED) {
					sctp_notify_stream_reset_add(stcb, stcb->asoc.streamincnt, stcb->asoc.streamoutcnt,
					    SCTP_STREAM_CHANGE_DENIED);
				} else {
					sctp_notify_stream_reset_add(stcb, stcb->asoc.streamincnt, stcb->asoc.streamoutcnt,
					    SCTP_STREAM_CHANGE_FAILED);
				}
			} else if (type == SCTP_STR_RESET_ADD_IN_STREAMS) {
				if (asoc->stream_reset_outstanding)
					asoc->stream_reset_outstanding--;
				if (action == SCTP_STREAM_RESET_RESULT_DENIED) {
					sctp_notify_stream_reset_add(stcb, stcb->asoc.streamincnt, stcb->asoc.streamoutcnt,
					    SCTP_STREAM_CHANGE_DENIED);
				} else if (action != SCTP_STREAM_RESET_RESULT_PERFORMED) {
					sctp_notify_stream_reset_add(stcb, stcb->asoc.streamincnt, stcb->asoc.streamoutcnt,
					    SCTP_STREAM_CHANGE_FAILED);
				}
			} else if (type == SCTP_STR_RESET_TSN_REQUEST) {
				/**
				 * a) Adopt the new in tsn.
				 * b) reset the map
				 * c) Adopt the new out-tsn
				 */
				struct sctp_stream_reset_response_tsn *resp;
				struct sctp_forward_tsn_chunk fwdtsn;
				int abort_flag = 0;

				if (respin == NULL) {
					/* huh ? */
					return (0);
				}
				if (ntohs(respin->ph.param_length) < sizeof(struct sctp_stream_reset_response_tsn)) {
					return (0);
				}
				if (action == SCTP_STREAM_RESET_RESULT_PERFORMED) {
					resp = (struct sctp_stream_reset_response_tsn *)respin;
					asoc->stream_reset_outstanding--;
					fwdtsn.ch.chunk_length = htons(sizeof(struct sctp_forward_tsn_chunk));
					fwdtsn.ch.chunk_type = SCTP_FORWARD_CUM_TSN;
					fwdtsn.new_cumulative_tsn = htonl(ntohl(resp->senders_next_tsn) - 1);
					sctp_handle_forward_tsn(stcb, &fwdtsn, &abort_flag, NULL, 0);
					if (abort_flag) {
						return (1);
					}
					stcb->asoc.highest_tsn_inside_map = (ntohl(resp->senders_next_tsn) - 1);
					if (SCTP_BASE_SYSCTL(sctp_logging_level) & SCTP_MAP_LOGGING_ENABLE) {
						sctp_log_map(0, 7, asoc->highest_tsn_inside_map, SCTP_MAP_SLIDE_RESULT);
					}

					stcb->asoc.tsn_last_delivered = stcb->asoc.cumulative_tsn = stcb->asoc.highest_tsn_inside_map;
					stcb->asoc.mapping_array_base_tsn = ntohl(resp->senders_next_tsn);
					memset(stcb->asoc.mapping_array, 0, stcb->asoc.mapping_array_size);

					stcb->asoc.highest_tsn_inside_nr_map = stcb->asoc.highest_tsn_inside_map;
					memset(stcb->asoc.nr_mapping_array, 0, stcb->asoc.mapping_array_size);

					stcb->asoc.sending_seq = ntohl(resp->receivers_next_tsn);
					stcb->asoc.last_acked_seq = stcb->asoc.cumulative_tsn;

					sctp_reset_out_streams(stcb, 0, (uint16_t *)NULL);
					sctp_reset_in_stream(stcb, 0, (uint16_t *)NULL);
					sctp_notify_stream_reset_tsn(stcb, stcb->asoc.sending_seq, (stcb->asoc.mapping_array_base_tsn + 1), 0);
				} else if (action == SCTP_STREAM_RESET_RESULT_DENIED) {
					sctp_notify_stream_reset_tsn(stcb, stcb->asoc.sending_seq, (stcb->asoc.mapping_array_base_tsn + 1),
					    SCTP_ASSOC_RESET_DENIED);
				} else {
					sctp_notify_stream_reset_tsn(stcb, stcb->asoc.sending_seq, (stcb->asoc.mapping_array_base_tsn + 1),
					    SCTP_ASSOC_RESET_FAILED);
				}
			}
			/* get rid of the request and get the request flags */
			if (asoc->stream_reset_outstanding == 0) {
				sctp_clean_up_stream_reset(stcb);
			}
		}
	}
	if (asoc->stream_reset_outstanding == 0) {
		sctp_send_stream_reset_out_if_possible(stcb, SCTP_SO_NOT_LOCKED);
	}
	return (0);
}