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
typedef  int /*<<< orphan*/  pcap_dumper_t ;

/* Variables and functions */
 scalar_t__ Uflag ; 
 int /*<<< orphan*/  info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infodelay ; 
 scalar_t__ infoprint ; 
 int /*<<< orphan*/  packets_captured ; 
 int /*<<< orphan*/  pcap_dump (int /*<<< orphan*/ *,struct pcap_pkthdr const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pcap_dump_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dump_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *sp)
{
	++packets_captured;

	++infodelay;

	pcap_dump(user, h, sp);
#ifdef HAVE_PCAP_DUMP_FLUSH
	if (Uflag)
		pcap_dump_flush((pcap_dumper_t *)user);
#endif

	--infodelay;
	if (infoprint)
		info(0);
}