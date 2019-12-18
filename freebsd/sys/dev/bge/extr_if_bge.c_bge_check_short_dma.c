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
struct mbuf {int m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 struct mbuf* m_defrag (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static struct mbuf *
bge_check_short_dma(struct mbuf *m)
{
	struct mbuf *n;
	int found;

	/*
	 * If device receive two back-to-back send BDs with less than
	 * or equal to 8 total bytes then the device may hang.  The two
	 * back-to-back send BDs must in the same frame for this failure
	 * to occur.  Scan mbuf chains and see whether two back-to-back
	 * send BDs are there. If this is the case, allocate new mbuf
	 * and copy the frame to workaround the silicon bug.
	 */
	for (n = m, found = 0; n != NULL; n = n->m_next) {
		if (n->m_len < 8) {
			found++;
			if (found > 1)
				break;
			continue;
		}
		found = 0;
	}

	if (found > 1) {
		n = m_defrag(m, M_NOWAIT);
		if (n == NULL)
			m_freem(m);
	} else
		n = m;
	return (n);
}