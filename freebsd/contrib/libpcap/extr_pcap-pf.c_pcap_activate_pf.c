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
typedef  void* u_int ;
struct timeval {int tv_sec; int tv_usec; } ;
struct pcap_pf {int OrigMissed; } ;
struct enfilter {int enf_Priority; scalar_t__ enf_FilterLen; } ;
struct endevp {int end_dev_type; } ;
struct TYPE_5__ {int device; int timeout; scalar_t__ promisc; int /*<<< orphan*/  immediate; } ;
struct TYPE_6__ {int fd; scalar_t__ snapshot; scalar_t__ linktype; int offset; int dlt_count; scalar_t__ fddipad; int bufsize; int selectable_fd; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; int /*<<< orphan*/  errbuf; int /*<<< orphan*/ * buffer; TYPE_1__ opt; void** dlt_list; struct pcap_pf* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  Filter ;

/* Variables and functions */
 int BUFSPACE ; 
 void* DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 scalar_t__ DLT_FDDI ; 
 scalar_t__ DLT_IEEE802 ; 
 scalar_t__ DLT_PPP ; 
 scalar_t__ DLT_SLIP ; 
 scalar_t__ EACCES ; 
 int /*<<< orphan*/  EIOCDEVP ; 
 int /*<<< orphan*/  EIOCMBIS ; 
 int /*<<< orphan*/  EIOCSETF ; 
 int /*<<< orphan*/  EIOCSETW ; 
 int /*<<< orphan*/  EIOCSRTIMEOUT ; 
 int /*<<< orphan*/  EIOCTRUNCATE ; 
 short ENBATCH ; 
 short ENCOPYALL ; 
#define  ENDT_10MB 133 
#define  ENDT_FDDI 132 
#define  ENDT_LOOPBACK 131 
#define  ENDT_PPP 130 
#define  ENDT_SLIP 129 
#define  ENDT_TRN 128 
 short ENNONEXCL ; 
 short ENPROMISC ; 
 short ENTSTAMP ; 
 scalar_t__ MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_PERM_DENIED ; 
 scalar_t__ PCAP_FDDIPAD ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (struct enfilter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  pcap_getnonblock_fd ; 
 int /*<<< orphan*/  pcap_inject_pf ; 
 int /*<<< orphan*/  pcap_read_pf ; 
 int /*<<< orphan*/  pcap_setfilter_pf ; 
 int /*<<< orphan*/  pcap_setnonblock_fd ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pcap_stats_pf ; 
 void* pfopen (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_activate_pf(pcap_t *p)
{
	struct pcap_pf *pf = p->priv;
	short enmode;
	int backlog = -1;	/* request the most */
	struct enfilter Filter;
	struct endevp devparams;
	int err;

	/*
	 * Initially try a read/write open (to allow the inject
	 * method to work).  If that fails due to permission
	 * issues, fall back to read-only.  This allows a
	 * non-root user to be granted specific access to pcap
	 * capabilities via file permissions.
	 *
	 * XXX - we should have an API that has a flag that
	 * controls whether to open read-only or read-write,
	 * so that denial of permission to send (or inability
	 * to send, if sending packets isn't supported on
	 * the device in question) can be indicated at open
	 * time.
	 *
	 * XXX - we assume here that "pfopen()" does not, in fact, modify
	 * its argument, even though it takes a "char *" rather than a
	 * "const char *" as its first argument.  That appears to be
	 * the case, at least on Digital UNIX 4.0.
	 *
	 * XXX - is there an error that means "no such device"?  Is
	 * there one that means "that device doesn't support pf"?
	 */
	p->fd = pfopen(p->opt.device, O_RDWR);
	if (p->fd == -1 && errno == EACCES)
		p->fd = pfopen(p->opt.device, O_RDONLY);
	if (p->fd < 0) {
		if (errno == EACCES) {
			pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
			    "pf open: %s: Permission denied\n"
"your system may not be properly configured; see the packetfilter(4) man page",
			    p->opt.device);
			err = PCAP_ERROR_PERM_DENIED;
		} else {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "pf open: %s", p->opt.device);
			err = PCAP_ERROR;
		}
		goto bad;
	}

	/*
	 * Turn a negative snapshot value (invalid), a snapshot value of
	 * 0 (unspecified), or a value bigger than the normal maximum
	 * value, into the maximum allowed value.
	 *
	 * If some application really *needs* a bigger snapshot
	 * length, we should just increase MAXIMUM_SNAPLEN.
	 */
	if (p->snapshot <= 0 || p->snapshot > MAXIMUM_SNAPLEN)
		p->snapshot = MAXIMUM_SNAPLEN;

	pf->OrigMissed = -1;
	enmode = ENTSTAMP|ENNONEXCL;
	if (!p->opt.immediate)
		enmode |= ENBATCH;
	if (p->opt.promisc)
		enmode |= ENPROMISC;
	if (ioctl(p->fd, EIOCMBIS, (caddr_t)&enmode) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "EIOCMBIS");
		err = PCAP_ERROR;
		goto bad;
	}
#ifdef	ENCOPYALL
	/* Try to set COPYALL mode so that we see packets to ourself */
	enmode = ENCOPYALL;
	(void)ioctl(p->fd, EIOCMBIS, (caddr_t)&enmode);/* OK if this fails */
#endif
	/* set the backlog */
	if (ioctl(p->fd, EIOCSETW, (caddr_t)&backlog) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "EIOCSETW");
		err = PCAP_ERROR;
		goto bad;
	}
	/* discover interface type */
	if (ioctl(p->fd, EIOCDEVP, (caddr_t)&devparams) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "EIOCDEVP");
		err = PCAP_ERROR;
		goto bad;
	}
	/* HACK: to compile prior to Ultrix 4.2 */
