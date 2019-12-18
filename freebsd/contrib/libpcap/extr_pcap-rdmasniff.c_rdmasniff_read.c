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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_rdmasniff {int cq_event; int /*<<< orphan*/  packets_recv; int /*<<< orphan*/  cq; int /*<<< orphan*/  channel; } ;
struct pcap_pkthdr {int /*<<< orphan*/  caplen; int /*<<< orphan*/  len; int /*<<< orphan*/  ts; } ;
struct ibv_wc {scalar_t__ status; int wr_id; int /*<<< orphan*/  byte_len; } ;
struct ibv_cq {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bf_insns; } ;
struct TYPE_6__ {scalar_t__ break_loop; TYPE_1__ fcode; scalar_t__ buffer; scalar_t__ snapshot; struct pcap_rdmasniff* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ IBV_WC_SUCCESS ; 
 scalar_t__ PACKET_COUNT_IS_UNLIMITED (int) ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_BREAK ; 
 int RDMASNIFF_RECEIVE_SIZE ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long long,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_ack_cq_events (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ibv_get_cq_event (int /*<<< orphan*/ ,struct ibv_cq**,void**) ; 
 int ibv_poll_cq (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 
 int /*<<< orphan*/  ibv_req_notify_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibv_wc_status_str (scalar_t__) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmasniff_post_recv (TYPE_2__*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
rdmasniff_read(pcap_t *handle, int max_packets, pcap_handler callback, u_char *user)
{
	struct pcap_rdmasniff *priv = handle->priv;
	struct ibv_cq *ev_cq;
	void *ev_ctx;
	struct ibv_wc wc;
	struct pcap_pkthdr pkth;
	u_char *pktd;
	int count = 0;

	if (!priv->cq_event) {
		while (ibv_get_cq_event(priv->channel, &ev_cq, &ev_ctx) < 0) {
			if (errno != EINTR) {
				return PCAP_ERROR;
			}
			if (handle->break_loop) {
				handle->break_loop = 0;
				return PCAP_ERROR_BREAK;
			}
		}
		ibv_ack_cq_events(priv->cq, 1);
		ibv_req_notify_cq(priv->cq, 0);
		priv->cq_event = 1;
	}

	while (count < max_packets || PACKET_COUNT_IS_UNLIMITED(max_packets)) {
		if (ibv_poll_cq(priv->cq, 1, &wc) != 1) {
			priv->cq_event = 0;
			break;
		}

		if (wc.status != IBV_WC_SUCCESS) {
			fprintf(stderr, "failed WC wr_id %lld status %d/%s\n",
				(unsigned long long) wc.wr_id,
				wc.status, ibv_wc_status_str(wc.status));
			continue;
		}

		pkth.len = wc.byte_len;
		pkth.caplen = min(pkth.len, (u_int)handle->snapshot);
		gettimeofday(&pkth.ts, NULL);

		pktd = (u_char *) handle->buffer + wc.wr_id * RDMASNIFF_RECEIVE_SIZE;

		if (handle->fcode.bf_insns == NULL ||
		    bpf_filter(handle->fcode.bf_insns, pktd, pkth.len, pkth.caplen)) {
			callback(user, &pkth, pktd);
			++priv->packets_recv;
			++count;
		}

		rdmasniff_post_recv(handle, wc.wr_id);

		if (handle->break_loop) {
			handle->break_loop = 0;
			return PCAP_ERROR_BREAK;
		}
	}

	return count;
}