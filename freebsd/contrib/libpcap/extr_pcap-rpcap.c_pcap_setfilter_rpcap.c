#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcap_rpcap {int /*<<< orphan*/  rmt_capstarted; } ;
struct bpf_program {int dummy; } ;
struct TYPE_5__ {struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int install_bpf_program (TYPE_1__*,struct bpf_program*) ; 
 scalar_t__ pcap_updatefilter_remote (TYPE_1__*,struct bpf_program*) ; 

__attribute__((used)) static int pcap_setfilter_rpcap(pcap_t *fp, struct bpf_program *prog)
{
	struct pcap_rpcap *pr = fp->priv;	/* structure used when doing a remote live capture */

	if (!pr->rmt_capstarted)
	{
		/* copy filter into the pcap_t structure */
		if (install_bpf_program(fp, prog) == -1)
			return -1;
		return 0;
	}

	/* we have to update a filter during run-time */
	if (pcap_updatefilter_remote(fp, prog))
		return -1;

	return 0;
}