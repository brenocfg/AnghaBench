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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int sb_lowat; int sb_hiwat; } ;
struct socket {TYPE_1__ so_rcv; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;
struct cf_conn {int resid; int eor; struct mbuf* mpending; struct mbuf* mreq; } ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_7__ {struct mbuf* m_next; } ;
struct TYPE_6__ {struct socket* xp_socket; scalar_t__ xp_p1; } ;
typedef  TYPE_2__ SVCXPRT ;

/* Variables and functions */
 int FALSE ; 
 int INT_MAX ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int TRUE ; 
 int imax (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imin (scalar_t__,int) ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,char*) ; 
 TYPE_4__* m_last (struct mbuf*) ; 
 struct mbuf* m_split (struct mbuf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 

__attribute__((used)) static int
svc_vc_process_pending(SVCXPRT *xprt)
{
	struct cf_conn *cd = (struct cf_conn *) xprt->xp_p1;
	struct socket *so = xprt->xp_socket;
	struct mbuf *m;

	/*
	 * If cd->resid is non-zero, we have part of the
	 * record already, otherwise we are expecting a record
	 * marker.
	 */
	if (!cd->resid && cd->mpending) {
		/*
		 * See if there is enough data buffered to
		 * make up a record marker. Make sure we can
		 * handle the case where the record marker is
		 * split across more than one mbuf.
		 */
		size_t n = 0;
		uint32_t header;

		m = cd->mpending;
		while (n < sizeof(uint32_t) && m) {
			n += m->m_len;
			m = m->m_next;
		}
		if (n < sizeof(uint32_t)) {
			so->so_rcv.sb_lowat = sizeof(uint32_t) - n;
			return (FALSE);
		}
		m_copydata(cd->mpending, 0, sizeof(header),
		    (char *)&header);
		header = ntohl(header);
		cd->eor = (header & 0x80000000) != 0;
		cd->resid = header & 0x7fffffff;
		m_adj(cd->mpending, sizeof(uint32_t));
	}

	/*
	 * Start pulling off mbufs from cd->mpending
	 * until we either have a complete record or
	 * we run out of data. We use m_split to pull
	 * data - it will pull as much as possible and
	 * split the last mbuf if necessary.
	 */
	while (cd->mpending && cd->resid) {
		m = cd->mpending;
		if (cd->mpending->m_next
		    || cd->mpending->m_len > cd->resid)
			cd->mpending = m_split(cd->mpending,
			    cd->resid, M_WAITOK);
		else
			cd->mpending = NULL;
		if (cd->mreq)
			m_last(cd->mreq)->m_next = m;
		else
			cd->mreq = m;
		while (m) {
			cd->resid -= m->m_len;
			m = m->m_next;
		}
	}

	/*
	 * Block receive upcalls if we have more data pending,
	 * otherwise report our need.
	 */
	if (cd->mpending)
		so->so_rcv.sb_lowat = INT_MAX;
	else
		so->so_rcv.sb_lowat =
		    imax(1, imin(cd->resid, so->so_rcv.sb_hiwat / 2));
	return (TRUE);
}