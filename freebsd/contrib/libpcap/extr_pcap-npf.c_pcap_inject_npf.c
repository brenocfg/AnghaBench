#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcap_win {int /*<<< orphan*/  adapter; } ;
struct TYPE_3__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PacketInitPacket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ PacketSendPacket (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
pcap_inject_npf(pcap_t *p, const void *buf, size_t size)
{
	struct pcap_win *pw = p->priv;
	PACKET pkt;

	PacketInitPacket(&pkt, (PVOID)buf, size);
	if(PacketSendPacket(pw->adapter,&pkt,TRUE) == FALSE) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE, "send error: PacketSendPacket failed");
		return (-1);
	}

	/*
	 * We assume it all got sent if "PacketSendPacket()" succeeded.
	 * "pcap_inject()" is expected to return the number of bytes
	 * sent.
	 */
	return ((int)size);
}