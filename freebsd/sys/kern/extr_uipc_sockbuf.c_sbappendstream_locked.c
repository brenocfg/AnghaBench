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
struct sockbuf {scalar_t__ sb_mb; scalar_t__ sb_lastrecord; int /*<<< orphan*/  sb_mbtail; int /*<<< orphan*/ * sb_tls_info; } ;
struct mbuf {int /*<<< orphan*/ * m_nextpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_NOTREADY ; 
 int PRUS_NOTREADY ; 
 int /*<<< orphan*/  SBLASTMBUFCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SBLASTRECORDCHK (struct sockbuf*) ; 
 int /*<<< orphan*/  SOCKBUF_LOCK_ASSERT (struct sockbuf*) ; 
 int /*<<< orphan*/  ktls_seq (struct sockbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_demote (struct mbuf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbcompress (struct sockbuf*,struct mbuf*,int /*<<< orphan*/ ) ; 

void
sbappendstream_locked(struct sockbuf *sb, struct mbuf *m, int flags)
{
	SOCKBUF_LOCK_ASSERT(sb);

	KASSERT(m->m_nextpkt == NULL,("sbappendstream 0"));
	KASSERT(sb->sb_mb == sb->sb_lastrecord,("sbappendstream 1"));

	SBLASTMBUFCHK(sb);

#ifdef KERN_TLS
	if (sb->sb_tls_info != NULL)
		ktls_seq(sb, m);
#endif

	/* Remove all packet headers and mbuf tags to get a pure data chain. */
	m_demote(m, 1, flags & PRUS_NOTREADY ? M_NOTREADY : 0);

	sbcompress(sb, m, sb->sb_mbtail);

	sb->sb_lastrecord = sb->sb_mb;
	SBLASTRECORDCHK(sb);
}