#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ifrn_name; } ;
struct iwreq {TYPE_1__ ifr_ifrn; } ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int /*<<< orphan*/  errbuf; TYPE_2__ opt; } ;
typedef  TYPE_3__ pcap_t ;

/* Variables and functions */
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  PATH_MAX ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_NO_SUCH_DEVICE ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int /*<<< orphan*/  SIOCGIWMODE ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int get_mac80211_phydev (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct iwreq*) ; 
 scalar_t__ is_bonding_device (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  pcap_protocol (TYPE_3__*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
pcap_can_set_rfmon_linux(pcap_t *handle)
{
#ifdef HAVE_LIBNL
	char phydev_path[PATH_MAX+1];
	int ret;
#endif
#ifdef IW_MODE_MONITOR
	int sock_fd;
	struct iwreq ireq;
#endif

	if (strcmp(handle->opt.device, "any") == 0) {
		/*
		 * Monitor mode makes no sense on the "any" device.
		 */
		return 0;
	}

#ifdef HAVE_LIBNL
	/*
	 * Bleah.  There doesn't seem to be a way to ask a mac80211
	 * device, through libnl, whether it supports monitor mode;
	 * we'll just check whether the device appears to be a
	 * mac80211 device and, if so, assume the device supports
	 * monitor mode.
	 *
	 * wmaster devices don't appear to support the Wireless
	 * Extensions, but we can create a mon device for a
	 * wmaster device, so we don't bother checking whether
	 * a mac80211 device supports the Wireless Extensions.
	 */
	ret = get_mac80211_phydev(handle, handle->opt.device, phydev_path,
	    PATH_MAX);
	if (ret < 0)
		return ret;	/* error */
	if (ret == 1)
		return 1;	/* mac80211 device */
#endif

#ifdef IW_MODE_MONITOR
	/*
	 * Bleah.  There doesn't appear to be an ioctl to use to ask
	 * whether a device supports monitor mode; we'll just do
	 * SIOCGIWMODE and, if it succeeds, assume the device supports
	 * monitor mode.
	 *
	 * Open a socket on which to attempt to get the mode.
	 * (We assume that if we have Wireless Extensions support
	 * we also have PF_PACKET support.)
	 */
	sock_fd = socket(PF_PACKET, SOCK_RAW, pcap_protocol(handle));
	if (sock_fd == -1) {
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "socket");
		return PCAP_ERROR;
	}

	if (is_bonding_device(sock_fd, handle->opt.device)) {
		/* It's a bonding device, so don't even try. */
		close(sock_fd);
		return 0;
	}

	/*
	 * Attempt to get the current mode.
	 */
	strlcpy(ireq.ifr_ifrn.ifrn_name, handle->opt.device,
	    sizeof ireq.ifr_ifrn.ifrn_name);
	if (ioctl(sock_fd, SIOCGIWMODE, &ireq) != -1) {
		/*
		 * Well, we got the mode; assume we can set it.
		 */
		close(sock_fd);
		return 1;
	}
	if (errno == ENODEV) {
		/* The device doesn't even exist. */
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "SIOCGIWMODE failed");
		close(sock_fd);
		return PCAP_ERROR_NO_SUCH_DEVICE;
	}
	close(sock_fd);
#endif
	return 0;
}