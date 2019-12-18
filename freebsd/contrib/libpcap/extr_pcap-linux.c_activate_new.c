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
typedef  int /*<<< orphan*/  val ;
struct pcap_linux {int cooked; char* mondevice; int ifindex; int vlan_offset; void* lo_ifindex; scalar_t__ sock_packet; } ;
typedef  int packet_mreq ;
typedef  int socklen_t ;
struct TYPE_7__ {char* device; scalar_t__ tstamp_precision; scalar_t__ promisc; scalar_t__ rfmon; } ;
struct TYPE_8__ {int linktype; scalar_t__ snapshot; scalar_t__ bufsize; int fd; int /*<<< orphan*/  bpf_codegen_flags; int /*<<< orphan*/  errbuf; TYPE_1__ opt; scalar_t__ offset; scalar_t__ dlt_count; int /*<<< orphan*/ * dlt_list; struct pcap_linux* priv; } ;
typedef  TYPE_2__ pcap_t ;
typedef  int /*<<< orphan*/  nsec_tstamps ;
typedef  int /*<<< orphan*/  mr ;
typedef  int /*<<< orphan*/  bpf_extensions ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_SPECIAL_VLAN_HANDLING ; 
#define  DLT_EN10MB 129 
 int DLT_LINUX_IRDA ; 
 int DLT_LINUX_LAPD ; 
