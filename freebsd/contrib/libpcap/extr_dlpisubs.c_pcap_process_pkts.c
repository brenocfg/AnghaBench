#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct sb_hdr {int sbh_origlen; int sbh_msglen; TYPE_3__ sbh_timestamp; int /*<<< orphan*/  sbh_totlen; int /*<<< orphan*/  sbh_drops; } ;
struct TYPE_11__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct pcap_pkthdr {int len; int caplen; TYPE_6__ ts; } ;
struct TYPE_7__ {int /*<<< orphan*/  ps_recv; int /*<<< orphan*/  ps_drop; } ;
struct pcap_dlpi {TYPE_1__ stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  bf_insns; } ;
struct TYPE_10__ {int cc; int /*<<< orphan*/ * bp; scalar_t__ snapshot; TYPE_2__ fcode; scalar_t__ break_loop; struct pcap_dlpi* priv; } ;
typedef  TYPE_4__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;
typedef  int bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  gettimeofday (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct sb_hdr*,int /*<<< orphan*/ *,int) ; 
 int min (scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

int
pcap_process_pkts(pcap_t *p, pcap_handler callback, u_char *user,
	int count, u_char *bufp, int len)
{
	struct pcap_dlpi *pd = p->priv;
	int n, caplen, origlen;
	u_char *ep, *pk;
	struct pcap_pkthdr pkthdr;
#ifdef HAVE_SYS_BUFMOD_H
	struct sb_hdr *sbp;
#ifdef LBL_ALIGN
	struct sb_hdr sbhdr;
#endif
#endif

	/* Loop through packets */
	ep = bufp + len;
	n = 0;

#ifdef HAVE_SYS_BUFMOD_H
	while (bufp < ep) {
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
				p->bp = bufp;
				p->cc = ep - bufp;
				return (n);
			}
		}
#ifdef LBL_ALIGN
		if ((long)bufp & 3) {
			sbp = &sbhdr;
			memcpy(sbp, bufp, sizeof(*sbp));
		} else
#endif
			sbp = (struct sb_hdr *)bufp;
		pd->stat.ps_drop = sbp->sbh_drops;
		pk = bufp + sizeof(*sbp);
		bufp += sbp->sbh_totlen;
		origlen = sbp->sbh_origlen;
		caplen = sbp->sbh_msglen;
#else
		origlen = len;
		caplen = min(p->snapshot, len);
		pk = bufp;
		bufp += caplen;
#endif
		++pd->stat.ps_recv;
		if (bpf_filter(p->fcode.bf_insns, pk, origlen, caplen)) {
#ifdef HAVE_SYS_BUFMOD_H
			pkthdr.ts.tv_sec = sbp->sbh_timestamp.tv_sec;
			pkthdr.ts.tv_usec = sbp->sbh_timestamp.tv_usec;
#else
			(void) gettimeofday(&pkthdr.ts, NULL);
#endif
			pkthdr.len = origlen;
			pkthdr.caplen = caplen;
			/* Insure caplen does not exceed snapshot */
			if (pkthdr.caplen > (bpf_u_int32)p->snapshot)
				pkthdr.caplen = (bpf_u_int32)p->snapshot;
			(*callback)(user, &pkthdr, pk);
			if (++n >= count && !PACKET_COUNT_IS_UNLIMITED(count)) {
				p->cc = ep - bufp;
				p->bp = bufp;
				return (n);
			}
		}
#ifdef HAVE_SYS_BUFMOD_H
	}
#endif
	p->cc = 0;
	return (n);
}