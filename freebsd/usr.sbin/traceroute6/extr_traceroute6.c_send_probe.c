#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u_int16_t ;
struct tcphdr {int th_sport; int th_dport; int th_seq; int th_off; int /*<<< orphan*/  th_sum; int /*<<< orphan*/  th_flags; int /*<<< orphan*/  th_ack; } ;
struct sockaddr {int dummy; } ;
struct sctphdr {int src_port; int dest_port; int v_tag; void* checksum; } ;
struct sctp_paramhdr {void* param_length; void* param_type; } ;
struct TYPE_6__ {int initiate_tag; void* initial_tsn; void* num_inbound_streams; void* num_outbound_streams; void* a_rwnd; } ;
struct TYPE_5__ {void* chunk_length; int /*<<< orphan*/  chunk_flags; int /*<<< orphan*/  chunk_type; } ;
struct sctp_init_chunk {TYPE_2__ init; TYPE_1__ ch; } ;
struct sctp_chunkhdr {void* chunk_length; int /*<<< orphan*/  chunk_flags; int /*<<< orphan*/  chunk_type; } ;
struct icmp6_hdr {int icmp6_id; void* icmp6_seq; int /*<<< orphan*/  icmp6_cksum; int /*<<< orphan*/  icmp6_code; int /*<<< orphan*/  icmp6_type; } ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_7__ {int /*<<< orphan*/  sin6_len; void* sin6_port; } ;

/* Variables and functions */
 TYPE_3__ Dst ; 
 int /*<<< orphan*/  ICMP6_ECHO_REQUEST ; 
#define  IPPROTO_ICMPV6 132 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
#define  IPPROTO_NONE 131 
#define  IPPROTO_SCTP 130 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  IPV6_UNICAST_HOPS ; 
 int /*<<< orphan*/  SCTP_INITIATION ; 
 int SCTP_PAD ; 
 int /*<<< orphan*/  SCTP_PAD_CHUNK ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_ACK ; 
 int /*<<< orphan*/  Src ; 
 int /*<<< orphan*/  TH_SYN ; 
 scalar_t__ datalen ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 char* hostname ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 int ident ; 
 scalar_t__ outpacket ; 
 int /*<<< orphan*/  perror (char*) ; 
 int port ; 
 int /*<<< orphan*/  printf (char*,char*,scalar_t__,int) ; 
 void* sctp_crc32c (scalar_t__,scalar_t__) ; 
 int sendto (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sndsock ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tcp_chksum (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,scalar_t__) ; 
 int useproto ; 

void
send_probe(int seq, u_long hops)
{
	struct icmp6_hdr *icp;
	struct sctphdr *sctp;
	struct sctp_chunkhdr *chk;
	struct sctp_init_chunk *init;
	struct sctp_paramhdr *param;
	struct tcphdr *tcp;
	int i;

	i = hops;
	if (setsockopt(sndsock, IPPROTO_IPV6, IPV6_UNICAST_HOPS,
	    (char *)&i, sizeof(i)) < 0) {
		perror("setsockopt IPV6_UNICAST_HOPS");
	}

	Dst.sin6_port = htons(port + seq);

	switch (useproto) {
	case IPPROTO_ICMPV6:
		icp = (struct icmp6_hdr *)outpacket;

		icp->icmp6_type = ICMP6_ECHO_REQUEST;
		icp->icmp6_code = 0;
		icp->icmp6_cksum = 0;
		icp->icmp6_id = ident;
		icp->icmp6_seq = htons(seq);
		break;
	case IPPROTO_UDP:
		break;
	case IPPROTO_NONE:
		/* No space for anything. No harm as seq/tv32 are decorative. */
		break;
	case IPPROTO_SCTP:
		sctp = (struct sctphdr *)outpacket;

		sctp->src_port = htons(ident);
		sctp->dest_port = htons(port + seq);
		if (datalen >= (u_long)(sizeof(struct sctphdr) +
		    sizeof(struct sctp_init_chunk))) {
			sctp->v_tag = 0;
		} else {
			sctp->v_tag = (sctp->src_port << 16) | sctp->dest_port;
		}
		sctp->checksum = htonl(0);
		if (datalen >= (u_long)(sizeof(struct sctphdr) +
		    sizeof(struct sctp_init_chunk))) {
			/*
			 * Send a packet containing an INIT chunk. This works
			 * better in case of firewalls on the path, but
			 * results in a probe packet containing at least
			 * 32 bytes of payload. For shorter payloads, use
			 * SHUTDOWN-ACK chunks.
			 */
			init = (struct sctp_init_chunk *)(sctp + 1);
			init->ch.chunk_type = SCTP_INITIATION;
			init->ch.chunk_flags = 0;
			init->ch.chunk_length = htons((u_int16_t)(datalen -
			    sizeof(struct sctphdr)));
			init->init.initiate_tag = (sctp->src_port << 16) |
			    sctp->dest_port;
			init->init.a_rwnd = htonl(1500);
			init->init.num_outbound_streams = htons(1);
			init->init.num_inbound_streams = htons(1);
			init->init.initial_tsn = htonl(0);
			if (datalen >= (u_long)(sizeof(struct sctphdr) +
			    sizeof(struct sctp_init_chunk) +
			    sizeof(struct sctp_paramhdr))) {
				param = (struct sctp_paramhdr *)(init + 1);
				param->param_type = htons(SCTP_PAD);
				param->param_length =
				    htons((u_int16_t)(datalen -
				    sizeof(struct sctphdr) -
				    sizeof(struct sctp_init_chunk)));
			}
		} else {
			/*
			 * Send a packet containing a SHUTDOWN-ACK chunk,
			 * possibly followed by a PAD chunk.
			 */
			if (datalen >= (u_long)(sizeof(struct sctphdr) +
			    sizeof(struct sctp_chunkhdr))) {
				chk = (struct sctp_chunkhdr *)(sctp + 1);
				chk->chunk_type = SCTP_SHUTDOWN_ACK;
				chk->chunk_flags = 0;
				chk->chunk_length = htons(4);
			}
			if (datalen >= (u_long)(sizeof(struct sctphdr) +
			    2 * sizeof(struct sctp_chunkhdr))) {
				chk = chk + 1;
				chk->chunk_type = SCTP_PAD_CHUNK;
				chk->chunk_flags = 0;
				chk->chunk_length = htons((u_int16_t)(datalen -
				    sizeof(struct sctphdr) -
				    sizeof(struct sctp_chunkhdr)));
			}
		}
		sctp->checksum = sctp_crc32c(outpacket, datalen);
		break;
	case IPPROTO_TCP:
		tcp = (struct tcphdr *)outpacket;

		tcp->th_sport = htons(ident);
		tcp->th_dport = htons(port + seq);
		tcp->th_seq = (tcp->th_sport << 16) | tcp->th_dport;
		tcp->th_ack = 0;
		tcp->th_off = 5;
		tcp->th_flags = TH_SYN;
		tcp->th_sum = 0;
		tcp->th_sum = tcp_chksum(&Src, &Dst, outpacket, datalen);
		break;
	default:
		fprintf(stderr, "Unknown probe protocol %d.\n", useproto);
		exit(1);
	}

	i = sendto(sndsock, (char *)outpacket, datalen, 0,
	    (struct sockaddr *)&Dst, Dst.sin6_len);
	if (i < 0 || (u_long)i != datalen)  {
		if (i < 0)
			perror("sendto");
		printf("traceroute6: wrote %s %lu chars, ret=%d\n",
		    hostname, datalen, i);
		(void) fflush(stdout);
	}
}