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
struct pcap_pkthdr {int dummy; } ;
struct oneshot_userdata {int /*<<< orphan*/  const** pkt; struct pcap_pkthdr* hdr; } ;

/* Variables and functions */

void
pcap_oneshot(u_char *user, const struct pcap_pkthdr *h, const u_char *pkt)
{
	struct oneshot_userdata *sp = (struct oneshot_userdata *)user;

	*sp->hdr = *h;
	*sp->pkt = pkt;
}