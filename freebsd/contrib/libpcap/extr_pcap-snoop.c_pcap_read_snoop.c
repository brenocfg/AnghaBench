#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_10__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct snoopheader {int snoop_packetlen; TYPE_4__ snoop_timestamp; } ;
struct TYPE_8__ {int /*<<< orphan*/  ps_recv; } ;
struct pcap_snoop {TYPE_2__ stat; } ;
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct pcap_pkthdr {int len; int caplen; TYPE_3__ ts; } ;
struct TYPE_7__ {int /*<<< orphan*/ * bf_insns; } ;
struct TYPE_11__ {int snapshot; int offset; scalar_t__ linktype; TYPE_1__ fcode; scalar_t__ buffer; int /*<<< orphan*/  errbuf; int /*<<< orphan*/  bufsize; int /*<<< orphan*/  fd; scalar_t__ break_loop; struct pcap_snoop* priv; } ;
typedef  TYPE_5__ pcap_t ;
typedef  int /*<<< orphan*/  (* pcap_handler ) (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ DLT_NULL ; 
#define  EINTR 129 
#define  EWOULDBLOCK 128 
 scalar_t__ bpf_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int errno ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int,char*) ; 
 int read (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,struct pcap_pkthdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pcap_read_snoop(pcap_t *p, int cnt, pcap_handler callback, u_char *user)
{
	struct pcap_snoop *psn = p->priv;
	int cc;
	register struct snoopheader *sh;
	register u_int datalen;
	register u_int caplen;
	register u_char *cp;

again:
	/*
	 * Has "pcap_breakloop()" been called?
	 */
	if (p->break_loop) {
		/*
		 * Yes - clear the flag that indicates that it
		 * has, and return -2 to indicate that we were
		 * told to break out of the loop.
		 */
		p->break_loop = 0;
		return (-2);
	}
	cc = read(p->fd, (char *)p->buffer, p->bufsize);
	if (cc < 0) {
		/* Don't choke when we get ptraced */
		switch (errno) {

		case EINTR:
			goto again;

		case EWOULDBLOCK:
			return (0);			/* XXX */
		}
		pcap_fmt_errmsg_for_errno(p->errbuf, sizeof(p->errbuf),
		    errno, "read");
		return (-1);
	}
	sh = (struct snoopheader *)p->buffer;
	datalen = sh->snoop_packetlen;

	/*
	 * XXX - Sigh, snoop_packetlen is a 16 bit quantity.  If we
	 * got a short length, but read a full sized snoop pakcet,
	 * assume we overflowed and add back the 64K...
	 */
	if (cc == (p->snapshot + sizeof(struct snoopheader)) &&
	    (datalen < p->snapshot))
		datalen += (64 * 1024);

	caplen = (datalen < p->snapshot) ? datalen : p->snapshot;
	cp = (u_char *)(sh + 1) + p->offset;		/* XXX */

	/*
	 * XXX unfortunately snoop loopback isn't exactly like
	 * BSD's.  The address family is encoded in the first 2
	 * bytes rather than the first 4 bytes!  Luckily the last
	 * two snoop loopback bytes are zeroed.
	 */
	if (p->linktype == DLT_NULL && *((short *)(cp + 2)) == 0) {
		u_int *uip = (u_int *)cp;
		*uip >>= 16;
	}

	if (p->fcode.bf_insns == NULL ||
	    bpf_filter(p->fcode.bf_insns, cp, datalen, caplen)) {
		struct pcap_pkthdr h;
		++psn->stat.ps_recv;
		h.ts.tv_sec = sh->snoop_timestamp.tv_sec;
		h.ts.tv_usec = sh->snoop_timestamp.tv_usec;
		h.len = datalen;
		h.caplen = caplen;
		(*callback)(user, &h, cp);
		return (1);
	}
	return (0);
}