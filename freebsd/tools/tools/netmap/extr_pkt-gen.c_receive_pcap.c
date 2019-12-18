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
struct pcap_pkthdr {scalar_t__ len; } ;
struct my_ctrs {int /*<<< orphan*/  pkts; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */

__attribute__((used)) static void
receive_pcap(u_char *user, const struct pcap_pkthdr * h,
	const u_char * bytes)
{
	struct my_ctrs *ctr = (struct my_ctrs *)user;
	(void)bytes;	/* UNUSED */
	ctr->bytes += h->len;
	ctr->pkts++;
}