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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int dummy; } ;
struct oneshot_userdata {TYPE_1__* pd; int /*<<< orphan*/  const** pkt; struct pcap_pkthdr* hdr; } ;
struct TYPE_4__ {int /*<<< orphan*/  oneshot_callback; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ pcap_dispatch (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const u_char *
pcap_next(pcap_t *p, struct pcap_pkthdr *h)
{
	struct oneshot_userdata s;
	const u_char *pkt;

	s.hdr = h;
	s.pkt = &pkt;
	s.pd = p;
	if (pcap_dispatch(p, 1, p->oneshot_callback, (u_char *)&s) <= 0)
		return (0);
	return (pkt);
}