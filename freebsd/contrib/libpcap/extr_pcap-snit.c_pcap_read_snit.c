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
struct TYPE_5__ {int /*<<< orphan*/  ps_drop; int /*<<< orphan*/  ps_recv; } ;
struct pcap_snit {TYPE_1__ stat; } ;
struct pcap_pkthdr {int len; int caplen; int /*<<< orphan*/  ts; } ;
struct nit_iftime {int /*<<< orphan*/  nh_timestamp; } ;
struct nit_iflen {int nh_pktlen; } ;
struct nit_ifdrops {int /*<<< orphan*/  nh_drops; } ;
struct nit_bufhdr {int /*<<< orphan*/  nhb_totlen; } ;
struct TYPE_6__ {int /*<<< orphan*/  bf_insns; } ;
struct TYPE_7__ {int cc; int snapshot; int /*<<< orphan*/ * bp; TYPE_2__ fcode; scalar_t__ break_loop; scalar_t__ buffer; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fd; struct pcap_snit* priv; } ;
typedef  TYPE_3__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pcap_read_snit(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_snit *psn = p->priv;
	register int cc, n;
	register u_char *bp, *cp, *ep;
	register struct nit_bufhdr *hdrp;
	register struct nit_iftime *ntp;
	register struct nit_iflen *nlp;
	register struct nit_ifdrops *ndp;
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
	 * loop through each snapshot in the chunk
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
				p->bp = bp;
				p->cc = ep - bp;
				return (n);
			}
		}

		++psn->stat.ps_recv;
		cp = bp;

		/* get past NIT buffer  */
		hdrp = (struct nit_bufhdr *)cp;
		cp += sizeof(*hdrp);

		/* get past NIT timer   */
		ntp = (struct nit_iftime *)cp;
		cp += sizeof(*ntp);

		ndp = (struct nit_ifdrops *)cp;
		psn->stat.ps_drop = ndp->nh_drops;
		cp += sizeof *ndp;

		/* get past packet len  */
		nlp = (struct nit_iflen *)cp;
		cp += sizeof(*nlp);

		/* next snapshot        */
		bp += hdrp->nhb_totlen;

		caplen = nlp->nh_pktlen;
		if (caplen > p->snapshot)
			caplen = p->snapshot;

		if (bpf_filter(p->fcode.bf_insns, cp, nlp->nh_pktlen, caplen)) {
			struct pcap_pkthdr h;
			h.ts = ntp->nh_timestamp;
			h.len = nlp->nh_pktlen;
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