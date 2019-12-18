#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; int /*<<< orphan*/  len; } ;
struct bpf_insn {int dummy; } ;
struct TYPE_5__ {struct bpf_insn* bf_insns; } ;
struct TYPE_6__ {int (* next_packet_op ) (TYPE_2__*,struct pcap_pkthdr*,int /*<<< orphan*/ **) ;TYPE_1__ fcode; scalar_t__ break_loop; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ bpf_filter (struct bpf_insn*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,struct pcap_pkthdr*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

int
pcap_offline_read(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct bpf_insn *fcode;
	int status = 0;
	int n = 0;
	u_char *data;

	while (status == 0) {
		struct pcap_pkthdr h;

		/*
		 * Has "pcap_breakloop()" been called?
		 * If so, return immediately - if we haven't read any
		 * packets, clear the flag and return -2 to indicate
		 * that we were told to break out of the loop, otherwise
		 * leave the flag set, so that the *next* call will break
		 * out of the loop without having read any packets, and
		 * return the number of packets we've processed so far.
		 */
		if (p->break_loop) {
			if (n == 0) {
				p->break_loop = 0;
				return (-2);
			} else
				return (n);
		}

		status = p->next_packet_op(p, &h, &data);
		if (status) {
			if (status == 1)
				return (0);
			return (status);
		}

		if ((fcode = p->fcode.bf_insns) == NULL ||
		    bpf_filter(fcode, data, h.len, h.caplen)) {
			(*callback)(user, &h, data);
			if (++n >= cnt && cnt > 0)
				break;
		}
	}
	/*XXX this breaks semantics tcpslice expects */
	return (n);
}