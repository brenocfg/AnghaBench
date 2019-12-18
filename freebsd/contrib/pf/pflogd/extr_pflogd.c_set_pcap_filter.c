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
struct bpf_program {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PCAP_OPT_FIL ; 
 int /*<<< orphan*/  filter ; 
 int /*<<< orphan*/  hpcap ; 
 int /*<<< orphan*/  logmsg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pcap_compile (int /*<<< orphan*/ ,struct bpf_program*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_freecode (struct bpf_program*) ; 
 int /*<<< orphan*/  pcap_geterr (int /*<<< orphan*/ ) ; 
 scalar_t__ pcap_setfilter (int /*<<< orphan*/ ,struct bpf_program*) ; 

void
set_pcap_filter(void)
{
	struct bpf_program bprog;

	if (pcap_compile(hpcap, &bprog, filter, PCAP_OPT_FIL, 0) < 0)
		logmsg(LOG_WARNING, "%s", pcap_geterr(hpcap));
	else {
		if (pcap_setfilter(hpcap, &bprog) < 0)
			logmsg(LOG_WARNING, "%s", pcap_geterr(hpcap));
		pcap_freecode(&bprog);
	}
}