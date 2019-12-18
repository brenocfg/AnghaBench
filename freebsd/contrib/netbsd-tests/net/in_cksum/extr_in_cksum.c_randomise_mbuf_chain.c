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
struct mbuf {int m_len; struct mbuf* m_next; scalar_t__ m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 int rand () ; 

__attribute__((used)) static void
randomise_mbuf_chain(struct mbuf *m)
{
	int i, data, len;

	for (i = 0; i < m->m_len; i += sizeof(int)) {
		data = rand();
		if (i + sizeof(int) < (size_t)m->m_len)
			len = sizeof(int);
		else
			len = m->m_len - i;
		memcpy(m->m_data + i, &data, len);
	}
	if (m->m_next)
		randomise_mbuf_chain(m->m_next);
}