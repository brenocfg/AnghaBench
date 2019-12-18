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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; int /*<<< orphan*/  len; } ;
struct bpf_program {struct bpf_insn* bf_insns; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int bpf_filter (struct bpf_insn const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
pcap_offline_filter(const struct bpf_program *fp, const struct pcap_pkthdr *h,
    const u_char *pkt)
{
	const struct bpf_insn *fcode = fp->bf_insns;

	if (fcode != NULL)
		return (bpf_filter(fcode, pkt, h->len, h->caplen));
	else
		return (0);
}