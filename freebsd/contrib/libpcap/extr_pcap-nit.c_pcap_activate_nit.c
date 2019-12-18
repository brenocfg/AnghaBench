#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct sockaddr_nit {int /*<<< orphan*/  snit_ifname; int /*<<< orphan*/  snit_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  snit ;
struct TYPE_7__ {int /*<<< orphan*/  device; scalar_t__ rfmon; } ;
struct TYPE_8__ {int snapshot; int fd; int bufsize; int selectable_fd; int dlt_count; int /*<<< orphan*/  stats_op; int /*<<< orphan*/  setnonblock_op; int /*<<< orphan*/  getnonblock_op; int /*<<< orphan*/ * set_datalink_op; int /*<<< orphan*/ * setdirection_op; int /*<<< orphan*/  setfilter_op; int /*<<< orphan*/  inject_op; int /*<<< orphan*/  read_op; void** dlt_list; int /*<<< orphan*/  errbuf; int /*<<< orphan*/ * buffer; void* linktype; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NIT ; 
 int BUFSPACE ; 
 void* DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 int MAXIMUM_SNAPLEN ; 
 int /*<<< orphan*/  NITIFSIZ ; 
 int /*<<< orphan*/  NITPROTO_RAW ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  install_bpf_program ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nit_setflags (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcap_getnonblock_fd ; 
 int /*<<< orphan*/  pcap_inject_nit ; 
 int /*<<< orphan*/  pcap_read_nit ; 
 int /*<<< orphan*/  pcap_setnonblock_fd ; 
 int /*<<< orphan*/  pcap_stats_nit ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcap_activate_nit(pcap_t *p)
{
	int fd;
	struct sockaddr_nit snit;

	if (p->opt.rfmon) {
		/*
		 * No monitor mode on SunOS 3.x or earlier (no
		 * Wi-Fi *devices* for the hardware that supported
		 * them!).
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

	memset(p, 0, sizeof(*p));
	p->fd = fd = socket(AF_NIT, SOCK_RAW, NITPROTO_RAW);
	if (fd < 0) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "socket");
		goto bad;
	}
	snit.snit_family = AF_NIT;
	(void)strncpy(snit.snit_ifname, p->opt.device, NITIFSIZ);

	if (bind(fd, (struct sockaddr *)&snit, sizeof(snit))) {
		/*
		 * XXX - there's probably a particular bind error that
		 * means "there's no such device" and a particular bind
		 * error that means "that device doesn't support NIT";
		 * they might be the same error, if they both end up
		 * meaning "NIT doesn't know about that device".
		 */
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "bind: %s", snit.snit_ifname);
		goto bad;
	}
	if (nit_setflags(p) < 0)
		goto bad;

	/*
	 * NIT supports only ethernets.
	 */
	p->linktype = DLT_EN10MB;

	p->bufsize = BUFSPACE;
	p->buffer = malloc(p->bufsize);
	if (p->buffer == NULL) {
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "malloc");
		goto bad;
	}

	/*
	 * "p->fd" is a socket, so "select()" should work on it.
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

	p->read_op = pcap_read_nit;
	p->inject_op = pcap_inject_nit;
	p->setfilter_op = install_bpf_program;	/* no kernel filtering */
	p->setdirection_op = NULL;	/* Not implemented. */
	p->set_datalink_op = NULL;	/* can't change data link type */
	p->getnonblock_op = pcap_getnonblock_fd;
	p->setnonblock_op = pcap_setnonblock_fd;
	p->stats_op = pcap_stats_nit;

	return (0);
 bad:
	pcap_cleanup_live_common(p);
	return (PCAP_ERROR);
}