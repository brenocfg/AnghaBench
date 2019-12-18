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
struct sockbuf {struct mbuf* sb_lastrecord; struct mbuf* sb_mb; } ;
struct mbuf {int m_flags; struct mbuf* m_next; struct mbuf* m_nextpkt; } ;

/* Variables and functions */
 int M_EOR ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  sbappendrecord_locked (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  sbcompress (struct sockbuf*,struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  sbm_clrprotoflags (struct mbuf*,int) ; 

void
sbappend_locked(struct sockbuf *sb, struct mbuf *m, int flags)
{
	struct mbuf *n;

	SOCKBUF_LOCK_ASSERT(sb);

	if (m == NULL)
		return;
	sbm_clrprotoflags(m, flags);
	SBLASTRECORDCHK(sb);
	n = sb->sb_mb;
	if (n) {
		while (n->m_nextpkt)
			n = n->m_nextpkt;
		do {
			if (n->m_flags & M_EOR) {
				sbappendrecord_locked(sb, m); /* XXXXXX!!!! */
				return;
			}
		} while (n->m_next && (n = n->m_next));
	} else {
		/*
		 * XXX Would like to simply use sb_mbtail here, but
		 * XXX I need to verify that I won't miss an EOR that
		 * XXX way.
		 */
		if ((n = sb->sb_lastrecord) != NULL) {
			do {
				if (n->m_flags & M_EOR) {
					sbappendrecord_locked(sb, m); /* XXXXXX!!!! */
					return;
				}
			} while (n->m_next && (n = n->m_next));
		} else {
			/*
			 * If this is the first record in the socket buffer,
			 * it's also the last record.
			 */
			sb->sb_lastrecord = m;
		}
	}
	sbcompress(sb, m, n);
	SBLASTRECORDCHK(sb);
}