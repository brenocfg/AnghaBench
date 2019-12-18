#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pcap_snf {int snf_timeout; } ;
struct TYPE_4__ {int timeout; } ;
struct TYPE_5__ {TYPE_1__ opt; struct pcap_snf* priv; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */

__attribute__((used)) static int
snf_setnonblock(pcap_t *p, int nonblock)
{
	struct pcap_snf *ps = p->priv;

	if (nonblock)
		ps->snf_timeout = 0;
	else {
		if (p->opt.timeout <= 0)
			ps->snf_timeout = -1; /* forever */
		else
			ps->snf_timeout = p->opt.timeout;
	}
	return (0);
}