#define  DLT_LINUX_SLL 128 
 int DLT_NETLINK ; 
 scalar_t__ EACCES ; 
 scalar_t__ EAFNOSUPPORT ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOPROTOOPT ; 
 scalar_t__ EPERM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  PACKET_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  PACKET_AUXDATA ; 
 int /*<<< orphan*/  PACKET_MR_PROMISC ; 
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int PCAP_ERROR ; 
 int PCAP_ERROR_PERM_DENIED ; 
 int PCAP_ERROR_RFMON_NOTSUP ; 
 scalar_t__ PCAP_TSTAMP_PRECISION_NANO ; 
 int /*<<< orphan*/  PF_PACKET ; 
 int SKF_AD_VLAN_TAG_PRESENT ; 
 scalar_t__ SLL_HDR_LEN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOL_PACKET ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BPF_EXTENSIONS ; 
 int /*<<< orphan*/  SO_TIMESTAMPNS ; 
 scalar_t__ VLAN_TAG_LEN ; 
 int close (int) ; 
 int /*<<< orphan*/  ebuf ; 
 int enter_rfmon_mode (TYPE_2__*,int,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int iface_bind (int,int,int /*<<< orphan*/ ,int) ; 
 int iface_get_arptype (int,char const*,int /*<<< orphan*/ ) ; 
 void* iface_get_id (int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_arphrd_to_dlt (TYPE_2__*,int,int,char const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_fmt_errmsg_for_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int pcap_protocol (TYPE_2__*) ; 
 int /*<<< orphan*/  pcap_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

__attribute__((used)) static int
activate_new(pcap_t *handle)
{
#ifdef HAVE_PF_PACKET_SOCKETS
	struct pcap_linux *handlep = handle->priv;
	const char		*device = handle->opt.device;
	int			is_any_device = (strcmp(device, "any") == 0);
	int			protocol = pcap_protocol(handle);
	int			sock_fd = -1, arptype;
#ifdef HAVE_PACKET_AUXDATA
	int			val;
#endif
	int			err = 0;
	struct packet_mreq	mr;
#if defined(SO_BPF_EXTENSIONS) && defined(SKF_AD_VLAN_TAG_PRESENT)
	int			bpf_extensions;
	socklen_t		len = sizeof(bpf_extensions);
#endif

	/*
	 * Open a socket with protocol family packet. If the
	 * "any" device was specified, we open a SOCK_DGRAM
	 * socket for the cooked interface, otherwise we first
	 * try a SOCK_RAW socket for the raw interface.
	 */
	sock_fd = is_any_device ?
		socket(PF_PACKET, SOCK_DGRAM, protocol) :
		socket(PF_PACKET, SOCK_RAW, protocol);

	if (sock_fd == -1) {
		if (errno == EINVAL || errno == EAFNOSUPPORT) {
			/*
			 * We don't support PF_PACKET/SOCK_whatever
			 * sockets; try the old mechanism.
			 */
			return 0;
		}

		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "socket");
		if (errno == EPERM || errno == EACCES) {
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

	/* It seems the kernel supports the new interface. */
	handlep->sock_packet = 0;

	/*
	 * Get the interface index of the loopback device.
	 * If the attempt fails, don't fail, just set the
	 * "handlep->lo_ifindex" to -1.
	 *
	 * XXX - can there be more than one device that loops
	 * packets back, i.e. devices other than "lo"?  If so,
	 * we'd need to find them all, and have an array of
	 * indices for them, and check all of them in
	 * "pcap_read_packet()".
	 */
	handlep->lo_ifindex = iface_get_id(sock_fd, "lo", handle->errbuf);

	/*
	 * Default value for offset to align link-layer payload
	 * on a 4-byte boundary.
	 */
	handle->offset	 = 0;

	/*
	 * What kind of frames do we have to deal with? Fall back
	 * to cooked mode if we have an unknown interface type
	 * or a type we know doesn't work well in raw mode.
	 */
	if (!is_any_device) {
		/* Assume for now we don't need cooked mode. */
		handlep->cooked = 0;

		if (handle->opt.rfmon) {
			/*
			 * We were asked to turn on monitor mode.
			 * Do so before we get the link-layer type,
			 * because entering monitor mode could change
			 * the link-layer type.
			 */
			err = enter_rfmon_mode(handle, sock_fd, device);
			if (err < 0) {
				/* Hard failure */
				close(sock_fd);
				return err;
			}
			if (err == 0) {
				/*
				 * Nothing worked for turning monitor mode
				 * on.
				 */
				close(sock_fd);
				return PCAP_ERROR_RFMON_NOTSUP;
			}

			/*
			 * Either monitor mode has been turned on for
			 * the device, or we've been given a different
			 * device to open for monitor mode.  If we've
			 * been given a different device, use it.
			 */
			if (handlep->mondevice != NULL)
				device = handlep->mondevice;
		}
		arptype	= iface_get_arptype(sock_fd, device, handle->errbuf);
		if (arptype < 0) {
			close(sock_fd);
			return arptype;
		}
		map_arphrd_to_dlt(handle, sock_fd, arptype, device, 1);
		if (handle->linktype == -1 ||
		    handle->linktype == DLT_LINUX_SLL ||
		    handle->linktype == DLT_LINUX_IRDA ||
		    handle->linktype == DLT_LINUX_LAPD ||
		    handle->linktype == DLT_NETLINK ||
		    (handle->linktype == DLT_EN10MB &&
		     (strncmp("isdn", device, 4) == 0 ||
		      strncmp("isdY", device, 4) == 0))) {
			/*
			 * Unknown interface type (-1), or a
			 * device we explicitly chose to run
			 * in cooked mode (e.g., PPP devices),
			 * or an ISDN device (whose link-layer
			 * type we can only determine by using
			 * APIs that may be different on different
			 * kernels) - reopen in cooked mode.
			 */
			if (close(sock_fd) == -1) {
				pcap_fmt_errmsg_for_errno(handle->errbuf,
				    PCAP_ERRBUF_SIZE, errno, "close");
				return PCAP_ERROR;
			}
			sock_fd = socket(PF_PACKET, SOCK_DGRAM, protocol);
			if (sock_fd == -1) {
				pcap_fmt_errmsg_for_errno(handle->errbuf,
				    PCAP_ERRBUF_SIZE, errno, "socket");
				if (errno == EPERM || errno == EACCES) {
					/*
					 * You don't have permission to
					 * open the socket.
					 */
					return PCAP_ERROR_PERM_DENIED;
				} else {
					/*
					 * Other error.
					 */
					return PCAP_ERROR;
				}
			}
			handlep->cooked = 1;

			/*
			 * Get rid of any link-layer type list
			 * we allocated - this only supports cooked
			 * capture.
			 */
			if (handle->dlt_list != NULL) {
				free(handle->dlt_list);
				handle->dlt_list = NULL;
				handle->dlt_count = 0;
			}

			if (handle->linktype == -1) {
				/*
				 * Warn that we're falling back on
				 * cooked mode; we may want to
				 * update "map_arphrd_to_dlt()"
				 * to handle the new type.
				 */
				pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE,
					"arptype %d not "
					"supported by libpcap - "
					"falling back to cooked "
					"socket",
					arptype);
			}

			/*
			 * IrDA capture is not a real "cooked" capture,
			 * it's IrLAP frames, not IP packets.  The
			 * same applies to LAPD capture.
			 */
			if (handle->linktype != DLT_LINUX_IRDA &&
			    handle->linktype != DLT_LINUX_LAPD &&
			    handle->linktype != DLT_NETLINK)
				handle->linktype = DLT_LINUX_SLL;
		}

		handlep->ifindex = iface_get_id(sock_fd, device,
		    handle->errbuf);
		if (handlep->ifindex == -1) {
			close(sock_fd);
			return PCAP_ERROR;
		}

		if ((err = iface_bind(sock_fd, handlep->ifindex,
		    handle->errbuf, protocol)) != 1) {
		    	close(sock_fd);
			if (err < 0)
				return err;
			else
				return 0;	/* try old mechanism */
		}
	} else {
		/*
		 * The "any" device.
		 */
		if (handle->opt.rfmon) {
			/*
			 * It doesn't support monitor mode.
			 */
			close(sock_fd);
			return PCAP_ERROR_RFMON_NOTSUP;
		}

		/*
		 * It uses cooked mode.
		 */
		handlep->cooked = 1;
		handle->linktype = DLT_LINUX_SLL;

		/*
		 * We're not bound to a device.
		 * For now, we're using this as an indication
		 * that we can't transmit; stop doing that only
		 * if we figure out how to transmit in cooked
		 * mode.
		 */
		handlep->ifindex = -1;
	}

	/*
	 * Select promiscuous mode on if "promisc" is set.
	 *
	 * Do not turn allmulti mode on if we don't select
	 * promiscuous mode - on some devices (e.g., Orinoco
	 * wireless interfaces), allmulti mode isn't supported
	 * and the driver implements it by turning promiscuous
	 * mode on, and that screws up the operation of the
	 * card as a normal networking interface, and on no
	 * other platform I know of does starting a non-
	 * promiscuous capture affect which multicast packets
	 * are received by the interface.
	 */

	/*
	 * Hmm, how can we set promiscuous mode on all interfaces?
	 * I am not sure if that is possible at all.  For now, we
	 * silently ignore attempts to turn promiscuous mode on
	 * for the "any" device (so you don't have to explicitly
	 * disable it in programs such as tcpdump).
	 */

	if (!is_any_device && handle->opt.promisc) {
		memset(&mr, 0, sizeof(mr));
		mr.mr_ifindex = handlep->ifindex;
		mr.mr_type    = PACKET_MR_PROMISC;
		if (setsockopt(sock_fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP,
		    &mr, sizeof(mr)) == -1) {
			pcap_fmt_errmsg_for_errno(handle->errbuf,
			    PCAP_ERRBUF_SIZE, errno, "setsockopt");
			close(sock_fd);
			return PCAP_ERROR;
		}
	}

	/* Enable auxillary data if supported and reserve room for
	 * reconstructing VLAN headers. */
#ifdef HAVE_PACKET_AUXDATA
	val = 1;
	if (setsockopt(sock_fd, SOL_PACKET, PACKET_AUXDATA, &val,
		       sizeof(val)) == -1 && errno != ENOPROTOOPT) {
		pcap_fmt_errmsg_for_errno(handle->errbuf, PCAP_ERRBUF_SIZE,
		    errno, "setsockopt");
		close(sock_fd);
		return PCAP_ERROR;
	}
	handle->offset += VLAN_TAG_LEN;
#endif /* HAVE_PACKET_AUXDATA */

	/*
	 * This is a 2.2[.x] or later kernel (we know that
	 * because we're not using a SOCK_PACKET socket -
	 * PF_PACKET is supported only in 2.2 and later
	 * kernels).
	 *
	 * We can safely pass "recvfrom()" a byte count
	 * based on the snapshot length.
	 *
	 * If we're in cooked mode, make the snapshot length
	 * large enough to hold a "cooked mode" header plus
	 * 1 byte of packet data (so we don't pass a byte
	 * count of 0 to "recvfrom()").
	 */
	if (handlep->cooked) {
		if (handle->snapshot < SLL_HDR_LEN + 1)
			handle->snapshot = SLL_HDR_LEN + 1;
	}
	handle->bufsize = handle->snapshot;

	/*
	 * Set the offset at which to insert VLAN tags.
	 * That should be the offset of the type field.
	 */
	switch (handle->linktype) {

	case DLT_EN10MB:
		/*
		 * The type field is after the destination and source
		 * MAC address.
		 */
		handlep->vlan_offset = 2 * ETH_ALEN;
		break;

	case DLT_LINUX_SLL:
		/*
		 * The type field is in the last 2 bytes of the
		 * DLT_LINUX_SLL header.
		 */
		handlep->vlan_offset = SLL_HDR_LEN - 2;
		break;

	default:
		handlep->vlan_offset = -1; /* unknown */
		break;
	}

#if defined(SIOCGSTAMPNS) && defined(SO_TIMESTAMPNS)
	if (handle->opt.tstamp_precision == PCAP_TSTAMP_PRECISION_NANO) {
		int nsec_tstamps = 1;

		if (setsockopt(sock_fd, SOL_SOCKET, SO_TIMESTAMPNS, &nsec_tstamps, sizeof(nsec_tstamps)) < 0) {
			pcap_snprintf(handle->errbuf, PCAP_ERRBUF_SIZE, "setsockopt: unable to set SO_TIMESTAMPNS");
			close(sock_fd);
			return PCAP_ERROR;
		}
	}
#endif /* defined(SIOCGSTAMPNS) && defined(SO_TIMESTAMPNS) */

	/*
	 * We've succeeded. Save the socket FD in the pcap structure.
	 */
	handle->fd = sock_fd;

#if defined(SO_BPF_EXTENSIONS) && defined(SKF_AD_VLAN_TAG_PRESENT)
	/*
	 * Can we generate special code for VLAN checks?
	 * (XXX - what if we need the special code but it's not supported
	 * by the OS?  Is that possible?)
	 */
	if (getsockopt(sock_fd, SOL_SOCKET, SO_BPF_EXTENSIONS,
	    &bpf_extensions, &len) == 0) {
		if (bpf_extensions >= SKF_AD_VLAN_TAG_PRESENT) {
			/*
			 * Yes, we can.  Request that we do so.
			 */
			handle->bpf_codegen_flags |= BPF_SPECIAL_VLAN_HANDLING;
		}
	}
#endif /* defined(SO_BPF_EXTENSIONS) && defined(SKF_AD_VLAN_TAG_PRESENT) */

	return 1;
#else /* HAVE_PF_PACKET_SOCKETS */
	strlcpy(ebuf,
		"New packet capturing interface not supported by build "
		"environment", PCAP_ERRBUF_SIZE);
	return 0;
#endif /* HAVE_PF_PACKET_SOCKETS */
}