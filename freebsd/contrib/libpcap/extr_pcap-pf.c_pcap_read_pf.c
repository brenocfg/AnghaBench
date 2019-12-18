#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; scalar_t__ len; int /*<<< orphan*/  ts; } ;
struct pcap_pf {scalar_t__ TotMissed; scalar_t__ OrigMissed; int /*<<< orphan*/  TotAccepted; scalar_t__ filtering_in_kernel; int /*<<< orphan*/  TotDrops; int /*<<< orphan*/  TotPkts; } ;
struct enstamp {int ens_stamplen; int ens_count; scalar_t__ ens_ifoverflows; int /*<<< orphan*/  ens_tstamp; scalar_t__ ens_dropped; } ;
struct TYPE_4__ {int /*<<< orphan*/  bf_insns; } ;
struct TYPE_5__ {int cc; int offset; scalar_t__ bufsize; int snapshot; int /*<<< orphan*/ * bp; TYPE_1__ fcode; int /*<<< orphan*/  errbuf; scalar_t__ break_loop; scalar_t__ fddipad; scalar_t__ buffer; int /*<<< orphan*/  fd; struct pcap_pf* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int ENALIGN (int) ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  PACKET_COUNT_IS_UNLIMITED (int) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ bpf_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ errno ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int read (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pcap_read_pf(pcap_t *pc, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_pf *pf = pc->priv;
	register u_char *p, *bp;
	register int cc, n, buflen, inc;
	register struct enstamp *sp;
#ifdef LBL_ALIGN
	struct enstamp stamp;
#endif
	register u_int pad;

 again:
	cc = pc->cc;
	if (cc == 0) {
		cc = read(pc->fd, (char *)pc->buffer + pc->offset, pc->bufsize);
		if (cc < 0) {
			if (errno == EWOULDBLOCK)
				return (0);
			if (errno == EINVAL &&
			    lseek(pc->fd, 0L, SEEK_CUR) + pc->bufsize < 0) {
				/*
				 * Due to a kernel bug, after 2^31 bytes,
				 * the kernel file offset overflows and
				 * read fails with EINVAL. The lseek()
				 * to 0 will fix things.
				 */
				(void)lseek(pc->fd, 0L, SEEK_SET);
				goto again;
			}
			pcap_fmt_errmsg_for_errno(pc->errbuf,
			    sizeof(pc->errbuf), errno, "pf read");
			return (-1);
		}
		bp = (u_char *)pc->buffer + pc->offset;
	} else
		bp = pc->bp;
	/*
	 * Loop through each packet.
	 */
	n = 0;
	pad = pc->fddipad;
	while (cc > 0) {
		/*
		 * Has "pcap_breakloop()" been called?
		 * If so, return immediately - if we haven't read any
		 * packets, clear the flag and return -2 to indicate
		 * that we were told to break out of the loop, otherwise
		 * leave the flag set, so that the *next* call will break
		 * out of the loop without having read any packets, and
		 * return the number of packets we've processed so far.
		 */
		if (pc->break_loop) {
			if (n == 0) {
				pc->break_loop = 0;
				return (-2);
			} else {
				pc->cc = cc;
				pc->bp = bp;
				return (n);
			}
		}
		if (cc < sizeof(*sp)) {
			pcap_snprintf(pc->errbuf, sizeof(pc->errbuf),
			    "pf short read (%d)", cc);
			return (-1);
		}
#ifdef LBL_ALIGN
		if ((long)bp & 3) {
			sp = &stamp;
			memcpy((char *)sp, (char *)bp, sizeof(*sp));
		} else
#endif
			sp = (struct enstamp *)bp;
		if (sp->ens_stamplen != sizeof(*sp)) {
			pcap_snprintf(pc->errbuf, sizeof(pc->errbuf),
			    "pf short stamplen (%d)",
			    sp->ens_stamplen);
			return (-1);
		}

		p = bp + sp->ens_stamplen;
		buflen = sp->ens_count;
		if (buflen > pc->snapshot)
			buflen = pc->snapshot;

		/* Calculate inc before possible pad update */
		inc = ENALIGN(buflen + sp->ens_stamplen);
		cc -= inc;
		bp += inc;
		pf->TotPkts++;
		pf->TotDrops += sp->ens_dropped;
		pf->TotMissed = sp->ens_ifoverflows;
		if (pf->OrigMissed < 0)
			pf->OrigMissed = pf->TotMissed;

		/*
		 * Short-circuit evaluation: if using BPF filter
		 * in kernel, no need to do it now - we already know
		 * the packet passed the filter.
		 *
		 * Note: the filter code was generated assuming
		 * that pc->fddipad was the amount of padding
		 * before the header, as that's what's required
		 * in the kernel, so we run the filter before
		 * skipping that padding.
		 */
		if (pf->filtering_in_kernel ||
		    bpf_filter(pc->fcode.bf_insns, p, sp->ens_count, buflen)) {
			struct pcap_pkthdr h;
			pf->TotAccepted++;
			h.ts = sp->ens_tstamp;
			h.len = sp->ens_count - pad;
			p += pad;
			buflen -= pad;
			h.caplen = buflen;
			(*callback)(user, &h, p);
			if (++n >= cnt && !PACKET_COUNT_IS_UNLIMITED(cnt)) {
				pc->cc = cc;
				pc->bp = bp;
				return (n);
			}
		}
	}
	pc->cc = 0;
	return (n);
}