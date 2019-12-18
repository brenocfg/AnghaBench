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
typedef  scalar_t__ uint32_t ;
struct sockbuf {struct mbuf* sb_sndptr; int /*<<< orphan*/  sb_sndptroff; } ;
struct mbuf {scalar_t__ m_len; struct mbuf* m_next; } ;

/* Variables and functions */

void
sbsndptr_adv(struct sockbuf *sb, struct mbuf *mb, uint32_t len)
{
	/*
	 * A small copy was done, advance forward the sb_sbsndptr to cover
	 * it.
	 */
	struct mbuf *m;

	if (mb != sb->sb_sndptr) {
		/* Did not copyout at the same mbuf */
		return;
	}
	m = mb;
	while (m && (len > 0)) {
		if (len >= m->m_len) {
			len -= m->m_len;
			if (m->m_next) {
				sb->sb_sndptroff += m->m_len;
				sb->sb_sndptr = m->m_next;
			}
			m = m->m_next;
		} else {
			len = 0;
		}
	}
}