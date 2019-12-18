#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {long sb_lowat; long sb_hiwat; } ;
struct socket {TYPE_3__ so_snd; } ;
struct icl_pdu_stailq {int dummy; } ;
struct icl_pdu {TYPE_2__* ip_bhs_mbuf; } ;
struct icl_conn {struct socket* ic_socket; } ;
struct TYPE_8__ {long len; } ;
struct TYPE_9__ {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICL_CONN_LOCK_ASSERT_NOT (struct icl_conn*) ; 
 int /*<<< orphan*/  ICL_DEBUG (char*,...) ; 
 int /*<<< orphan*/  MSG_DONTWAIT ; 
 int /*<<< orphan*/  SOCKBUF_LOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  SOCKBUF_UNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  STAILQ_EMPTY (struct icl_pdu_stailq*) ; 
 struct icl_pdu* STAILQ_FIRST (struct icl_pdu_stailq*) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_AFTER (struct icl_pdu_stailq*,struct icl_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (struct icl_pdu_stailq*,int /*<<< orphan*/ ) ; 
 scalar_t__ coalesce ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  icl_conn_fail (struct icl_conn*) ; 
 int icl_pdu_finalize (struct icl_pdu*) ; 
 long icl_pdu_size (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_soft_conn_pdu_free (struct icl_conn*,struct icl_pdu*) ; 
 int /*<<< orphan*/  ip_next ; 
 int /*<<< orphan*/  m_cat (TYPE_2__*,TYPE_2__*) ; 
 long sbspace (TYPE_3__*) ; 
 int sosend (struct socket*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
icl_conn_send_pdus(struct icl_conn *ic, struct icl_pdu_stailq *queue)
{
	struct icl_pdu *request, *request2;
	struct socket *so;
	long available, size, size2;
	int coalesced, error;

	ICL_CONN_LOCK_ASSERT_NOT(ic);

	so = ic->ic_socket;

	SOCKBUF_LOCK(&so->so_snd);
	/*
	 * Check how much space do we have for transmit.  We can't just
	 * call sosend() and retry when we get EWOULDBLOCK or EMSGSIZE,
	 * as it always frees the mbuf chain passed to it, even in case
	 * of error.
	 */
	available = sbspace(&so->so_snd);

	/*
	 * Notify the socket upcall that we don't need wakeups
	 * for the time being.
	 */
	so->so_snd.sb_lowat = so->so_snd.sb_hiwat + 1;
	SOCKBUF_UNLOCK(&so->so_snd);

	while (!STAILQ_EMPTY(queue)) {
		request = STAILQ_FIRST(queue);
		size = icl_pdu_size(request);
		if (available < size) {

			/*
			 * Set the low watermark, to be checked by
			 * sowriteable() in icl_soupcall_send()
			 * to avoid unnecessary wakeups until there
			 * is enough space for the PDU to fit.
			 */
			SOCKBUF_LOCK(&so->so_snd);
			available = sbspace(&so->so_snd);
			if (available < size) {
#if 1
				ICL_DEBUG("no space to send; "
				    "have %ld, need %ld",
				    available, size);
#endif
				so->so_snd.sb_lowat = size;
				SOCKBUF_UNLOCK(&so->so_snd);
				return;
			}
			SOCKBUF_UNLOCK(&so->so_snd);
		}
		STAILQ_REMOVE_HEAD(queue, ip_next);
		error = icl_pdu_finalize(request);
		if (error != 0) {
			ICL_DEBUG("failed to finalize PDU; "
			    "dropping connection");
			icl_soft_conn_pdu_free(ic, request);
			icl_conn_fail(ic);
			return;
		}
		if (coalesce) {
			coalesced = 1;
			for (;;) {
				request2 = STAILQ_FIRST(queue);
				if (request2 == NULL)
					break;
				size2 = icl_pdu_size(request2);
				if (available < size + size2)
					break;
				STAILQ_REMOVE_HEAD(queue, ip_next);
				error = icl_pdu_finalize(request2);
				if (error != 0) {
					ICL_DEBUG("failed to finalize PDU; "
					    "dropping connection");
					icl_soft_conn_pdu_free(ic, request);
					icl_soft_conn_pdu_free(ic, request2);
					icl_conn_fail(ic);
					return;
				}
				m_cat(request->ip_bhs_mbuf, request2->ip_bhs_mbuf);
				request2->ip_bhs_mbuf = NULL;
				request->ip_bhs_mbuf->m_pkthdr.len += size2;
				size += size2;
				STAILQ_REMOVE_AFTER(queue, request, ip_next);
				icl_soft_conn_pdu_free(ic, request2);
				coalesced++;
			}
#if 0
			if (coalesced > 1) {
				ICL_DEBUG("coalesced %d PDUs into %ld bytes",
				    coalesced, size);
			}
#endif
		}
		available -= size;
		error = sosend(so, NULL, NULL, request->ip_bhs_mbuf,
		    NULL, MSG_DONTWAIT, curthread);
		request->ip_bhs_mbuf = NULL; /* Sosend consumes the mbuf. */
		if (error != 0) {
			ICL_DEBUG("failed to send PDU, error %d; "
			    "dropping connection", error);
			icl_soft_conn_pdu_free(ic, request);
			icl_conn_fail(ic);
			return;
		}
		icl_soft_conn_pdu_free(ic, request);
	}
}