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
struct mbuf {struct mbuf* m_next; scalar_t__ m_len; } ;
struct mbchain {struct mbuf* mb_cur; int /*<<< orphan*/  mb_mleft; int /*<<< orphan*/  mb_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TRAILINGSPACE (struct mbuf*) ; 

int
mb_put_mbuf(struct mbchain *mbp, struct mbuf *m)
{
	mbp->mb_cur->m_next = m;
	while (m) {
		mbp->mb_count += m->m_len;
		if (m->m_next == NULL)
			break;
		m = m->m_next;
	}
	mbp->mb_mleft = M_TRAILINGSPACE(m);
	mbp->mb_cur = m;
	return (0);
}