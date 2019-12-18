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
struct pcap_pkthdr {int caplen; } ;
struct pcap_handler_data {int len; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void handler(u_char *data, const struct pcap_pkthdr *header,
		    const u_char *packet)
{
	int len;

	struct pcap_handler_data *hdata = (struct pcap_handler_data *) data;

	len = hdata->len < header->caplen ? hdata->len : header->caplen;
	memcpy(hdata->buffer, packet, len);
	hdata->len = len;
}