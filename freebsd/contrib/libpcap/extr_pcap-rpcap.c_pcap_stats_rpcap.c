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
struct pcap_stat {int dummy; } ;
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_STATS_STANDARD ; 
 struct pcap_stat* rpcap_stats_rpcap (int /*<<< orphan*/ *,struct pcap_stat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_stats_rpcap(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_stat *retval;

	retval = rpcap_stats_rpcap(p, ps, PCAP_STATS_STANDARD);

	if (retval)
		return 0;
	else
		return -1;
}