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
struct mbuf {int m_flags; struct mbuf* m_next; } ;

/* Variables and functions */
 int M_EXT ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_pcap_clusters_referenced_cur ; 

__attribute__((used)) static __inline void
tcp_pcap_adj_cluster_reference(struct mbuf *m, int adj)
{
	while (m) {
		if (m->m_flags & M_EXT)
			atomic_add_int(&tcp_pcap_clusters_referenced_cur, adj);

		m = m->m_next;
	}
}