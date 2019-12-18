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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infodelay ; 
 scalar_t__ infoprint ; 
 int /*<<< orphan*/  packets_captured ; 
 int /*<<< orphan*/  pretty_print_packet (int /*<<< orphan*/ *,struct pcap_pkthdr const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *sp)
{
	++packets_captured;

	++infodelay;

	pretty_print_packet((netdissect_options *)user, h, sp, packets_captured);

	--infodelay;
	if (infoprint)
		info(0);
}