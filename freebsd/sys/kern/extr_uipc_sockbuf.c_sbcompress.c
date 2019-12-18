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
struct sockbuf {int sb_flags; int sb_ccc; int sb_acc; int sb_ctl; struct mbuf* sb_mbtail; struct mbuf* sb_mb; int /*<<< orphan*/ * sb_fnrdy; struct mbuf* sb_lastrecord; } ;
struct mbuf {int m_flags; int m_len; scalar_t__ m_type; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int MCLBYTES ; 
 int MLEN ; 
 scalar_t__ MT_DATA ; 
 scalar_t__ MT_OOBDATA ; 
 int M_EOR ; 
 int M_NOMAP ; 
 int M_NOTREADY ; 
 int M_TRAILINGSPACE (struct mbuf*) ; 
 scalar_t__ M_WRITABLE (struct mbuf*) ; 
 int /*<<< orphan*/  SBLASTMBUFCHK (struct sockbuf*) ; 
 int SB_NOCOALESCE ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_free (struct mbuf*) ; 
 int /*<<< orphan*/  mb_unmapped_compress (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_has_tls_session (struct mbuf*) ; 
 int /*<<< orphan*/  mtodo (struct mbuf*,int) ; 
 int /*<<< orphan*/  sballoc (struct sockbuf*,struct mbuf*) ; 

void
sbcompress(struct sockbuf *sb, struct mbuf *m, struct mbuf *n)
{
	int eor = 0;
	struct mbuf *o;

	SOCKBUF_LOCK_ASSERT(sb);

	while (m) {
		eor |= m->m_flags & M_EOR;
		if (m->m_len == 0 &&
		    (eor == 0 ||
		     (((o = m->m_next) || (o = n)) &&
		      o->m_type == m->m_type))) {
			if (sb->sb_lastrecord == m)
				sb->sb_lastrecord = m->m_next;
			m = m_free(m);
			continue;
		}
		if (n && (n->m_flags & M_EOR) == 0 &&
		    M_WRITABLE(n) &&
		    ((sb->sb_flags & SB_NOCOALESCE) == 0) &&
		    !(m->m_flags & M_NOTREADY) &&
		    !(n->m_flags & (M_NOTREADY | M_NOMAP)) &&
		    !mbuf_has_tls_session(m) &&
		    !mbuf_has_tls_session(n) &&
		    m->m_len <= MCLBYTES / 4 && /* XXX: Don't copy too much */
		    m->m_len <= M_TRAILINGSPACE(n) &&
		    n->m_type == m->m_type) {
			m_copydata(m, 0, m->m_len, mtodo(n, n->m_len));
			n->m_len += m->m_len;
			sb->sb_ccc += m->m_len;
			if (sb->sb_fnrdy == NULL)
				sb->sb_acc += m->m_len;
			if (m->m_type != MT_DATA && m->m_type != MT_OOBDATA)
				/* XXX: Probably don't need.*/
				sb->sb_ctl += m->m_len;
			m = m_free(m);
			continue;
		}
		if (m->m_len <= MLEN && (m->m_flags & M_NOMAP) &&
		    (m->m_flags & M_NOTREADY) == 0 &&
		    !mbuf_has_tls_session(m))
			(void)mb_unmapped_compress(m);
		if (n)
			n->m_next = m;
		else
			sb->sb_mb = m;
		sb->sb_mbtail = m;
		sballoc(sb, m);
		n = m;
		m->m_flags &= ~M_EOR;
		m = m->m_next;
		n->m_next = 0;
	}
	if (eor) {
		KASSERT(n != NULL, ("sbcompress: eor && n == NULL"));
		n->m_flags |= eor;
	}
	SBLASTMBUFCHK(sb);
}