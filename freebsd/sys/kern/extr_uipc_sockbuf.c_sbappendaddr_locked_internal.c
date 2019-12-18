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
struct sockbuf {struct mbuf* sb_mbtail; } ;
struct sockaddr {scalar_t__ sa_len; } ;
struct TYPE_2__ {scalar_t__ rsstype; scalar_t__ fibnum; scalar_t__ csum_flags; scalar_t__ flowid; int /*<<< orphan*/ * rcvif; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 scalar_t__ MLEN ; 
 int /*<<< orphan*/  MT_SONAME ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  SBLASTMBUFCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLINKRECORD (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (struct sockaddr const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  m_clrprotoflags (struct mbuf*) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sballoc (struct sockbuf*,struct mbuf*) ; 

__attribute__((used)) static int
sbappendaddr_locked_internal(struct sockbuf *sb, const struct sockaddr *asa,
    struct mbuf *m0, struct mbuf *control, struct mbuf *ctrl_last)
{
	struct mbuf *m, *n, *nlast;
#if MSIZE <= 256
	if (asa->sa_len > MLEN)
		return (0);
#endif
	m = m_get(M_NOWAIT, MT_SONAME);
	if (m == NULL)
		return (0);
	m->m_len = asa->sa_len;
	bcopy(asa, mtod(m, caddr_t), asa->sa_len);
	if (m0) {
		m_clrprotoflags(m0);
		m_tag_delete_chain(m0, NULL);
		/*
		 * Clear some persistent info from pkthdr.
		 * We don't use m_demote(), because some netgraph consumers
		 * expect M_PKTHDR presence.
		 */
		m0->m_pkthdr.rcvif = NULL;
		m0->m_pkthdr.flowid = 0;
		m0->m_pkthdr.csum_flags = 0;
		m0->m_pkthdr.fibnum = 0;
		m0->m_pkthdr.rsstype = 0;
	}
	if (ctrl_last)
		ctrl_last->m_next = m0;	/* concatenate data to control */
	else
		control = m0;
	m->m_next = control;
	for (n = m; n->m_next != NULL; n = n->m_next)
		sballoc(sb, n);
	sballoc(sb, n);
	nlast = n;
	SBLINKRECORD(sb, m);

	sb->sb_mbtail = nlast;
	SBLASTMBUFCHK(sb);

	SBLASTRECORDCHK(sb);
	return (1);
}