#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t sb_lowat; int sb_hiwat; int /*<<< orphan*/  sb_mtx; } ;
struct socket {TYPE_1__ so_rcv; } ;
struct icl_conn {size_t ic_receive_len; int ic_receive_running; int /*<<< orphan*/  ic_send_cv; int /*<<< orphan*/  ic_receive_cv; scalar_t__ ic_disconnecting; struct socket* ic_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_CONN_UNLOCK (struct icl_conn*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_conn_receive_pdus (struct icl_conn*,size_t) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 size_t sbavail (TYPE_1__*) ; 

__attribute__((used)) static void
icl_receive_thread(void *arg)
{
	struct icl_conn *ic;
	size_t available;
	struct socket *so;

	ic = arg;
	so = ic->ic_socket;

	for (;;) {
		if (ic->ic_disconnecting) {
			//ICL_DEBUG("terminating");
			break;
		}

		/*
		 * Set the low watermark, to be checked by
		 * soreadable() in icl_soupcall_receive()
		 * to avoid unnecessary wakeups until there
		 * is enough data received to read the PDU.
		 */
		SOCKBUF_LOCK(&so->so_rcv);
		available = sbavail(&so->so_rcv);
		if (available < ic->ic_receive_len) {
			so->so_rcv.sb_lowat = ic->ic_receive_len;
			cv_wait(&ic->ic_receive_cv, &so->so_rcv.sb_mtx);
		} else
			so->so_rcv.sb_lowat = so->so_rcv.sb_hiwat + 1;
		SOCKBUF_UNLOCK(&so->so_rcv);

		icl_conn_receive_pdus(ic, available);
	}

	ICL_CONN_LOCK(ic);
	ic->ic_receive_running = false;
	cv_signal(&ic->ic_send_cv);
	ICL_CONN_UNLOCK(ic);
	kthread_exit();
}