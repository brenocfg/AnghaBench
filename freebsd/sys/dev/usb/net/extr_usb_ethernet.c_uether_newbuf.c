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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct mbuf {TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ALIGN ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct mbuf *
uether_newbuf(void)
{
	struct mbuf *m_new;

	m_new = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
	if (m_new == NULL)
		return (NULL);
	m_new->m_len = m_new->m_pkthdr.len = MCLBYTES;

	m_adj(m_new, ETHER_ALIGN);
	return (m_new);
}