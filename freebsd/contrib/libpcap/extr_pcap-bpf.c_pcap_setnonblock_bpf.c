#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_bpf {int nonblock; scalar_t__ zerocopy; } ;
struct TYPE_4__ {struct pcap_bpf* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int pcap_setnonblock_fd (TYPE_1__*,int) ; 

__attribute__((used)) static int
pcap_setnonblock_bpf(pcap_t *p, int nonblock)
{
#ifdef HAVE_ZEROCOPY_BPF
	struct pcap_bpf *pb = p->priv;

	if (pb->zerocopy) {
		pb->nonblock = nonblock;
		return (0);
	}
#endif
	return (pcap_setnonblock_fd(p, nonblock));
}