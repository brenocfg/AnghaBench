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
struct ifreq {scalar_t__ ifr_name; } ;
struct TYPE_4__ {scalar_t__ device; scalar_t__ rfmon; } ;
struct TYPE_5__ {TYPE_1__ opt; int /*<<< orphan*/  errbuf; } ;
typedef  TYPE_2__ pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ ENETDOWN ; 
 int ENXIO ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_IFACE_NOT_UP ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,scalar_t__,scalar_t__,char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  strlcpy (scalar_t__,char*,int) ; 
 scalar_t__ strncmp (scalar_t__,char*,int) ; 

__attribute__((used)) static int
check_setif_failure(pcap_t *p, int error)
{
#ifdef __APPLE__
	int fd;
	struct ifreq ifr;
	int err;
#endif

	if (error == ENXIO) {
		/*
		 * No such device exists.
		 */
#ifdef __APPLE__
		if (p->opt.rfmon && strncmp(p->opt.device, "wlt", 3) == 0) {
			/*
			 * Monitor mode was requested, and we're trying
			 * to open a "wltN" device.  Assume that this
			 * is 10.4 and that we were asked to open an
			 * "enN" device; if that device exists, return
			 * "monitor mode not supported on the device".
			 */
			fd = socket(AF_INET, SOCK_DGRAM, 0);
			if (fd != -1) {
				strlcpy(ifr.ifr_name, "en",
				    sizeof(ifr.ifr_name));
				strlcat(ifr.ifr_name, p->opt.device + 3,
				    sizeof(ifr.ifr_name));
				if (ioctl(fd, SIOCGIFFLAGS, (char *)&ifr) < 0) {
					/*
					 * We assume this failed because
					 * the underlying device doesn't
					 * exist.
					 */
					err = PCAP_ERROR_NO_SUCH_DEVICE;
					pcap_fmt_errmsg_for_errno(p->errbuf,
					    PCAP_ERRBUF_SIZE, errno,
					    "SIOCGIFFLAGS on %s failed",
					    ifr.ifr_name);
				} else {
					/*
					 * The underlying "enN" device
					 * exists, but there's no
					 * corresponding "wltN" device;
					 * that means that the "enN"
					 * device doesn't support
					 * monitor mode, probably because
					 * it's an Ethernet device rather
					 * than a wireless device.
					 */
					err = PCAP_ERROR_RFMON_NOTSUP;
				}
				close(fd);
			} else {
				/*
				 * We can't find out whether there's
				 * an underlying "enN" device, so
				 * just report "no such device".
				 */
				err = PCAP_ERROR_NO_SUCH_DEVICE;
				pcap_fmt_errmsg_for_errno(p->errbuf,
				    errno, PCAP_ERRBUF_SIZE,
				    "socket() failed");
			}
			return (err);
		}
#endif
		/*
		 * No such device.
		 */
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "BIOCSETIF failed");
		return (PCAP_ERROR_NO_SUCH_DEVICE);
	} else if (errno == ENETDOWN) {
		/*
		 * Return a "network down" indication, so that
		 * the application can report that rather than
		 * saying we had a mysterious failure and
		 * suggest that they report a problem to the
		 * libpcap developers.
		 */
		return (PCAP_ERROR_IFACE_NOT_UP);
	} else {
		/*
		 * Some other error; fill in the error string, and
		 * return PCAP_ERROR.
		 */
		pcap_fmt_errmsg_for_errno(p->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "BIOCSETIF: %s", p->opt.device);
		return (PCAP_ERROR);
	}
}