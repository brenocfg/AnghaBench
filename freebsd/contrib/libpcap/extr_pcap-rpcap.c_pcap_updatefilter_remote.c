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
struct rpcap_header {int /*<<< orphan*/  plen; } ;
struct rpcap_filterbpf_insn {int dummy; } ;
struct rpcap_filter {int dummy; } ;
struct pcap_rpcap {int /*<<< orphan*/  rmt_sockctrl; int /*<<< orphan*/  protocol_version; } ;
struct bpf_program {int bf_len; } ;
struct TYPE_4__ {int /*<<< orphan*/  errbuf; struct pcap_rpcap* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  RPCAP_MSG_UPDATEFILTER_REQ ; 
 int RPCAP_NETBUF_SIZE ; 
 int /*<<< orphan*/  SOCKBUF_CHECKONLY ; 
 scalar_t__ pcap_pack_bpffilter (TYPE_1__*,char*,int*,struct bpf_program*) ; 
 int /*<<< orphan*/  rpcap_createhdr (struct rpcap_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int rpcap_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rpcap_process_msg_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rpcap_header*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_bufferize (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_send (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_updatefilter_remote(pcap_t *fp, struct bpf_program *prog)
{
	struct pcap_rpcap *pr = fp->priv;	/* structure used when doing a remote live capture */
	char sendbuf[RPCAP_NETBUF_SIZE];	/* temporary buffer in which data to be sent is buffered */
	int sendbufidx = 0;			/* index which keeps the number of bytes currently buffered */
	struct rpcap_header header;		/* To keep the reply message */

	if (sock_bufferize(NULL, sizeof(struct rpcap_header), NULL, &sendbufidx,
		RPCAP_NETBUF_SIZE, SOCKBUF_CHECKONLY, fp->errbuf, PCAP_ERRBUF_SIZE))
		return -1;

	rpcap_createhdr((struct rpcap_header *) sendbuf,
	    pr->protocol_version, RPCAP_MSG_UPDATEFILTER_REQ, 0,
	    sizeof(struct rpcap_filter) + prog->bf_len * sizeof(struct rpcap_filterbpf_insn));

	if (pcap_pack_bpffilter(fp, &sendbuf[sendbufidx], &sendbufidx, prog))
		return -1;

	if (sock_send(pr->rmt_sockctrl, sendbuf, sendbufidx, fp->errbuf,
	    PCAP_ERRBUF_SIZE) < 0)
		return -1;

	/* Receive and process the reply message header. */
	if (rpcap_process_msg_header(pr->rmt_sockctrl, pr->protocol_version,
	    RPCAP_MSG_UPDATEFILTER_REQ, &header, fp->errbuf) == -1)
		return -1;

	/*
	 * It shouldn't have any contents; discard it if it does.
	 */
	if (rpcap_discard(pr->rmt_sockctrl, header.plen, fp->errbuf) == -1)
		return -1;

	return 0;
}