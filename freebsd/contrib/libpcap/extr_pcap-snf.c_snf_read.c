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
typedef  int /*<<< orphan*/  u_char ;
struct snf_recv_req {int length; int /*<<< orphan*/  pkt_addr; int /*<<< orphan*/  timestamp; } ;
struct pcap_snf {int snf_timeout; int /*<<< orphan*/  snf_ring; } ;
struct pcap_pkthdr {int caplen; int len; int /*<<< orphan*/  ts; } ;
struct TYPE_6__ {int /*<<< orphan*/  tstamp_precision; } ;
struct TYPE_5__ {int /*<<< orphan*/ * bf_insns; } ;
struct TYPE_7__ {int snapshot; TYPE_2__ opt; TYPE_1__ fcode; int /*<<< orphan*/  errbuf; scalar_t__ break_loop; struct pcap_snf* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 scalar_t__ PACKET_COUNT_IS_UNLIMITED (int) ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int snf_ring_recv (int /*<<< orphan*/ ,int,struct snf_recv_req*) ; 
 int /*<<< orphan*/  snf_timestamp_to_timeval (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snf_read(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_snf *ps = p->priv;
	struct pcap_pkthdr hdr;
	int i, flags, err, caplen, n;
	struct snf_recv_req req;
	int nonblock, timeout;

	if (!p)
		return -1;

	n = 0;
	timeout = ps->snf_timeout;
	while (n < cnt || PACKET_COUNT_IS_UNLIMITED(cnt)) {
		/*
		 * Has "pcap_breakloop()" been called?
		 */
		if (p->break_loop) {
			if (n == 0) {
				p->break_loop = 0;
				return (-2);
			} else {
				return (n);
			}
		}

		err = snf_ring_recv(ps->snf_ring, timeout, &req);

		if (err) {
			if (err == EBUSY || err == EAGAIN) {
				return (n);
			}
			else if (err == EINTR) {
				timeout = 0;
				continue;
			}
			else {
				pcap_fmt_errmsg_for_errno(p->errbuf,
				    PCAP_ERRBUF_SIZE, err, "snf_read");
				return -1;
			}
		}

		caplen = req.length;
		if (caplen > p->snapshot)
			caplen = p->snapshot;

		if ((p->fcode.bf_insns == NULL) ||
		     bpf_filter(p->fcode.bf_insns, req.pkt_addr, req.length, caplen)) {
			hdr.ts = snf_timestamp_to_timeval(req.timestamp, p->opt.tstamp_precision);
			hdr.caplen = caplen;
			hdr.len = req.length;
			callback(user, &hdr, req.pkt_addr);
		}
		n++;

		/* After one successful packet is received, we won't block
		* again for that timeout. */
		if (timeout != 0)
			timeout = 0;
	}
	return (n);
}