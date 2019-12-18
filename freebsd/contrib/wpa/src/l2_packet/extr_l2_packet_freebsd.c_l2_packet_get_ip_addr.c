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
struct sockaddr_in {scalar_t__ sin_family; int /*<<< orphan*/  sin_addr; } ;
struct pcap_addr {struct pcap_addr* next; scalar_t__ addr; } ;
struct l2_packet_data {int /*<<< orphan*/  ifname; } ;
struct TYPE_4__ {struct pcap_addr* addresses; int /*<<< orphan*/  name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ pcap_if_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ pcap_findalldevs (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  pcap_freealldevs (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

int l2_packet_get_ip_addr(struct l2_packet_data *l2, char *buf, size_t len)
{
	pcap_if_t *devs, *dev;
	struct pcap_addr *addr;
	struct sockaddr_in *saddr;
	int found = 0;
	char err[PCAP_ERRBUF_SIZE + 1];

	if (pcap_findalldevs(&devs, err) < 0) {
		wpa_printf(MSG_DEBUG, "pcap_findalldevs: %s\n", err);
		return -1;
	}

	for (dev = devs; dev && !found; dev = dev->next) {
		if (os_strcmp(dev->name, l2->ifname) != 0)
			continue;

		addr = dev->addresses;
		while (addr) {
			saddr = (struct sockaddr_in *) addr->addr;
			if (saddr && saddr->sin_family == AF_INET) {
				os_strlcpy(buf, inet_ntoa(saddr->sin_addr),
					   len);
				found = 1;
				break;
			}
			addr = addr->next;
		}
	}

	pcap_freealldevs(devs);

	return found ? 0 : -1;
}