#ifndef	ENDT_FDDI
#define	ENDT_FDDI	4
#endif
	switch (devparams.end_dev_type) {

	case ENDT_10MB:
		p->linktype = DLT_EN10MB;
		p->offset = 2;
		/*
		 * This is (presumably) a real Ethernet capture; give it a
		 * link-layer-type list with DLT_EN10MB and DLT_DOCSIS, so
		 * that an application can let you choose it, in case you're
		 * capturing DOCSIS traffic that a Cisco Cable Modem
		 * Termination System is putting out onto an Ethernet (it
		 * doesn't put an Ethernet header onto the wire, it puts raw
		 * DOCSIS frames out on the wire inside the low-level
		 * Ethernet framing).
		 */
		p->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (p->dlt_list != NULL) {
			p->dlt_list[0] = DLT_EN10MB;
			p->dlt_list[1] = DLT_DOCSIS;
			p->dlt_count = 2;
		}
		break;

	case ENDT_FDDI:
		p->linktype = DLT_FDDI;
		break;

#ifdef ENDT_SLIP
	case ENDT_SLIP:
		p->linktype = DLT_SLIP;
		break;
#endif

#ifdef ENDT_PPP
	case ENDT_PPP:
		p->linktype = DLT_PPP;
		break;
#endif

#ifdef ENDT_LOOPBACK
	case ENDT_LOOPBACK:
		/*
		 * It appears to use Ethernet framing, at least on
		 * Digital UNIX 4.0.
		 */
		p->linktype = DLT_EN10MB;
		p->offset = 2;
		break;
#endif

#ifdef ENDT_TRN
	case ENDT_TRN:
		p->linktype = DLT_IEEE802;
		break;
#endif

	default:
		/*
		 * XXX - what about ENDT_IEEE802?  The pfilt.h header
		 * file calls this "IEEE 802 networks (non-Ethernet)",
		 * but that doesn't specify a specific link layer type;
		 * it could be 802.4, or 802.5 (except that 802.5 is
		 * ENDT_TRN), or 802.6, or 802.11, or....  That's why
		 * DLT_IEEE802 was hijacked to mean Token Ring in various
		 * BSDs, and why we went along with that hijacking.
		 *
		 * XXX - what about ENDT_HDLC and ENDT_NULL?
		 * Presumably, as ENDT_OTHER is just "Miscellaneous
		 * framing", there's not much we can do, as that
		 * doesn't specify a particular type of header.
		 */
		pcap_snprintf(p->errbuf, PCAP_ERRBUF_SIZE,
		    "unknown data-link type %u", devparams.end_dev_type);
		err = PCAP_ERROR;
		goto bad;
	}
	/* set truncation */
	if (p->linktype == DLT_FDDI) {
		p->fddipad = PCAP_FDDIPAD;

		/* packetfilter includes the padding in the snapshot */
		p->snapshot += PCAP_FDDIPAD;
	} else
		p->fddipad = 0;
	if (ioctl(p->fd, EIOCTRUNCATE, (caddr_t)&p->snapshot) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "EIOCTRUNCATE");
		err = PCAP_ERROR;
		goto bad;
	}
	/* accept all packets */
	memset(&Filter, 0, sizeof(Filter));
	Filter.enf_Priority = 37;	/* anything > 2 */
	Filter.enf_FilterLen = 0;	/* means "always true" */
	if (ioctl(p->fd, EIOCSETF, (caddr_t)&Filter) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "EIOCSETF");
		err = PCAP_ERROR;
		goto bad;
	}

	if (p->opt.timeout != 0) {
		struct timeval timeout;
		timeout.tv_sec = p->opt.timeout / 1000;
		timeout.tv_usec = (p->opt.timeout * 1000) % 1000000;
		if (ioctl(p->fd, EIOCSRTIMEOUT, (caddr_t)&timeout) < 0) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "EIOCSRTIMEOUT");
			err = PCAP_ERROR;
			goto bad;
		}
	}

	p->bufsize = BUFSPACE;
	p->buffer = malloc(p->bufsize + p->offset);
	if (p->buffer == NULL) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		err = PCAP_ERROR;
		goto bad;
	}

	/*
	 * "select()" and "poll()" work on packetfilter devices.
	 */
	p->selectable_fd = p->fd;

	p->read_op = pcap_read_pf;
	p->inject_op = pcap_inject_pf;
	p->setfilter_op = pcap_setfilter_pf;
	p->setdirection_op = NULL;	/* Not implemented. */
	p->set_datalink_op = NULL;	/* can't change data link type */
	p->getnonblock_op = pcap_getnonblock_fd;
	p->setnonblock_op = pcap_setnonblock_fd;
	p->stats_op = pcap_stats_pf;

	return (0);
 bad:
	pcap_cleanup_live_common(p);
	return (err);
}