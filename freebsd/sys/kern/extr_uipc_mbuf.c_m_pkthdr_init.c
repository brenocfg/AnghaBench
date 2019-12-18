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
struct TYPE_2__ {int /*<<< orphan*/  numa_domain; } ;
struct mbuf {TYPE_1__ m_pkthdr; int /*<<< orphan*/  m_pktdat; int /*<<< orphan*/  m_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NODOM ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int mac_mbuf_init (struct mbuf*,int) ; 

int
m_pkthdr_init(struct mbuf *m, int how)
{
#ifdef MAC
	int error;
#endif
	m->m_data = m->m_pktdat;
	bzero(&m->m_pkthdr, sizeof(m->m_pkthdr));
#ifdef NUMA
	m->m_pkthdr.numa_domain = M_NODOM;
#endif
#ifdef MAC
	/* If the label init fails, fail the alloc */
	error = mac_mbuf_init(m, how);
	if (error)
		return (error);
#endif

	return (0);
}