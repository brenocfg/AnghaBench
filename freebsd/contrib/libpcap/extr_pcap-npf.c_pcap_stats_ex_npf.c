#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_win {int /*<<< orphan*/  adapter; } ;
struct pcap_stat {int /*<<< orphan*/  ps_capt; int /*<<< orphan*/  ps_ifdrop; int /*<<< orphan*/  ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct bpf_stat {int /*<<< orphan*/  bs_capt; int /*<<< orphan*/  ps_ifdrop; int /*<<< orphan*/  bs_drop; int /*<<< orphan*/  bs_recv; } ;
struct TYPE_3__ {struct pcap_stat stat; int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PacketGetStatsEx (int /*<<< orphan*/ ,struct bpf_stat*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 

struct pcap_stat *
pcap_stats_ex_npf(pcap_t *p, int *pcap_stat_size)
{
	struct pcap_win *pw = p->priv;
	struct bpf_stat bstats;
	char errbuf[PCAP_ERRBUF_SIZE+1];

	*pcap_stat_size = sizeof (p->stat);

	/*
	 * Try to get statistics.
	 *
	 * (Please note - "struct pcap_stat" is *not* the same as
	 * WinPcap's "struct bpf_stat". It might currently have the
	 * same layout, but let's not cheat.)
	 */
	if (!PacketGetStatsEx(pw->adapter, &bstats)) {
		pcap_win32_err_to_str(GetLastError(), errbuf);
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "PacketGetStatsEx error: %s", errbuf);
		return (NULL);
	}
	p->stat.ps_recv = bstats.bs_recv;
	p->stat.ps_drop = bstats.bs_drop;
	p->stat.ps_ifdrop = bstats.ps_ifdrop;
#ifdef ENABLE_REMOTE
	p->stat.ps_capt = bstats.bs_capt;
#endif
	return (&p->stat);
}