#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct pcap_win {int /*<<< orphan*/ * adapter; } ;
struct TYPE_5__ {int /*<<< orphan*/  errbuf; struct pcap_win* priv; } ;
typedef  TYPE_1__ pcap_t ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_2__ pcap_send_queue ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PacketSendPackets (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcap_win32_err_to_str (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u_int
pcap_sendqueue_transmit_npf(pcap_t *p, pcap_send_queue *queue, int sync)
{
	struct pcap_win *pw = p->priv;
	u_int res;
	char errbuf[PCAP_ERRBUF_SIZE+1];

	if (pw->adapter==NULL) {
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Cannot transmit a queue to an offline capture or to a TurboCap port");
		return (0);
	}

	res = PacketSendPackets(pw->adapter,
		queue->buffer,
		queue->len,
		(BOOLEAN)sync);

	if(res != queue->len){
		pcap_win32_err_to_str(GetLastError(), errbuf);
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Error opening adapter: %s", errbuf);
	}

	return (res);
}