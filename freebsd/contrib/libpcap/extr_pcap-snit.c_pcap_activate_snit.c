#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct strioctl {int ic_len; char* ic_dp; int /*<<< orphan*/  ic_cmd; int /*<<< orphan*/  ic_timout; } ;
struct ifreq {char* ifr_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  device; scalar_t__ rfmon; } ;
struct TYPE_7__ {int snapshot; int fd; int bufsize; int selectable_fd; int dlt_count; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; void** dlt_list; int /*<<< orphan*/  errbuf; int /*<<< orphan*/ * buffer; void* linktype; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  chunksize ;

/* Variables and functions */
 int BUFSPACE ; 
 int CHUNKSIZE ; 
 void* DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 scalar_t__ EACCES ; 
 scalar_t__ FLUSHR ; 
 int /*<<< orphan*/  INFTIM ; 
 int /*<<< orphan*/  I_FLUSH ; 
 int /*<<< orphan*/  I_PUSH ; 
 int /*<<< orphan*/  I_SRDOPT ; 
 int /*<<< orphan*/  I_STR ; 
 int MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  NIOCBIND ; 
 int /*<<< orphan*/  NIOCSCHUNK ; 
 int /*<<< orphan*/  NIOCSSNAP ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 scalar_t__ RMSGD ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  install_bpf_program ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ nit_setflags (TYPE_2__*) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  pcap_getnonblock_fd ; 
 int /*<<< orphan*/  pcap_inject_snit ; 
 int /*<<< orphan*/  pcap_read_snit ; 
 int /*<<< orphan*/  pcap_setnonblock_fd ; 
 int /*<<< orphan*/  pcap_stats_snit ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcap_activate_snit(pcap_t *p)
{
	struct strioctl si;		/* struct for ioctl() */
	struct ifreq ifr;		/* interface request struct */
	int chunksize = CHUNKSIZE;
	int fd;
	static const char dev[] = "/dev/nit";
	int err;

	if (p->opt.rfmon) {
		/*
		 * No monitor mode on SunOS 4.x (no Wi-Fi devices on
		 * hardware supported by SunOS 4.x).
		 */
		return (PCAP_ERROR_RFMON_NOTSUP);
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

	if (p->snapshot < 96)
		/*
		 * NIT requires a snapshot length of at least 96.
		 */
		p->snapshot = 96;

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
	 */
	p->fd = fd = open(dev, O_RDWR);
	if (fd < 0 && errno == EACCES)
		p->fd = fd = open(dev, O_RDONLY);
	if (fd < 0) {
		if (errno == EACCES)
			err = PCAP_ERROR_PERM_DENIED;
		else
			err = PCAP_ERROR;
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "%s", dev);
		goto bad;
	}

	/* arrange to get discrete messages from the STREAM and use NIT_BUF */
	if (ioctl(fd, I_SRDOPT, (char *)RMSGD) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "I_SRDOPT");
		err = PCAP_ERROR;
		goto bad;
	}
	if (ioctl(fd, I_PUSH, "nbuf") < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "push nbuf");
		err = PCAP_ERROR;
		goto bad;
	}
	/* set the chunksize */
	si.ic_cmd = NIOCSCHUNK;
	si.ic_timout = INFTIM;
	si.ic_len = sizeof(chunksize);
	si.ic_dp = (char *)&chunksize;
	if (ioctl(fd, I_STR, (char *)&si) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "NIOCSCHUNK");
		err = PCAP_ERROR;
		goto bad;
	}

	/* request the interface */
	strncpy(ifr.ifr_name, p->opt.device, sizeof(ifr.ifr_name));
	ifr.ifr_name[sizeof(ifr.ifr_name) - 1] = '\0';
	si.ic_cmd = NIOCBIND;
	si.ic_len = sizeof(ifr);
	si.ic_dp = (char *)&ifr;
	if (ioctl(fd, I_STR, (char *)&si) < 0) {
		/*
		 * XXX - is there an error that means "no such device"?
		 * Is there one that means "that device doesn't support
		 * STREAMS NIT"?
		 */
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "NIOCBIND: %s", ifr.ifr_name);
		err = PCAP_ERROR;
		goto bad;
	}

	/* set the snapshot length */
	si.ic_cmd = NIOCSSNAP;
	si.ic_len = sizeof(p->snapshot);
	si.ic_dp = (char *)&p->snapshot;
	if (ioctl(fd, I_STR, (char *)&si) < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "NIOCSSNAP");
		err = PCAP_ERROR;
		goto bad;
	}
	if (nit_setflags(p) < 0) {
		err = PCAP_ERROR;
		goto bad;
	}

	(void)ioctl(fd, I_FLUSH, (char *)FLUSHR);
	/*
	 * NIT supports only ethernets.
	 */
	p->linktype = DLT_EN10MB;

	p->bufsize = BUFSPACE;
	p->buffer = malloc(p->bufsize);
	if (p->buffer == NULL) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		err = PCAP_ERROR;
		goto bad;
	}

	/*
	 * "p->fd" is an FD for a STREAMS device, so "select()" and
	 * "poll()" should work on it.
	 */
	p->selectable_fd = p->fd;

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

	p->read_op = pcap_read_snit;
	p->inject_op = pcap_inject_snit;
	p->setfilter_op = install_bpf_program;	/* no kernel filtering */
	p->setdirection_op = NULL;	/* Not implemented. */
	p->set_datalink_op = NULL;	/* can't change data link type */
	p->getnonblock_op = pcap_getnonblock_fd;
	p->setnonblock_op = pcap_setnonblock_fd;
	p->stats_op = pcap_stats_snit;

	return (0);
 bad:
	pcap_cleanup_live_common(p);
	return (err);
}