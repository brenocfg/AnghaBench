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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct socket {int dummy; } ;
struct sockaddr {int dummy; } ;
struct sctphdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; scalar_t__ vrf_id; scalar_t__ peer_vtag; } ;
struct sctp_tcb {TYPE_1__ asoc; } ;
struct sctp_inpcb {int /*<<< orphan*/  fibnum; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_ADD_SUBSTATE (struct sctp_tcb*,int /*<<< orphan*/ ) ; 
 scalar_t__ SCTP_FROM_SCTPUTIL ; 
 scalar_t__ SCTP_GET_STATE (struct sctp_tcb*) ; 
 struct socket* SCTP_INP_SO (struct sctp_inpcb*) ; 
 scalar_t__ SCTP_LOC_4 ; 
 int /*<<< orphan*/  SCTP_NORMAL_PROC ; 
 int /*<<< orphan*/  SCTP_SOCKET_LOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SOCKET_UNLOCK (struct socket*,int) ; 
 int /*<<< orphan*/  SCTP_SO_NOT_LOCKED ; 
 scalar_t__ SCTP_STATE_OPEN ; 
 scalar_t__ SCTP_STATE_SHUTDOWN_RECEIVED ; 
 int /*<<< orphan*/  SCTP_STATE_WAS_ABORTED ; 
 int /*<<< orphan*/  SCTP_STAT_DECR_GAUGE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_STAT_INCR_COUNTER32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_TCB_LOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  SCTP_TCB_UNLOCK (struct sctp_tcb*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sctp_abort_notification (struct sctp_tcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_free_assoc (struct sctp_inpcb*,struct sctp_tcb*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sctp_send_abort (struct mbuf*,int,struct sockaddr*,struct sockaddr*,struct sctphdr*,scalar_t__,struct mbuf*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctps_aborted ; 
 int /*<<< orphan*/  sctps_currestab ; 

void
sctp_abort_association(struct sctp_inpcb *inp, struct sctp_tcb *stcb,
    struct mbuf *m, int iphlen,
    struct sockaddr *src, struct sockaddr *dst,
    struct sctphdr *sh, struct mbuf *op_err,
    uint8_t mflowtype, uint32_t mflowid,
    uint32_t vrf_id, uint16_t port)
{
	uint32_t vtag;
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
	struct socket *so;
#endif

	vtag = 0;
	if (stcb != NULL) {
		vtag = stcb->asoc.peer_vtag;
		vrf_id = stcb->asoc.vrf_id;
	}
	sctp_send_abort(m, iphlen, src, dst, sh, vtag, op_err,
	    mflowtype, mflowid, inp->fibnum,
	    vrf_id, port);
	if (stcb != NULL) {
		/* We have a TCB to abort, send notification too */
		sctp_abort_notification(stcb, 0, 0, NULL, SCTP_SO_NOT_LOCKED);
		SCTP_ADD_SUBSTATE(stcb, SCTP_STATE_WAS_ABORTED);
		/* Ok, now lets free it */
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		so = SCTP_INP_SO(inp);
		atomic_add_int(&stcb->asoc.refcnt, 1);
		SCTP_TCB_UNLOCK(stcb);
		SCTP_SOCKET_LOCK(so, 1);
		SCTP_TCB_LOCK(stcb);
		atomic_subtract_int(&stcb->asoc.refcnt, 1);
#endif
		SCTP_STAT_INCR_COUNTER32(sctps_aborted);
		if ((SCTP_GET_STATE(stcb) == SCTP_STATE_OPEN) ||
		    (SCTP_GET_STATE(stcb) == SCTP_STATE_SHUTDOWN_RECEIVED)) {
			SCTP_STAT_DECR_GAUGE32(sctps_currestab);
		}
		(void)sctp_free_assoc(inp, stcb, SCTP_NORMAL_PROC,
		    SCTP_FROM_SCTPUTIL + SCTP_LOC_4);
#if defined(__APPLE__) || defined(SCTP_SO_LOCK_TESTING)
		SCTP_SOCKET_UNLOCK(so, 1);
#endif
	}
}