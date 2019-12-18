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
struct pcap_stat {int /*<<< orphan*/  ps_ifdrop; int /*<<< orphan*/  ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct bpf_stat {int /*<<< orphan*/  ps_ifdrop; int /*<<< orphan*/  bs_drop; int /*<<< orphan*/  bs_recv; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PacketGetStats (int /*<<< orphan*/ ,struct bpf_stat*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_stats_npf(pcap_t *p, struct pcap_stat *ps)
{
	struct pcap_win *pw = p->priv;
	struct bpf_stat bstats;
	char errbuf[PCAP_ERRBUF_SIZE+1];

	/*
	 * Try to get statistics.
	 *
	 * (Please note - "struct pcap_stat" is *not* the same as
	 * WinPcap's "struct bpf_stat". It might currently have the
	 * same layout, but let's not cheat.
	 *
	 * Note also that we don't fill in ps_capt, as we might have
	 * been called by code compiled against an earlier version of
	 * WinPcap that didn't have ps_capt, in which case filling it
	 * in would stomp on whatever comes after the structure passed
	 * to us.
	 */
	if (!PacketGetStats(pw->adapter, &bstats)) {
		pcap_win32_err_to_str(GetLastError(), errbuf);
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "PacketGetStats error: %s", errbuf);
		return (-1);
	}
	ps->ps_recv = bstats.bs_recv;
	ps->ps_drop = bstats.bs_drop;

	/*
	 * XXX - PacketGetStats() doesn't fill this in, so we just
	 * return 0.
	 */
#if 0
	ps->ps_ifdrop = bstats.ps_ifdrop;
#else
	ps->ps_ifdrop = 0;
#endif

	return (0);
}