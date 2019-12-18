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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_pcap_clusters_referenced_cur ; 
 scalar_t__ tcp_pcap_clusters_referenced_max ; 

__attribute__((used)) static __inline bool
tcp_pcap_take_cluster_reference(void)
{
	if (atomic_fetchadd_int(&tcp_pcap_clusters_referenced_cur, 1) >=
		tcp_pcap_clusters_referenced_max) {
		atomic_add_int(&tcp_pcap_clusters_referenced_cur, -1);
		return FALSE;
	}
	return TRUE;
}