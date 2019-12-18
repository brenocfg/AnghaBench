#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct sctp_tcb {int /*<<< orphan*/  tcb_mtx; } ;
struct sctp_inpcb {TYPE_3__* sctp_socket; int /*<<< orphan*/  inp_create_mtx; int /*<<< orphan*/  inp_mtx; } ;
struct TYPE_11__ {int /*<<< orphan*/  log4; int /*<<< orphan*/  log3; int /*<<< orphan*/  log2; int /*<<< orphan*/  log1; } ;
struct TYPE_10__ {void* socksndbuf_lock; void* sockrcvbuf_lock; void* sock_lock; int /*<<< orphan*/  info_lock; void* create_lock; void* inp_lock; void* tcb_lock; void* inp; void* sock; } ;
struct TYPE_12__ {TYPE_5__ misc; TYPE_4__ lock; } ;
struct sctp_cwnd_log {TYPE_6__ x; } ;
typedef  int /*<<< orphan*/  sctp_clog ;
struct TYPE_8__ {int /*<<< orphan*/  sb_mtx; } ;
struct TYPE_7__ {int /*<<< orphan*/  sb_mtx; } ;
struct TYPE_9__ {TYPE_2__ so_snd; TYPE_1__ so_rcv; } ;

/* Variables and functions */
 int /*<<< orphan*/  KTR_SCTP ; 
 int /*<<< orphan*/  SCTP_BASE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCTP_CTR6 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* SCTP_LOCK_UNKNOWN ; 
 int /*<<< orphan*/  SCTP_LOG_LOCK_EVENT ; 
 int /*<<< orphan*/  ipi_ep_mtx ; 
 int /*<<< orphan*/  memset (struct sctp_cwnd_log*,int /*<<< orphan*/ ,int) ; 
 void* mtx_owned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wowned (int /*<<< orphan*/ *) ; 

void
sctp_log_lock(struct sctp_inpcb *inp, struct sctp_tcb *stcb, uint8_t from)
{
#if defined(SCTP_LOCAL_TRACE_BUF)
	struct sctp_cwnd_log sctp_clog;

	memset(&sctp_clog, 0, sizeof(sctp_clog));
	if (inp) {
		sctp_clog.x.lock.sock = (void *)inp->sctp_socket;

	} else {
		sctp_clog.x.lock.sock = (void *)NULL;
	}
	sctp_clog.x.lock.inp = (void *)inp;
	if (stcb) {
		sctp_clog.x.lock.tcb_lock = mtx_owned(&stcb->tcb_mtx);
	} else {
		sctp_clog.x.lock.tcb_lock = SCTP_LOCK_UNKNOWN;
	}
	if (inp) {
		sctp_clog.x.lock.inp_lock = mtx_owned(&inp->inp_mtx);
		sctp_clog.x.lock.create_lock = mtx_owned(&inp->inp_create_mtx);
	} else {
		sctp_clog.x.lock.inp_lock = SCTP_LOCK_UNKNOWN;
		sctp_clog.x.lock.create_lock = SCTP_LOCK_UNKNOWN;
	}
	sctp_clog.x.lock.info_lock = rw_wowned(&SCTP_BASE_INFO(ipi_ep_mtx));
	if (inp && (inp->sctp_socket)) {
		sctp_clog.x.lock.sock_lock = mtx_owned(&(inp->sctp_socket->so_rcv.sb_mtx));
		sctp_clog.x.lock.sockrcvbuf_lock = mtx_owned(&(inp->sctp_socket->so_rcv.sb_mtx));
		sctp_clog.x.lock.socksndbuf_lock = mtx_owned(&(inp->sctp_socket->so_snd.sb_mtx));
	} else {
		sctp_clog.x.lock.sock_lock = SCTP_LOCK_UNKNOWN;
		sctp_clog.x.lock.sockrcvbuf_lock = SCTP_LOCK_UNKNOWN;
		sctp_clog.x.lock.socksndbuf_lock = SCTP_LOCK_UNKNOWN;
	}
	SCTP_CTR6(KTR_SCTP, "SCTP:%d[%d]:%x-%x-%x-%x",
	    SCTP_LOG_LOCK_EVENT,
	    from,
	    sctp_clog.x.misc.log1,
	    sctp_clog.x.misc.log2,
	    sctp_clog.x.misc.log3,
	    sctp_clog.x.misc.log4);
#endif
}