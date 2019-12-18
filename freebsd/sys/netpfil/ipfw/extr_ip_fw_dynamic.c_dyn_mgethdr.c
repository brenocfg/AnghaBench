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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int len; } ;
struct mbuf {int m_len; int /*<<< orphan*/  m_data; TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_SETFIB (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_SKIP_FIREWALL ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 struct mbuf* m_gethdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_netinet_firewall_send (struct mbuf*) ; 
 scalar_t__ max_linkhdr ; 

__attribute__((used)) static struct mbuf *
dyn_mgethdr(int len, uint16_t fibnum)
{
	struct mbuf *m;

	m = m_gethdr(M_NOWAIT, MT_DATA);
	if (m == NULL)
		return (NULL);
#ifdef MAC
	mac_netinet_firewall_send(m);
#endif
	M_SETFIB(m, fibnum);
	m->m_data += max_linkhdr;
	m->m_flags |= M_SKIP_FIREWALL;
	m->m_len = m->m_pkthdr.len = len;
	bzero(m->m_data, len);
	return (m);
}