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

/* Variables and functions */

__attribute__((used)) static size_t
m_totlen(struct mbuf *m0)
{
	struct mbuf *m = m0;
	int len = 0;

	while (m) {
		len += m->m_len;
		m = m->m_next;
	}
	return len;
}