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
typedef  scalar_t__ u_int ;
struct utsname {int /*<<< orphan*/  release; } ;
struct pcap_linux {int sock_packet; int vlan_offset; int /*<<< orphan*/  must_do_on_close; scalar_t__ cooked; } ;
struct ifreq {int ifr_flags; int /*<<< orphan*/  ifr_name; } ;
struct TYPE_7__ {char* device; scalar_t__ promisc; } ;
struct TYPE_8__ {int fd; int linktype; scalar_t__ bufsize; scalar_t__ offset; scalar_t__ snapshot; int /*<<< orphan*/  errbuf; TYPE_1__ opt; struct pcap_linux* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  ifr ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int /*<<< orphan*/  ETH_P_ALL ; 
 int IFF_PROMISC ; 
 scalar_t__ MAX_LINKHEADER_SIZE ; 
 int /*<<< orphan*/  MUST_CLEAR_PROMISC ; 
 int PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIOCGIFFLAGS ; 
 int /*<<< orphan*/  SIOCSIFFLAGS ; 
 int /*<<< orphan*/  SOCK_PACKET ; 
 int errno ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int iface_bind_old (int,char const*,int /*<<< orphan*/ ) ; 
 int iface_get_arptype (int,char const*,int /*<<< orphan*/ ) ; 
 int iface_get_mtu (int,char const*,int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  map_arphrd_to_dlt (TYPE_2__*,int,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_add_to_pcaps_to_close (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_do_addexit (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uname (struct utsname*) ; 

__attribute__((used)) static int
activate_old(pcap_t *handle)
{
	struct pcap_linux *handlep = handle->priv;
	int		err;
	int		arptype;
	struct ifreq	ifr;
	const char	*device = handle->opt.device;
	struct utsname	utsname;
	int		mtu;

	/* Open the socket */

	handle->fd = socket(PF_INET, SOCK_PACKET, htons(ETH_P_ALL));
	if (handle->fd == -1) {
		err = errno;
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    err, "socket");
		if (err == EPERM || err == EACCES) {
			/*
			 * You don't have permission to open the
			 * socket.
			 */
			return PCAP_ERROR_PERM_DENIED;
		} else {
			/*
			 * Other error.
			 */
			return PCAP_ERROR;
		}
	}

	/* It worked - we are using the old interface */
	handlep->sock_packet = 1;

	/* ...which means we get the link-layer header. */
	handlep->cooked = 0;

	/* Bind to the given device */

	if (strcmp(device, "any") == 0) {
		strlcpy(handle->errbuf, "pcap_activate: The \"any\" device isn't supported on 2.0[.x]-kernel systems",
			PCAP_ERRBUF_SIZE);
		return PCAP_ERROR;
	}
	if (iface_bind_old(handle->fd, device, handle->errbuf) == -1)
		return PCAP_ERROR;

	/*
	 * Try to get the link-layer type.
	 */
	arptype = iface_get_arptype(handle->fd, device, handle->errbuf);
	if (arptype < 0)
		return PCAP_ERROR;

	/*
	 * Try to find the DLT_ type corresponding to that
	 * link-layer type.
	 */
	map_arphrd_to_dlt(handle, handle->fd, arptype, device, 0);
	if (handle->linktype == -1) {
		pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
			 "unknown arptype %d", arptype);
		return PCAP_ERROR;
	}

	/* Go to promisc mode if requested */

	if (handle->opt.promisc) {
		memset(&ifr, 0, sizeof(ifr));
		strlcpy(ifr.ifr_name, device, sizeof(ifr.ifr_name));
		if (ioctl(handle->fd, SIOCGIFFLAGS, &ifr) == -1) {
			pcap_fmt_errmsg_for_errno(handle->errbuf,
			    PCAP_ERRBUF_SIZE, errno, "SIOCGIFFLAGS");
			return PCAP_ERROR;
		}
		if ((ifr.ifr_flags & IFF_PROMISC) == 0) {
			/*
			 * Promiscuous mode isn't currently on,
			 * so turn it on, and remember that
			 * we should turn it off when the
			 * pcap_t is closed.
			 */

			/*
			 * If we haven't already done so, arrange
			 * to have "pcap_close_all()" called when
			 * we exit.
			 */
			if (!pcap_do_addexit(handle)) {
				/*
				 * "atexit()" failed; don't put
				 * the interface in promiscuous
				 * mode, just give up.
				 */
				return PCAP_ERROR;
			}

			ifr.ifr_flags |= IFF_PROMISC;
			if (ioctl(handle->fd, SIOCSIFFLAGS, &ifr) == -1) {
				pcap_fmt_errmsg_for_errno(handle->errbuf,
				    PCAP_ERRBUF_SIZE, errno, "SIOCSIFFLAGS");
				return PCAP_ERROR;
			}
			handlep->must_do_on_close |= MUST_CLEAR_PROMISC;

			/*
			 * Add this to the list of pcaps
			 * to close when we exit.
			 */
			pcap_add_to_pcaps_to_close(handle);
		}
	}

	/*
	 * Compute the buffer size.
	 *
	 * We're using SOCK_PACKET, so this might be a 2.0[.x]
	 * kernel, and might require special handling - check.
	 */
	if (uname(&utsname) < 0 ||
	    strncmp(utsname.release, "2.0", 3) == 0) {
		/*
		 * Either we couldn't find out what kernel release
		 * this is, or it's a 2.0[.x] kernel.
		 *
		 * In the 2.0[.x] kernel, a "recvfrom()" on
		 * a SOCK_PACKET socket, with MSG_TRUNC set, will
		 * return the number of bytes read, so if we pass
		 * a length based on the snapshot length, it'll
		 * return the number of bytes from the packet
		 * copied to userland, not the actual length
		 * of the packet.
		 *
		 * This means that, for example, the IP dissector
		 * in tcpdump will get handed a packet length less
		 * than the length in the IP header, and will
		 * complain about "truncated-ip".
		 *
		 * So we don't bother trying to copy from the
		 * kernel only the bytes in which we're interested,
		 * but instead copy them all, just as the older
		 * versions of libpcap for Linux did.
		 *
		 * The buffer therefore needs to be big enough to
		 * hold the largest packet we can get from this
		 * device.  Unfortunately, we can't get the MRU
		 * of the network; we can only get the MTU.  The
		 * MTU may be too small, in which case a packet larger
		 * than the buffer size will be truncated *and* we
		 * won't get the actual packet size.
		 *
		 * However, if the snapshot length is larger than
		 * the buffer size based on the MTU, we use the
		 * snapshot length as the buffer size, instead;
		 * this means that with a sufficiently large snapshot
		 * length we won't artificially truncate packets
		 * to the MTU-based size.
		 *
		 * This mess just one of many problems with packet
		 * capture on 2.0[.x] kernels; you really want a
		 * 2.2[.x] or later kernel if you want packet capture
		 * to work well.
		 */
		mtu = iface_get_mtu(handle->fd, device, handle->errbuf);
		if (mtu == -1)
			return PCAP_ERROR;
		handle->bufsize = MAX_LINKHEADER_SIZE + mtu;
		if (handle->bufsize < (u_int)handle->snapshot)
			handle->bufsize = (u_int)handle->snapshot;
	} else {
		/*
		 * This is a 2.2[.x] or later kernel.
		 *
		 * We can safely pass "recvfrom()" a byte count
		 * based on the snapshot length.
		 */
		handle->bufsize = (u_int)handle->snapshot;
	}

	/*
	 * Default value for offset to align link-layer payload
	 * on a 4-byte boundary.
	 */
	handle->offset	 = 0;

	/*
	 * SOCK_PACKET sockets don't supply information from
	 * stripped VLAN tags.
	 */
	handlep->vlan_offset = -1; /* unknown */

	return 1;
}