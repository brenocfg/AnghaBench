#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct pcap_rpcap {int /*<<< orphan*/  rmt_capstarted; scalar_t__ rmt_clientside; } ;
struct pcap_pkthdr {int dummy; } ;
struct TYPE_5__ {scalar_t__ break_loop; struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ PACKET_COUNT_IS_UNLIMITED (int) ; 
 int PCAP_ERROR_BREAK ; 
 int pcap_read_nocb_remote (TYPE_1__*,struct pcap_pkthdr*,int /*<<< orphan*/ **) ; 
 scalar_t__ pcap_startcapture_remote (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcap_read_rpcap(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_rpcap *pr = p->priv;	/* structure used when doing a remote live capture */
	struct pcap_pkthdr pkt_header;
	u_char *pkt_data;
	int n = 0;
	int ret;

	/*
	 * If this is client-side, and we haven't already started
	 * the capture, start it now.
	 */
	if (pr->rmt_clientside)
	{
		/* We are on an remote capture */
		if (!pr->rmt_capstarted)
		{
			/*
			 * The capture isn't started yet, so try to
			 * start it.
			 */
			if (pcap_startcapture_remote(p))
				return -1;
		}
	}

	while (n < cnt || PACKET_COUNT_IS_UNLIMITED(cnt))
	{
		/*
		 * Has "pcap_breakloop()" been called?
		 */
		if (p->break_loop) {
			/*
			 * Yes - clear the flag that indicates that it
			 * has, and return PCAP_ERROR_BREAK to indicate
			 * that we were told to break out of the loop.
			 */
			p->break_loop = 0;
			return (PCAP_ERROR_BREAK);
		}

		/*
		 * Read some packets.
		 */
		ret = pcap_read_nocb_remote(p, &pkt_header, &pkt_data);
		if (ret == 1)
		{
			/*
			 * We got a packet.  Hand it to the callback
			 * and count it so we can return the count.
			 */
			(*callback)(user, &pkt_header, pkt_data);
			n++;
		}
		else if (ret == -1)
		{
			/* Error. */
			return ret;
		}
		else
		{
			/*
			 * No packet; this could mean that we timed
			 * out, or that we got interrupted, or that
			 * we got a bad packet.
			 *
			 * Were we told to break out of the loop?
			 */
			if (p->break_loop) {
				/*
				 * Yes.
				 */
				p->break_loop = 0;
				return (PCAP_ERROR_BREAK);
			}
			/* No - return the number of packets we've processed. */
			return n;
		}
	}
	return n;
}