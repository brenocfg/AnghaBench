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
struct pcap_pkthdr {int len; int caplen; int /*<<< orphan*/  ts; } ;
struct TYPE_5__ {int /*<<< orphan*/  ps_recv; int /*<<< orphan*/  ps_drop; } ;
struct pcap_nit {TYPE_1__ stat; } ;
struct nit_hdr {int nh_state; int nh_datalen; int nh_wirelen; int /*<<< orphan*/  nh_timestamp; int /*<<< orphan*/  nh_dropped; } ;
struct TYPE_6__ {int /*<<< orphan*/  bf_insns; } ;
struct TYPE_7__ {int cc; int snapshot; int /*<<< orphan*/ * bp; TYPE_2__ fcode; int /*<<< orphan*/  errbuf; scalar_t__ break_loop; scalar_t__ buffer; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fd; struct pcap_nit* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
#define  NIT_CATCH 132 
#define  NIT_NOCLUSTER 131 
#define  NIT_NOMBUF 130 
#define  NIT_NOSPACE 129 
#define  NIT_SEQNO 128 
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pcap_read_nit(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_nit *pn = p->priv;
	register int cc, n;
	register u_char *bp, *cp, *ep;
	register struct nit_hdr *nh;
	register int caplen;

	cc = p->cc;
	if (cc == 0) {
		cc = read(p->fd, (char *)p->buffer, p->bufsize);
		if (cc < 0) {
			if (errno == EWOULDBLOCK)
				return (0);
			pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
			    errno, "pcap_read");
			return (-1);
		}
		bp = (u_char *)p->buffer;
	} else
		bp = p->bp;

	/*
	 * Loop through each packet.  The increment expression
	 * rounds up to the next int boundary past the end of
	 * the previous packet.
	 */
	n = 0;
	ep = bp + cc;
	while (bp < ep) {
		/*
		 * Has "pcap_breakloop()" been called?
		 * If so, return immediately - if we haven't read any
		 * packets, clear the flag and return -2 to indicate
		 * that we were told to break out of the loop, otherwise
		 * leave the flag set, so that the *next* call will break
		 * out of the loop without having read any packets, and
		 * return the number of packets we've processed so far.
		 */
		if (p->break_loop) {
			if (n == 0) {
				p->break_loop = 0;
				return (-2);
			} else {
				p->cc = ep - bp;
				p->bp = bp;
				return (n);
			}
		}

		nh = (struct nit_hdr *)bp;
		cp = bp + sizeof(*nh);

		switch (nh->nh_state) {

		case NIT_CATCH:
			break;

		case NIT_NOMBUF:
		case NIT_NOCLUSTER:
		case NIT_NOSPACE:
			pn->stat.ps_drop = nh->nh_dropped;
			continue;

		case NIT_SEQNO:
			continue;

		default:
			pcap_snprintf(p->errbuf, sizeof(p->errbuf),
			    "bad nit state %d", nh->nh_state);
			return (-1);
		}
		++pn->stat.ps_recv;
		bp += ((sizeof(struct nit_hdr) + nh->nh_datalen +
		    sizeof(int) - 1) & ~(sizeof(int) - 1));

		caplen = nh->nh_wirelen;
		if (caplen > p->snapshot)
			caplen = p->snapshot;
		if (bpf_filter(p->fcode.bf_insns, cp, nh->nh_wirelen, caplen)) {
			struct pcap_pkthdr h;
			h.ts = nh->nh_timestamp;
			h.len = nh->nh_wirelen;
			h.caplen = caplen;
			(*callback)(user, &h, cp);
			if (++n >= cnt && !PACKET_COUNT_IS_UNLIMITED(cnt)) {
				p->cc = ep - bp;
				p->bp = bp;
				return (n);
			}
		}
	}
	p->cc = 0;
	return (n);
}