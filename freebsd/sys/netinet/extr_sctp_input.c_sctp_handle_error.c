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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct socket {int dummy; } ;
struct sctp_association {int cookie_preserve_req; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  max_init_times; int /*<<< orphan*/  stale_cookie_count; } ;
struct sctp_tcb {int /*<<< orphan*/  sctp_ep; struct sctp_association asoc; } ;
struct sctp_paramhdr {int /*<<< orphan*/  param_type; } ;
struct sctp_nets {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  chunk_type; } ;
struct sctp_error_unrecognized_chunk {TYPE_1__ ch; } ;
struct sctp_error_stale_cookie {int /*<<< orphan*/  stale_time; } ;
struct sctp_error_cause {int /*<<< orphan*/  length; int /*<<< orphan*/  code; } ;
struct sctp_chunkhdr {int chunk_flags; int /*<<< orphan*/  chunk_length; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTPDBG (int /*<<< orphan*/ ,char*,int,...) ; 
#define  SCTP_CAUSE_COOKIE_IN_SHUTDOWN 142 
#define  SCTP_CAUSE_DELETING_LAST_ADDR 141 
#define  SCTP_CAUSE_DELETING_SRC_ADDR 140 
#define  SCTP_CAUSE_INVALID_PARAM 139 
#define  SCTP_CAUSE_INVALID_STREAM 138 
#define  SCTP_CAUSE_MISSING_PARAM 137 
#define  SCTP_CAUSE_NAT_COLLIDING_STATE 136 
#define  SCTP_CAUSE_NAT_MISSING_STATE 135 
#define  SCTP_CAUSE_NO_USER_DATA 134 
#define  SCTP_CAUSE_OUT_OF_RESC 133 
#define  SCTP_CAUSE_RESOURCE_SHORTAGE 132 
#define  SCTP_CAUSE_STALE_COOKIE 131 
#define  SCTP_CAUSE_UNRECOG_CHUNK 130 
#define  SCTP_CAUSE_UNRECOG_PARAM 129 
#define  SCTP_CAUSE_UNRESOLVABLE_ADDR 128 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT1 ; 
 int /*<<< orphan*/  SCTP_DEBUG_INPUT2 ; 
 scalar_t__ SCTP_FROM_SCTP_INPUT ; 
 int /*<<< orphan*/  SCTP_GET_STATE (struct sctp_tcb*) ; 
 struct socket* SCTP_INP_SO (int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_LOC_12 ; 
 int /*<<< orphan*/  SCTP_NORMAL_PROC ; 
 int /*<<< orphan*/  SCTP_NOTIFY_REMOTE_ERROR ; 
 int /*<<< orphan*/  SCTP_SET_STATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int SCTP_SIZE32 (int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_LOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_UNLOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 int /*<<< orphan*/  SCTP_STATE_COOKIE_ECHOED ; 
 int /*<<< orphan*/  SCTP_STATE_COOKIE_WAIT ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_abort_notification (struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_assoc (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sctp_handle_nat_colliding_state (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_handle_nat_missing_state (struct sctp_tcb*,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_process_unrecog_chunk (struct sctp_tcb*,int /*<<< orphan*/ ,struct sctp_nets*) ; 
 int /*<<< orphan*/  sctp_process_unrecog_param (struct sctp_tcb*,int) ; 
 int /*<<< orphan*/  sctp_send_initiate (int /*<<< orphan*/ ,struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_stop_all_cookie_timers (struct sctp_tcb*) ; 
 int /*<<< orphan*/  sctp_toss_old_cookies (struct sctp_tcb*,struct sctp_association*) ; 
 int /*<<< orphan*/  sctp_ulp_notify (int /*<<< orphan*/ ,struct sctp_tcb*,int,struct sctp_chunkhdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sctp_handle_error(struct sctp_chunkhdr *ch,
    struct sctp_tcb *stcb, struct sctp_nets *net, uint32_t limit)
{
	struct sctp_error_cause *cause;
	struct sctp_association *asoc;
	uint32_t remaining_length, adjust;
	uint16_t code, cause_code, cause_length;
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	struct socket *so;
#endif

	/* parse through all of the errors and process */
	asoc = &stcb->asoc;
	cause = (struct sctp_error_cause *)((caddr_t)ch +
	    sizeof(struct sctp_chunkhdr));
	remaining_length = ntohs(ch->chunk_length);
	if (remaining_length > limit) {
		remaining_length = limit;
	}
	if (remaining_length >= sizeof(struct sctp_chunkhdr)) {
		remaining_length -= sizeof(struct sctp_chunkhdr);
	} else {
		remaining_length = 0;
	}
	code = 0;
	while (remaining_length >= sizeof(struct sctp_error_cause)) {
		/* Process an Error Cause */
		cause_code = ntohs(cause->code);
		cause_length = ntohs(cause->length);
		if ((cause_length > remaining_length) || (cause_length == 0)) {
			/* Invalid cause length, possibly due to truncation. */
			SCTPDBG(SCTP_DEBUG_INPUT1, "Bogus length in cause - bytes left: %u cause length: %u\n",
			    remaining_length, cause_length);
			return (0);
		}
		if (code == 0) {
			/* report the first error cause */
			code = cause_code;
		}
		switch (cause_code) {
		case SCTP_CAUSE_INVALID_STREAM:
		case SCTP_CAUSE_MISSING_PARAM:
		case SCTP_CAUSE_INVALID_PARAM:
		case SCTP_CAUSE_NO_USER_DATA:
			SCTPDBG(SCTP_DEBUG_INPUT1, "Software error we got a %u back? We have a bug :/ (or do they?)\n",
			    cause_code);
			break;
		case SCTP_CAUSE_NAT_COLLIDING_STATE:
			SCTPDBG(SCTP_DEBUG_INPUT2, "Received Colliding state abort flags: %x\n",
			    ch->chunk_flags);
			if (sctp_handle_nat_colliding_state(stcb)) {
				return (0);
			}
			break;
		case SCTP_CAUSE_NAT_MISSING_STATE:
			SCTPDBG(SCTP_DEBUG_INPUT2, "Received missing state abort flags: %x\n",
			    ch->chunk_flags);
			if (sctp_handle_nat_missing_state(stcb, net)) {
				return (0);
			}
			break;
		case SCTP_CAUSE_STALE_COOKIE:
			/*
			 * We only act if we have echoed a cookie and are
			 * waiting.
			 */
			if ((cause_length >= sizeof(struct sctp_error_stale_cookie)) &&
			    (SCTP_GET_STATE(stcb) == SCTP_STATE_COOKIE_ECHOED)) {
				struct sctp_error_stale_cookie *stale_cookie;

				stale_cookie = (struct sctp_error_stale_cookie *)cause;
				asoc->cookie_preserve_req = ntohl(stale_cookie->stale_time);
				/* Double it to be more robust on RTX */
				if (asoc->cookie_preserve_req <= UINT32_MAX / 2) {
					asoc->cookie_preserve_req *= 2;
				} else {
					asoc->cookie_preserve_req = UINT32_MAX;
				}
				asoc->stale_cookie_count++;
				if (asoc->stale_cookie_count >
				    asoc->max_init_times) {
					sctp_abort_notification(stcb, 0, 0, NULL, SCTP_SO_NOT_LOCKED);
					/* now free the asoc */
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
					so = SCTP_INP_SO(stcb->sctp_ep);
					atomic_add_int(&stcb->asoc.refcnt, 1);
					SCTP_TCB_UNLOCK(stcb);
					SCTP_SOCKET_LOCK(so, 1);
					SCTP_TCB_LOCK(stcb);
					atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
					(void)sctp_free_assoc(stcb->sctp_ep, stcb, SCTP_NORMAL_PROC,
					    SCTP_FROM_SCTP_INPUT + SCTP_LOC_12);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
					SCTP_SOCKET_UNLOCK(so, 1);
#endif
					return (-1);
				}
				/* blast back to INIT state */
				sctp_toss_old_cookies(stcb, &stcb->asoc);
				SCTP_SET_STATE(stcb, SCTP_STATE_COOKIE_WAIT);
				sctp_stop_all_cookie_timers(stcb);
				sctp_send_initiate(stcb->sctp_ep, stcb, SCTP_SO_NOT_LOCKED);
			}
			break;
		case SCTP_CAUSE_UNRESOLVABLE_ADDR:
			/*
			 * Nothing we can do here, we don't do hostname
			 * addresses so if the peer does not like my IPv6
			 * (or IPv4 for that matter) it does not matter. If
			 * they don't support that type of address, they can
			 * NOT possibly get that packet type... i.e. with no
			 * IPv6 you can't receive a IPv6 packet. so we can
			 * safely ignore this one. If we ever added support
			 * for HOSTNAME Addresses, then we would need to do
			 * something here.
			 */
			break;
		case SCTP_CAUSE_UNRECOG_CHUNK:
			if (cause_length >= sizeof(struct sctp_error_unrecognized_chunk)) {
				struct sctp_error_unrecognized_chunk *unrec_chunk;

				unrec_chunk = (struct sctp_error_unrecognized_chunk *)cause;
				sctp_process_unrecog_chunk(stcb, unrec_chunk->ch.chunk_type, net);
			}
			break;
		case SCTP_CAUSE_UNRECOG_PARAM:
			/* XXX: We only consider the first parameter */
			if (cause_length >= sizeof(struct sctp_error_cause) + sizeof(struct sctp_paramhdr)) {
				struct sctp_paramhdr *unrec_parameter;

				unrec_parameter = (struct sctp_paramhdr *)(cause + 1);
				sctp_process_unrecog_param(stcb, ntohs(unrec_parameter->param_type));
			}
			break;
		case SCTP_CAUSE_COOKIE_IN_SHUTDOWN:
			/*
			 * We ignore this since the timer will drive out a
			 * new cookie anyway and there timer will drive us
			 * to send a SHUTDOWN_COMPLETE. We can't send one
			 * here since we don't have their tag.
			 */
			break;
		case SCTP_CAUSE_DELETING_LAST_ADDR:
		case SCTP_CAUSE_RESOURCE_SHORTAGE:
		case SCTP_CAUSE_DELETING_SRC_ADDR:
			/*
			 * We should NOT get these here, but in a
			 * ASCONF-ACK.
			 */
			SCTPDBG(SCTP_DEBUG_INPUT2, "Peer sends ASCONF errors in a error cause with code %u.\n",
			    cause_code);
			break;
		case SCTP_CAUSE_OUT_OF_RESC:
			/*
			 * And what, pray tell do we do with the fact that
			 * the peer is out of resources? Not really sure we
			 * could do anything but abort. I suspect this
			 * should have came WITH an abort instead of in a
			 * OP-ERROR.
			 */
			break;
		default:
			SCTPDBG(SCTP_DEBUG_INPUT1, "sctp_handle_error: unknown code 0x%x\n",
			    cause_code);
			break;
		}
		adjust = SCTP_SIZE32(cause_length);
		if (remaining_length >= adjust) {
			remaining_length -= adjust;
		} else {
			remaining_length = 0;
		}
		cause = (struct sctp_error_cause *)((caddr_t)cause + adjust);
	}
	sctp_ulp_notify(SCTP_NOTIFY_REMOTE_ERROR, stcb, code, ch, SCTP_SO_NOT_LOCKED);
	return (0);
}