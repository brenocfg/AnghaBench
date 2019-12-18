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
typedef  int /*<<< orphan*/  uint32 ;
struct rpcap_stats {int /*<<< orphan*/  svrcapt; int /*<<< orphan*/  ifrecv; int /*<<< orphan*/  ifdrop; int /*<<< orphan*/  krnldrop; } ;
struct rpcap_header {int /*<<< orphan*/  plen; } ;
struct pcap_stat {void* ps_sent; int /*<<< orphan*/  ps_netdrop; int /*<<< orphan*/  ps_capt; void* ps_recv; void* ps_ifdrop; void* ps_drop; } ;
struct pcap_rpcap {int /*<<< orphan*/  rmt_sockctrl; int /*<<< orphan*/  TotNetDrops; int /*<<< orphan*/  TotCapt; int /*<<< orphan*/  protocol_version; int /*<<< orphan*/  rmt_capstarted; } ;
struct TYPE_3__ {int /*<<< orphan*/ * errbuf; struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_STATS_EX ; 
 int PCAP_STATS_STANDARD ; 
 int /*<<< orphan*/  RPCAP_MSG_STATS_REQ ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rpcap_createhdr (struct rpcap_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpcap_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rpcap_process_msg_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,int /*<<< orphan*/ *) ; 
 int rpcap_recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sock_send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pcap_stat *rpcap_stats_rpcap(pcap_t *p, struct pcap_stat *ps, int mode)
{
	struct pcap_rpcap *pr = p->priv;	/* structure used when doing a remote live capture */
	struct rpcap_header header;		/* header of the RPCAP packet */
	struct rpcap_stats netstats;		/* statistics sent on the network */
	uint32 plen;				/* data remaining in the message */

#ifdef _WIN32
	if (mode != PCAP_STATS_STANDARD && mode != PCAP_STATS_EX)
#else
	if (mode != PCAP_STATS_STANDARD)
#endif
	{
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "Invalid stats mode %d", mode);
		return NULL;
	}

	/*
	 * If the capture has not yet started, we cannot request statistics
	 * for the capture from our peer, so we return 0 for all statistics,
	 * as nothing's been seen yet.
	 */
	if (!pr->rmt_capstarted)
	{
		ps->ps_drop = 0;
		ps->ps_ifdrop = 0;
		ps->ps_recv = 0;
#ifdef _WIN32
		if (mode == PCAP_STATS_EX)
		{
			ps->ps_capt = 0;
			ps->ps_sent = 0;
			ps->ps_netdrop = 0;
		}
#endif /* _WIN32 */

		return ps;
	}

	rpcap_createhdr(&header, pr->protocol_version,
	    RPCAP_MSG_STATS_REQ, 0, 0);

	/* Send the PCAP_STATS command */
	if (sock_send(pr->rmt_sockctrl, (char *)&header,
	    sizeof(struct rpcap_header), p->errbuf, PCAP_ERRBUF_SIZE) < 0)
		return NULL;		/* Unrecoverable network error */

	/* Receive and process the reply message header. */
	if (rpcap_process_msg_header(pr->rmt_sockctrl, pr->protocol_version,
	    RPCAP_MSG_STATS_REQ, &header, p->errbuf) == -1)
		return NULL;		/* Error */

	plen = header.plen;

	/* Read the reply body */
	if (rpcap_recv(pr->rmt_sockctrl, (char *)&netstats,
	    sizeof(struct rpcap_stats), &plen, p->errbuf) == -1)
		goto error;

	ps->ps_drop = ntohl(netstats.krnldrop);
	ps->ps_ifdrop = ntohl(netstats.ifdrop);
	ps->ps_recv = ntohl(netstats.ifrecv);
#ifdef _WIN32
	if (mode == PCAP_STATS_EX)
	{
		ps->ps_capt = pr->TotCapt;
		ps->ps_netdrop = pr->TotNetDrops;
		ps->ps_sent = ntohl(netstats.svrcapt);
	}
#endif /* _WIN32 */

	/* Discard the rest of the message. */
	if (rpcap_discard(pr->rmt_sockctrl, plen, p->errbuf) == -1)
		goto error;

	return ps;

error:
	/*
	 * Discard the rest of the message.
	 * We already reported an error; if this gets an error, just
	 * drive on.
	 */
	(void)rpcap_discard(pr->rmt_sockctrl, plen, NULL);

	return NULL;
}