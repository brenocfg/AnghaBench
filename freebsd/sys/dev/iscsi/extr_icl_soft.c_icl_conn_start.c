#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockopt {int* sopt_val; int sopt_valsize; int /*<<< orphan*/  sopt_name; int /*<<< orphan*/  sopt_level; int /*<<< orphan*/  sopt_dir; } ;
struct iscsi_bhs {int dummy; } ;
struct icl_conn {int ic_receive_len; int ic_disconnecting; int ic_max_data_segment_length; int ic_send_running; int ic_receive_running; int /*<<< orphan*/  ic_send_cv; int /*<<< orphan*/  ic_name; TYPE_1__* ic_socket; int /*<<< orphan*/  ic_receive_state; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  one ;
struct TYPE_7__ {int /*<<< orphan*/  sb_flags; } ;
struct TYPE_6__ {TYPE_4__ so_rcv; TYPE_4__ so_snd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_STATE_BHS ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_WARN (char*,int) ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int ISCSI_DATA_DIGEST_SIZE ; 
 int ISCSI_HEADER_DIGEST_SIZE ; 
 int /*<<< orphan*/  SB_AUTOSIZE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  SOPT_SET ; 
 int /*<<< orphan*/  SO_RCV ; 
 int /*<<< orphan*/  SO_SND ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  bzero (struct sockopt*,int) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_receive_thread ; 
 int /*<<< orphan*/  icl_send_thread ; 
 int /*<<< orphan*/  icl_soft_conn_close (struct icl_conn*) ; 
 int /*<<< orphan*/  icl_soupcall_receive ; 
 int /*<<< orphan*/  icl_soupcall_send ; 
 int kthread_add (int /*<<< orphan*/ ,struct icl_conn*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 size_t recvspace ; 
 size_t sendspace ; 
 int soreserve (TYPE_1__*,size_t,size_t) ; 
 int sosetopt (TYPE_1__*,struct sockopt*) ; 
 int /*<<< orphan*/  soupcall_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icl_conn*) ; 

__attribute__((used)) static int
icl_conn_start(struct icl_conn *ic)
{
	size_t minspace;
	struct sockopt opt;
	int error, one = 1;

	ICL_CONN_LOCK(ic);

	/*
	 * XXX: Ugly hack.
	 */
	if (ic->ic_socket == NULL) {
		ICL_CONN_UNLOCK(ic);
		return (EINVAL);
	}

	ic->ic_receive_state = ICL_CONN_STATE_BHS;
	ic->ic_receive_len = sizeof(struct iscsi_bhs);
	ic->ic_disconnecting = false;

	ICL_CONN_UNLOCK(ic);

	/*
	 * For sendspace, this is required because the current code cannot
	 * send a PDU in pieces; thus, the minimum buffer size is equal
	 * to the maximum PDU size.  "+4" is to account for possible padding.
	 *
	 * What we should actually do here is to use autoscaling, but set
	 * some minimal buffer size to "minspace".  I don't know a way to do
	 * that, though.
	 */
	minspace = sizeof(struct iscsi_bhs) + ic->ic_max_data_segment_length +
	    ISCSI_HEADER_DIGEST_SIZE + ISCSI_DATA_DIGEST_SIZE + 4;
	if (sendspace < minspace) {
		ICL_WARN("kern.icl.sendspace too low; must be at least %zd",
		    minspace);
		sendspace = minspace;
	}
	if (recvspace < minspace) {
		ICL_WARN("kern.icl.recvspace too low; must be at least %zd",
		    minspace);
		recvspace = minspace;
	}

	error = soreserve(ic->ic_socket, sendspace, recvspace);
	if (error != 0) {
		ICL_WARN("soreserve failed with error %d", error);
		icl_soft_conn_close(ic);
		return (error);
	}
	ic->ic_socket->so_snd.sb_flags |= SB_AUTOSIZE;
	ic->ic_socket->so_rcv.sb_flags |= SB_AUTOSIZE;

	/*
	 * Disable Nagle.
	 */
	bzero(&opt, sizeof(opt));
	opt.sopt_dir = SOPT_SET;
	opt.sopt_level = IPPROTO_TCP;
	opt.sopt_name = TCP_NODELAY;
	opt.sopt_val = &one;
	opt.sopt_valsize = sizeof(one);
	error = sosetopt(ic->ic_socket, &opt);
	if (error != 0) {
		ICL_WARN("disabling TCP_NODELAY failed with error %d", error);
		icl_soft_conn_close(ic);
		return (error);
	}

	/*
	 * Register socket upcall, to get notified about incoming PDUs
	 * and free space to send outgoing ones.
	 */
	SOCKBUF_LOCK(&ic->ic_socket->so_snd);
	soupcall_set(ic->ic_socket, SO_SND, icl_soupcall_send, ic);
	SOCKBUF_UNLOCK(&ic->ic_socket->so_snd);
	SOCKBUF_LOCK(&ic->ic_socket->so_rcv);
	soupcall_set(ic->ic_socket, SO_RCV, icl_soupcall_receive, ic);
	SOCKBUF_UNLOCK(&ic->ic_socket->so_rcv);

	/*
	 * Start threads.
	 */
	ICL_CONN_LOCK(ic);
	ic->ic_send_running = ic->ic_receive_running = true;
	ICL_CONN_UNLOCK(ic);
	error = kthread_add(icl_send_thread, ic, NULL, NULL, 0, 0, "%stx",
	    ic->ic_name);
	if (error != 0) {
		ICL_WARN("kthread_add(9) failed with error %d", error);
		ICL_CONN_LOCK(ic);
		ic->ic_send_running = ic->ic_receive_running = false;
		cv_signal(&ic->ic_send_cv);
		ICL_CONN_UNLOCK(ic);
		icl_soft_conn_close(ic);
		return (error);
	}
	error = kthread_add(icl_receive_thread, ic, NULL, NULL, 0, 0, "%srx",
	    ic->ic_name);
	if (error != 0) {
		ICL_WARN("kthread_add(9) failed with error %d", error);
		ICL_CONN_LOCK(ic);
		ic->ic_receive_running = false;
		cv_signal(&ic->ic_send_cv);
		ICL_CONN_UNLOCK(ic);
		icl_soft_conn_close(ic);
		return (error);
	}

	return (0);
}