#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32 ;
typedef  int /*<<< orphan*/  u_char ;
struct timeval {int tv_sec; int tv_usec; } ;
struct rpcap_pkthdr {int caplen; int len; int timestamp_sec; int timestamp_usec; int npkt; } ;
struct rpcap_header {int plen; scalar_t__ type; } ;
struct pcap_rpcap {int rmt_flags; unsigned int TotCapt; int /*<<< orphan*/  TotNetDrops; int /*<<< orphan*/  protocol_version; scalar_t__ rmt_sockdata; } ;
struct TYPE_7__ {int tv_sec; int tv_usec; } ;
struct pcap_pkthdr {int caplen; int len; TYPE_2__ ts; } ;
struct TYPE_6__ {int timeout; } ;
struct TYPE_8__ {int bufsize; int /*<<< orphan*/  errbuf; scalar_t__ cc; scalar_t__ buffer; scalar_t__ bp; TYPE_1__ opt; struct pcap_rpcap* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_OPENFLAG_DATATX_UDP ; 
 scalar_t__ RPCAP_MSG_PACKET ; 
 scalar_t__ errno ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rpcap_check_msg_ver (scalar_t__,int /*<<< orphan*/ ,struct rpcap_header*,int /*<<< orphan*/ ) ; 
 int rpcap_read_packet_msg (scalar_t__,TYPE_3__*,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  sock_geterror (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sock_recv_dgram (scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_read_nocb_remote(pcap_t *p, struct pcap_pkthdr *pkt_header, u_char **pkt_data)
{
	struct pcap_rpcap *pr = p->priv;	/* structure used when doing a remote live capture */
	struct rpcap_header *header;		/* general header according to the RPCAP format */
	struct rpcap_pkthdr *net_pkt_header;	/* header of the packet, from the message */
	u_char *net_pkt_data;			/* packet data from the message */
	uint32 plen;
	int retval;				/* generic return value */
	int msglen;

	/* Structures needed for the select() call */
	struct timeval tv;			/* maximum time the select() can block waiting for data */
	fd_set rfds;				/* set of socket descriptors we have to check */

	/*
	 * Define the packet buffer timeout, to be used in the select()
	 * 'timeout', in pcap_t, is in milliseconds; we have to convert it into sec and microsec
	 */
	tv.tv_sec = p->opt.timeout / 1000;
	tv.tv_usec = (p->opt.timeout - tv.tv_sec * 1000) * 1000;

	/* Watch out sockdata to see if it has input */
	FD_ZERO(&rfds);

	/*
	 * 'fp->rmt_sockdata' has always to be set before calling the select(),
	 * since it is cleared by the select()
	 */
	FD_SET(pr->rmt_sockdata, &rfds);

	retval = select((int) pr->rmt_sockdata + 1, &rfds, NULL, NULL, &tv);
	if (retval == -1)
	{
#ifndef _WIN32
		if (errno == EINTR)
		{
			/* Interrupted. */
			return 0;
		}
#endif
		sock_geterror("select(): ", p->errbuf, PCAP_ERRBUF_SIZE);
		return -1;
	}

	/* There is no data waiting, so return '0' */
	if (retval == 0)
		return 0;

	/*
	 * We have to define 'header' as a pointer to a larger buffer,
	 * because in case of UDP we have to read all the message within a single call
	 */
	header = (struct rpcap_header *) p->buffer;
	net_pkt_header = (struct rpcap_pkthdr *) ((char *)p->buffer + sizeof(struct rpcap_header));
	net_pkt_data = (u_char *)p->buffer + sizeof(struct rpcap_header) + sizeof(struct rpcap_pkthdr);

	if (pr->rmt_flags & PCAP_OPENFLAG_DATATX_UDP)
	{
		/* Read the entire message from the network */
		msglen = sock_recv_dgram(pr->rmt_sockdata, p->buffer,
		    p->bufsize, p->errbuf, PCAP_ERRBUF_SIZE);
		if (msglen == -1)
		{
			/* Network error. */
			return -1;
		}
		if (msglen == -3)
		{
			/* Interrupted receive. */
			return 0;
		}
		if ((size_t)msglen < sizeof(struct rpcap_header))
		{
			/*
			 * Message is shorter than an rpcap header.
			 */
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "UDP packet message is shorter than an rpcap header");
			return -1;
		}
		plen = ntohl(header->plen);
		if ((size_t)msglen < sizeof(struct rpcap_header) + plen)
		{
			/*
			 * Message is shorter than the header claims it
			 * is.
			 */
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "UDP packet message is shorter than its rpcap header claims");
			return -1;
		}
	}
	else
	{
		int status;

		if ((size_t)p->cc < sizeof(struct rpcap_header))
		{
			/*
			 * We haven't read any of the packet header yet.
			 * The size we should get is the size of the
			 * packet header.
			 */
			status = rpcap_read_packet_msg(pr->rmt_sockdata, p,
			    sizeof(struct rpcap_header));
			if (status == -1)
			{
				/* Network error. */
				return -1;
			}
			if (status == -3)
			{
				/* Interrupted receive. */
				return 0;
			}
		}

		/*
		 * We have the header, so we know how long the
		 * message payload is.  The size we should get
		 * is the size of the packet header plus the
		 * size of the payload.
		 */
		plen = ntohl(header->plen);
		if (plen > p->bufsize - sizeof(struct rpcap_header))
		{
			/*
			 * This is bigger than the largest
			 * record we'd expect.  (We do it by
			 * subtracting in order to avoid an
			 * overflow.)
			 */
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "Server sent us a message larger than the largest expected packet message");
			return -1;
		}
		status = rpcap_read_packet_msg(pr->rmt_sockdata, p,
		    sizeof(struct rpcap_header) + plen);
		if (status == -1)
		{
			/* Network error. */
			return -1;
		}
		if (status == -3)
		{
			/* Interrupted receive. */
			return 0;
		}

		/*
		 * We have the entire message; reset the buffer pointer
		 * and count, as the next read should start a new
		 * message.
		 */
		p->bp = p->buffer;
		p->cc = 0;
	}

	/*
	 * We have the entire message.
	 */
	header->plen = plen;

	/*
	 * Did the server specify the version we negotiated?
	 */
	if (rpcap_check_msg_ver(pr->rmt_sockdata, pr->protocol_version,
	    header, p->errbuf) == -1)
	{
		return 0;	/* Return 'no packets received' */
	}

	/*
	 * Is this a RPCAP_MSG_PACKET message?
	 */
	if (header->type != RPCAP_MSG_PACKET)
	{
		return 0;	/* Return 'no packets received' */
	}

	if (ntohl(net_pkt_header->caplen) > plen)
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Packet's captured data goes past the end of the received packet message.");
		return -1;
	}

	/* Fill in packet header */
	pkt_header->caplen = ntohl(net_pkt_header->caplen);
	pkt_header->len = ntohl(net_pkt_header->len);
	pkt_header->ts.tv_sec = ntohl(net_pkt_header->timestamp_sec);
	pkt_header->ts.tv_usec = ntohl(net_pkt_header->timestamp_usec);

	/* Supply a pointer to the beginning of the packet data */
	*pkt_data = net_pkt_data;

	/*
	 * I don't update the counter of the packets dropped by the network since we're using TCP,
	 * therefore no packets are dropped. Just update the number of packets received correctly
	 */
	pr->TotCapt++;

	if (pr->rmt_flags & PCAP_OPENFLAG_DATATX_UDP)
	{
		unsigned int npkt;

		/* We're using UDP, so we need to update the counter of the packets dropped by the network */
		npkt = ntohl(net_pkt_header->npkt);

		if (pr->TotCapt != npkt)
		{
			pr->TotNetDrops += (npkt - pr->TotCapt);
			pr->TotCapt = npkt;
		}
	}

	/* Packet read successfully */
	return 1;
}