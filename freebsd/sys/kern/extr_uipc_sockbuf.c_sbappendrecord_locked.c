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
struct sockbuf {struct mbuf* sb_mbtail; } ;
struct mbuf {int m_flags; struct mbuf* m_next; } ;

/* Variables and functions */
 int M_EOR ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLINKRECORD (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  m_clrprotoflags (struct mbuf*) ; 
 int /*<<< orphan*/  sballoc (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  sbcompress (struct sockbuf*,struct mbuf*,struct mbuf*) ; 

void
sbappendrecord_locked(struct sockbuf *sb, struct mbuf *m0)
{
	struct mbuf *m;

	SOCKBUF_LOCK_ASSERT(sb);

	if (m0 == NULL)
		return;
	m_clrprotoflags(m0);
	/*
	 * Put the first mbuf on the queue.  Note this permits zero length
	 * records.
	 */
	sballoc(sb, m0);
	SBLASTRECORDCHK(sb);
	SBLINKRECORD(sb, m0);
	sb->sb_mbtail = m0;
	m = m0->m_next;
	m0->m_next = 0;
	if (m && (m0->m_flags & M_EOR)) {
		m0->m_flags &= ~M_EOR;
		m->m_flags |= M_EOR;
	}
	/* always call sbcompress() so it can do SBLASTMBUFCHK() */
	sbcompress(sb, m, m0);
}