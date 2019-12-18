#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; int /*<<< orphan*/  len; } ;
struct pcap_netmap {int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb ) (int /*<<< orphan*/ ,struct pcap_pkthdr*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  rx_pkts; } ;
struct bpf_insn {int dummy; } ;
struct TYPE_3__ {struct bpf_insn* bf_insns; } ;
struct TYPE_4__ {TYPE_1__ fcode; struct pcap_netmap* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 scalar_t__ bpf_filter (struct bpf_insn const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct pcap_pkthdr*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
pcap_netmap_filter(u_char *arg, struct pcap_pkthdr *h, const u_char *buf)
{
	pcap_t *p = (pcap_t *)arg;
	struct pcap_netmap *pn = p->priv;
	const struct bpf_insn *pc = p->fcode.bf_insns;

	++pn->rx_pkts;
	if (pc == NULL || bpf_filter(pc, buf, h->len, h->caplen))
		pn->cb(pn->cb_arg, h, buf);
}