#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct sctphdr {int src_port; int dest_port; int v_tag; void* checksum; } ;
struct sctp_paramhdr {void* param_length; void* param_type; } ;
struct TYPE_4__ {int initiate_tag; void* initial_tsn; void* num_inbound_streams; void* num_outbound_streams; void* a_rwnd; } ;
struct TYPE_3__ {void* chunk_length; scalar_t__ chunk_flags; int /*<<< orphan*/  chunk_type; } ;
struct sctp_init_chunk {TYPE_2__ init; TYPE_1__ ch; } ;
struct sctp_chunkhdr {void* chunk_length; scalar_t__ chunk_flags; int /*<<< orphan*/  chunk_type; } ;
struct outdata {int seq; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_INITIATION ; 
 int SCTP_PAD ; 
 int /*<<< orphan*/  SCTP_PAD_CHUNK ; 
 int /*<<< orphan*/  SCTP_SHUTDOWN_ACK ; 
 scalar_t__ doipcksum ; 
 scalar_t__ fixedPort ; 
 void* htonl (int) ; 
 void* htons (int) ; 
 int ident ; 
 scalar_t__ outp ; 
 int port ; 
 int protlen ; 
 void* sctp_crc32c (struct sctphdr* const,int) ; 

void
sctp_prep(struct outdata *outdata)
{
	struct sctphdr *const sctp = (struct sctphdr *) outp;
	struct sctp_chunkhdr *chk;
	struct sctp_init_chunk *init;
	struct sctp_paramhdr *param;

	sctp->src_port = htons(ident);
	sctp->dest_port = htons(port + (fixedPort ? 0 : outdata->seq));
	if (protlen >= (int)(sizeof(struct sctphdr) +
	    sizeof(struct sctp_init_chunk))) {
		sctp->v_tag = 0;
	} else {
		sctp->v_tag = (sctp->src_port << 16) | sctp->dest_port;
	}
	sctp->checksum = htonl(0);
	if (protlen >= (int)(sizeof(struct sctphdr) +
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
		init->ch.chunk_length = htons((u_int16_t)(protlen -
		    sizeof(struct sctphdr)));
		init->init.initiate_tag = (sctp->src_port << 16) |
		    sctp->dest_port;
		init->init.a_rwnd = htonl(1500);
		init->init.num_outbound_streams = htons(1);
		init->init.num_inbound_streams = htons(1);
		init->init.initial_tsn = htonl(0);
		if (protlen >= (int)(sizeof(struct sctphdr) +
		    sizeof(struct sctp_init_chunk) +
		    sizeof(struct sctp_paramhdr))) {
			param = (struct sctp_paramhdr *)(init + 1);
			param->param_type = htons(SCTP_PAD);
			param->param_length =
			    htons((u_int16_t)(protlen -
			    sizeof(struct sctphdr) -
			    sizeof(struct sctp_init_chunk)));
		}
	} else {
		/*
		 * Send a packet containing a SHUTDOWN-ACK chunk,
		 * possibly followed by a PAD chunk.
		 */
		if (protlen >=
		    (int)(sizeof(struct sctphdr) +
		    sizeof(struct sctp_chunkhdr))) {
			chk = (struct sctp_chunkhdr *)(sctp + 1);
			chk->chunk_type = SCTP_SHUTDOWN_ACK;
			chk->chunk_flags = 0;
			chk->chunk_length = htons(4);
		}
		if (protlen >=
		    (int)(sizeof(struct sctphdr) +
		    2 * sizeof(struct sctp_chunkhdr))) {
			chk = chk + 1;
			chk->chunk_type = SCTP_PAD_CHUNK;
			chk->chunk_flags = 0;
			chk->chunk_length = htons(protlen -
			    (sizeof(struct sctphdr) + sizeof(struct sctp_chunkhdr)));
		}
	}
	if (doipcksum) {
		sctp->checksum = sctp_crc32c(sctp, protlen);
	}
}