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
struct utsname {char* release; } ;
struct ifreq {int /*<<< orphan*/  ifr_name; } ;
struct bpf_dltlist {int /*<<< orphan*/  bfl_list; } ;
struct TYPE_5__ {scalar_t__ device; } ;
struct TYPE_6__ {int /*<<< orphan*/  errbuf; TYPE_1__ opt; } ;
typedef  TYPE_2__ pcap_t ;
typedef  char* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BIOCSETIF ; 
 int /*<<< orphan*/  DLT_NULL ; 
#define  ENETDOWN 129 
#define  ENXIO 128 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_IFACE_NOT_UP ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int bpf_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int find_802_11 (struct bpf_dltlist*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int get_dlt_list (int,int /*<<< orphan*/ ,struct bpf_dltlist*,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int monitor_mode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int uname (struct utsname*) ; 

__attribute__((used)) static int
pcap_can_set_rfmon_bpf(pcap_t *p)
{
#if defined(__APPLE__)
	struct utsname osinfo;
	struct ifreq ifr;
	int fd;
#ifdef BIOCGDLTLIST
	struct bpf_dltlist bdl;
#endif

	/*
	 * The joys of monitor mode on Mac OS X/OS X/macOS.
	 *
	 * Prior to 10.4, it's not supported at all.
	 *
	 * In 10.4, if adapter enN supports monitor mode, there's a
	 * wltN adapter corresponding to it; you open it, instead of
	 * enN, to get monitor mode.  You get whatever link-layer
	 * headers it supplies.
	 *
	 * In 10.5, and, we assume, later releases, if adapter enN
	 * supports monitor mode, it offers, among its selectable
	 * DLT_ values, values that let you get the 802.11 header;
	 * selecting one of those values puts the adapter into monitor
	 * mode (i.e., you can't get 802.11 headers except in monitor
	 * mode, and you can't get Ethernet headers in monitor mode).
	 */
	if (uname(&osinfo) == -1) {
		/*
		 * Can't get the OS version; just say "no".
		 */
		return (0);
	}
	/*
	 * We assume osinfo.sysname is "Darwin", because
	 * __APPLE__ is defined.  We just check the version.
	 */
	if (osinfo.release[0] < '8' && osinfo.release[1] == '.') {
		/*
		 * 10.3 (Darwin 7.x) or earlier.
		 * Monitor mode not supported.
		 */
		return (0);
	}
	if (osinfo.release[0] == '8' && osinfo.release[1] == '.') {
		/*
		 * 10.4 (Darwin 8.x).  s/en/wlt/, and check
		 * whether the device exists.
		 */
		if (strncmp(p->opt.device, "en", 2) != 0) {
			/*
			 * Not an enN device; no monitor mode.
			 */
			return (0);
		}
		fd = socket(AF_INET, SOCK_DGRAM, 0);
		if (fd == -1) {
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "socket");
			return (PCAP_ERROR);
		}
		strlcpy(ifr.ifr_name, "wlt", sizeof(ifr.ifr_name));
		strlcat(ifr.ifr_name, p->opt.device + 2, sizeof(ifr.ifr_name));
		if (ioctl(fd, SIOCGIFFLAGS, (char *)&ifr) < 0) {
			/*
			 * No such device?
			 */
			close(fd);
			return (0);
		}
		close(fd);
		return (1);
	}

#ifdef BIOCGDLTLIST
	/*
	 * Everything else is 10.5 or later; for those,
	 * we just open the enN device, and check whether
	 * we have any 802.11 devices.
	 *
	 * First, open a BPF device.
	 */
	fd = bpf_open(p->errbuf);
	if (fd < 0)
		return (fd);	/* fd is the appropriate error code */

	/*
	 * Now bind to the device.
	 */
	(void)strncpy(ifr.ifr_name, p->opt.device, sizeof(ifr.ifr_name));
	if (ioctl(fd, BIOCSETIF, (caddr_t)&ifr) < 0) {
		switch (errno) {

		case ENXIO:
			/*
			 * There's no such device.
			 */
			close(fd);
			return (PCAP_ERROR_NO_SUCH_DEVICE);

		case ENETDOWN:
			/*
			 * Return a "network down" indication, so that
			 * the application can report that rather than
			 * saying we had a mysterious failure and
			 * suggest that they report a problem to the
			 * libpcap developers.
			 */
			close(fd);
			return (PCAP_ERROR_IFACE_NOT_UP);

		default:
			pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
			    errno, "BIOCSETIF: %s", p->opt.device);
			close(fd);
			return (PCAP_ERROR);
		}
	}

	/*
	 * We know the default link type -- now determine all the DLTs
	 * this interface supports.  If this fails with EINVAL, it's
	 * not fatal; we just don't get to use the feature later.
	 * (We don't care about DLT_DOCSIS, so we pass DLT_NULL
	 * as the default DLT for this adapter.)
	 */
	if (get_dlt_list(fd, DLT_NULL, &bdl, p->errbuf) == PCAP_ERROR) {
		close(fd);
		return (PCAP_ERROR);
	}
	if (find_802_11(&bdl) != -1) {
		/*
		 * We have an 802.11 DLT, so we can set monitor mode.
		 */
		free(bdl.bfl_list);
		close(fd);
		return (1);
	}
	free(bdl.bfl_list);
	close(fd);
#endif /* BIOCGDLTLIST */
	return (0);
#elif defined(HAVE_BSD_IEEE80211)
	int ret;

	ret = monitor_mode(p, 0);
	if (ret == PCAP_ERROR_RFMON_NOTSUP)
		return (0);	/* not an error, just a "can't do" */
	if (ret == 0)
		return (1);	/* success */
	return (ret);
#else
	return (0);
#endif
}