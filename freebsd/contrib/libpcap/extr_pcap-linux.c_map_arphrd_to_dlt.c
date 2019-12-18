#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
struct TYPE_3__ {int linktype; int dlt_count; int offset; void** dlt_list; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
#define  ARPHRD_ADAPT 166 
#define  ARPHRD_ARCNET 165 
#define  ARPHRD_ATM 164 
#define  ARPHRD_AX25 163 
#define  ARPHRD_CAN 162 
#define  ARPHRD_CHAOS 161 
#define  ARPHRD_CISCO 160 
#define  ARPHRD_CSLIP 159 
#define  ARPHRD_CSLIP6 158 
#define  ARPHRD_DLCI 157 
#define  ARPHRD_EETHER 156 
#define  ARPHRD_ETHER 155 
#define  ARPHRD_FCAL 154 
#define  ARPHRD_FCFABRIC 153 
#define  ARPHRD_FCPL 152 
#define  ARPHRD_FCPP 151 
#define  ARPHRD_FDDI 150 
#define  ARPHRD_FRAD 149 
#define  ARPHRD_IEEE802 148 
#define  ARPHRD_IEEE80211 147 
#define  ARPHRD_IEEE80211_PRISM 146 
#define  ARPHRD_IEEE80211_RADIOTAP 145 
#define  ARPHRD_IEEE802154 144 
#define  ARPHRD_IEEE802_TR 143 
#define  ARPHRD_IRDA 142 
#define  ARPHRD_LAPD 141 
#define  ARPHRD_LOCALTLK 140 
#define  ARPHRD_LOOPBACK 139 
#define  ARPHRD_METRICOM 138 
#define  ARPHRD_NETLINK 137 
#define  ARPHRD_NONE 136 
#define  ARPHRD_PPP 135 
#define  ARPHRD_PRONET 134 
#define  ARPHRD_RAWHDLC 133 
#define  ARPHRD_SIT 132 
#define  ARPHRD_SLIP 131 
#define  ARPHRD_SLIP6 130 
#define  ARPHRD_TUNNEL 129 
#define  ARPHRD_VSOCKMON 128 
 int DLT_ARCNET_LINUX ; 
 int DLT_AX25_KISS ; 
 int DLT_CHAOS ; 
 int DLT_C_HDLC ; 
 void* DLT_DOCSIS ; 
 void* DLT_EN10MB ; 
 int DLT_EN3MB ; 
 void* DLT_FC_2 ; 
 void* DLT_FC_2_WITH_FRAME_DELIMS ; 
 int DLT_FDDI ; 
 int DLT_FRELAY ; 
 int DLT_IEEE802 ; 
 int DLT_IEEE802_11 ; 
 int DLT_IEEE802_11_RADIO ; 
 int DLT_IEEE802_15_4_NOFCS ; 
 void* DLT_IP_OVER_FC ; 
 int DLT_LINUX_IRDA ; 
 int DLT_LINUX_LAPD ; 
 void* DLT_LINUX_SLL ; 
 int DLT_LTALK ; 
 int DLT_NETLINK ; 
 int DLT_PRISM_HEADER ; 
 int DLT_PRONET ; 
 void* DLT_RAW ; 
 int DLT_VSOCK ; 
 int /*<<< orphan*/  is_wifi (int,char const*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 

__attribute__((used)) static void map_arphrd_to_dlt(pcap_t *handle, int sock_fd, int arptype,
			      const char *device, int cooked_ok)
{
	static const char cdma_rmnet[] = "cdma_rmnet";

	switch (arptype) {

	case ARPHRD_ETHER:
		/*
		 * For various annoying reasons having to do with DHCP
		 * software, some versions of Android give the mobile-
		 * phone-network interface an ARPHRD_ value of
		 * ARPHRD_ETHER, even though the packets supplied by
		 * that interface have no link-layer header, and begin
		 * with an IP header, so that the ARPHRD_ value should
		 * be ARPHRD_NONE.
		 *
		 * Detect those devices by checking the device name, and
		 * use DLT_RAW for them.
		 */
		if (strncmp(device, cdma_rmnet, sizeof cdma_rmnet - 1) == 0) {
			handle->linktype = DLT_RAW;
			return;
		}

		/*
		 * Is this a real Ethernet device?  If so, give it a
		 * link-layer-type list with DLT_EN10MB and DLT_DOCSIS, so
		 * that an application can let you choose it, in case you're
		 * capturing DOCSIS traffic that a Cisco Cable Modem
		 * Termination System is putting out onto an Ethernet (it
		 * doesn't put an Ethernet header onto the wire, it puts raw
		 * DOCSIS frames out on the wire inside the low-level
		 * Ethernet framing).
		 *
		 * XXX - are there any other sorts of "fake Ethernet" that
		 * have ARPHRD_ETHER but that shouldn't offer DLT_DOCSIS as
		 * a Cisco CMTS won't put traffic onto it or get traffic
		 * bridged onto it?  ISDN is handled in "activate_new()",
		 * as we fall back on cooked mode there, and we use
		 * is_wifi() to check for 802.11 devices; are there any
		 * others?
		 */
		if (!is_wifi(sock_fd, device)) {
			/*
			 * It's not a Wi-Fi device; offer DOCSIS.
			 */
			handle->dlt_list = (u_int *) malloc(sizeof(u_int) * 2);
			/*
			 * If that fails, just leave the list empty.
			 */
			if (handle->dlt_list != NULL) {
				handle->dlt_list[0] = DLT_EN10MB;
				handle->dlt_list[1] = DLT_DOCSIS;
				handle->dlt_count = 2;
			}
		}
		/* FALLTHROUGH */

	case ARPHRD_METRICOM:
	case ARPHRD_LOOPBACK:
		handle->linktype = DLT_EN10MB;
		handle->offset = 2;
		break;

	case ARPHRD_EETHER:
		handle->linktype = DLT_EN3MB;
		break;

	case ARPHRD_AX25:
		handle->linktype = DLT_AX25_KISS;
		break;

	case ARPHRD_PRONET:
		handle->linktype = DLT_PRONET;
		break;

	case ARPHRD_CHAOS:
		handle->linktype = DLT_CHAOS;
		break;
#ifndef ARPHRD_CAN
#define ARPHRD_CAN 280
#endif
	case ARPHRD_CAN:
		/*
		 * Map this to DLT_LINUX_SLL; that way, CAN frames will
		 * have ETH_P_CAN/LINUX_SLL_P_CAN as the protocol and
		 * CAN FD frames will have ETH_P_CANFD/LINUX_SLL_P_CANFD
		 * as the protocol, so they can be distinguished by the
		 * protocol in the SLL header.
		 */
		handle->linktype = DLT_LINUX_SLL;
		break;

#ifndef ARPHRD_IEEE802_TR
#define ARPHRD_IEEE802_TR 800	/* From Linux 2.4 */
#endif
	case ARPHRD_IEEE802_TR:
	case ARPHRD_IEEE802:
		handle->linktype = DLT_IEEE802;
		handle->offset = 2;
		break;

	case ARPHRD_ARCNET:
		handle->linktype = DLT_ARCNET_LINUX;
		break;

#ifndef ARPHRD_FDDI	/* From Linux 2.2.13 */
#define ARPHRD_FDDI	774
#endif
	case ARPHRD_FDDI:
		handle->linktype = DLT_FDDI;
		handle->offset = 3;
		break;

#ifndef ARPHRD_ATM  /* FIXME: How to #include this? */
#define ARPHRD_ATM 19
#endif
	case ARPHRD_ATM:
		/*
		 * The Classical IP implementation in ATM for Linux
		 * supports both what RFC 1483 calls "LLC Encapsulation",
		 * in which each packet has an LLC header, possibly
		 * with a SNAP header as well, prepended to it, and
		 * what RFC 1483 calls "VC Based Multiplexing", in which
		 * different virtual circuits carry different network
		 * layer protocols, and no header is prepended to packets.
		 *
		 * They both have an ARPHRD_ type of ARPHRD_ATM, so
		 * you can't use the ARPHRD_ type to find out whether
		 * captured packets will have an LLC header, and,
		 * while there's a socket ioctl to *set* the encapsulation
		 * type, there's no ioctl to *get* the encapsulation type.
		 *
		 * This means that
		 *
		 *	programs that dissect Linux Classical IP frames
		 *	would have to check for an LLC header and,
		 *	depending on whether they see one or not, dissect
		 *	the frame as LLC-encapsulated or as raw IP (I
		 *	don't know whether there's any traffic other than
		 *	IP that would show up on the socket, or whether
		 *	there's any support for IPv6 in the Linux
		 *	Classical IP code);
		 *
		 *	filter expressions would have to compile into
		 *	code that checks for an LLC header and does
		 *	the right thing.
		 *
		 * Both of those are a nuisance - and, at least on systems
		 * that support PF_PACKET sockets, we don't have to put
		 * up with those nuisances; instead, we can just capture
		 * in cooked mode.  That's what we'll do, if we can.
		 * Otherwise, we'll just fail.
		 */
		if (cooked_ok)
			handle->linktype = DLT_LINUX_SLL;
		else
			handle->linktype = -1;
		break;

#ifndef ARPHRD_IEEE80211  /* From Linux 2.4.6 */
#define ARPHRD_IEEE80211 801
#endif
	case ARPHRD_IEEE80211:
		handle->linktype = DLT_IEEE802_11;
		break;

#ifndef ARPHRD_IEEE80211_PRISM  /* From Linux 2.4.18 */
#define ARPHRD_IEEE80211_PRISM 802
#endif
	case ARPHRD_IEEE80211_PRISM:
		handle->linktype = DLT_PRISM_HEADER;
		break;

#ifndef ARPHRD_IEEE80211_RADIOTAP /* new */
#define ARPHRD_IEEE80211_RADIOTAP 803
#endif
	case ARPHRD_IEEE80211_RADIOTAP:
		handle->linktype = DLT_IEEE802_11_RADIO;
		break;

	case ARPHRD_PPP:
		/*
		 * Some PPP code in the kernel supplies no link-layer
		 * header whatsoever to PF_PACKET sockets; other PPP
		 * code supplies PPP link-layer headers ("syncppp.c");
		 * some PPP code might supply random link-layer
		 * headers (PPP over ISDN - there's code in Ethereal,
		 * for example, to cope with PPP-over-ISDN captures
		 * with which the Ethereal developers have had to cope,
		 * heuristically trying to determine which of the
		 * oddball link-layer headers particular packets have).
		 *
		 * As such, we just punt, and run all PPP interfaces
		 * in cooked mode, if we can; otherwise, we just treat
		 * it as DLT_RAW, for now - if somebody needs to capture,
		 * on a 2.0[.x] kernel, on PPP devices that supply a
		 * link-layer header, they'll have to add code here to
		 * map to the appropriate DLT_ type (possibly adding a
		 * new DLT_ type, if necessary).
		 */
		if (cooked_ok)
			handle->linktype = DLT_LINUX_SLL;
		else {
			/*
			 * XXX - handle ISDN types here?  We can't fall
			 * back on cooked sockets, so we'd have to
			 * figure out from the device name what type of
			 * link-layer encapsulation it's using, and map
			 * that to an appropriate DLT_ value, meaning
			 * we'd map "isdnN" devices to DLT_RAW (they
			 * supply raw IP packets with no link-layer
			 * header) and "isdY" devices to a new DLT_I4L_IP
			 * type that has only an Ethernet packet type as
			 * a link-layer header.
			 *
			 * But sometimes we seem to get random crap
			 * in the link-layer header when capturing on
			 * ISDN devices....
			 */
			handle->linktype = DLT_RAW;
		}
		break;

#ifndef ARPHRD_CISCO
#define ARPHRD_CISCO 513 /* previously ARPHRD_HDLC */
#endif
	case ARPHRD_CISCO:
		handle->linktype = DLT_C_HDLC;
		break;

	/* Not sure if this is correct for all tunnels, but it
	 * works for CIPE */
	case ARPHRD_TUNNEL:
#ifndef ARPHRD_SIT
#define ARPHRD_SIT 776	/* From Linux 2.2.13 */
#endif
	case ARPHRD_SIT:
	case ARPHRD_CSLIP:
	case ARPHRD_SLIP6:
	case ARPHRD_CSLIP6:
	case ARPHRD_ADAPT:
	case ARPHRD_SLIP:
#ifndef ARPHRD_RAWHDLC
#define ARPHRD_RAWHDLC 518
#endif
	case ARPHRD_RAWHDLC:
#ifndef ARPHRD_DLCI
#define ARPHRD_DLCI 15
#endif
	case ARPHRD_DLCI:
		/*
		 * XXX - should some of those be mapped to DLT_LINUX_SLL
		 * instead?  Should we just map all of them to DLT_LINUX_SLL?
		 */
		handle->linktype = DLT_RAW;
		break;

#ifndef ARPHRD_FRAD
#define ARPHRD_FRAD 770
#endif
	case ARPHRD_FRAD:
		handle->linktype = DLT_FRELAY;
		break;

	case ARPHRD_LOCALTLK:
		handle->linktype = DLT_LTALK;
		break;

	case 18:
		/*
		 * RFC 4338 defines an encapsulation for IP and ARP
		 * packets that's compatible with the RFC 2625
		 * encapsulation, but that uses a different ARP
		 * hardware type and hardware addresses.  That
		 * ARP hardware type is 18; Linux doesn't define
		 * any ARPHRD_ value as 18, but if it ever officially
		 * supports RFC 4338-style IP-over-FC, it should define
		 * one.
		 *
		 * For now, we map it to DLT_IP_OVER_FC, in the hopes
		 * that this will encourage its use in the future,
		 * should Linux ever officially support RFC 4338-style
		 * IP-over-FC.
		 */
		handle->linktype = DLT_IP_OVER_FC;
		break;

#ifndef ARPHRD_FCPP
#define ARPHRD_FCPP	784
#endif
	case ARPHRD_FCPP:
#ifndef ARPHRD_FCAL
#define ARPHRD_FCAL	785
#endif
	case ARPHRD_FCAL:
#ifndef ARPHRD_FCPL
#define ARPHRD_FCPL	786
#endif
	case ARPHRD_FCPL:
#ifndef ARPHRD_FCFABRIC
#define ARPHRD_FCFABRIC	787
#endif
	case ARPHRD_FCFABRIC:
		/*
		 * Back in 2002, Donald Lee at Cray wanted a DLT_ for
		 * IP-over-FC:
		 *
		 *	http://www.mail-archive.com/tcpdump-workers@sandelman.ottawa.on.ca/msg01043.html
		 *
		 * and one was assigned.
		 *
		 * In a later private discussion (spun off from a message
		 * on the ethereal-users list) on how to get that DLT_
		 * value in libpcap on Linux, I ended up deciding that
		 * the best thing to do would be to have him tweak the
		 * driver to set the ARPHRD_ value to some ARPHRD_FCxx
		 * type, and map all those types to DLT_IP_OVER_FC:
		 *
		 *	I've checked into the libpcap and tcpdump CVS tree
		 *	support for DLT_IP_OVER_FC.  In order to use that,
		 *	you'd have to modify your modified driver to return
		 *	one of the ARPHRD_FCxxx types, in "fcLINUXfcp.c" -
		 *	change it to set "dev->type" to ARPHRD_FCFABRIC, for
		 *	example (the exact value doesn't matter, it can be
		 *	any of ARPHRD_FCPP, ARPHRD_FCAL, ARPHRD_FCPL, or
		 *	ARPHRD_FCFABRIC).
		 *
		 * 11 years later, Christian Svensson wanted to map
		 * various ARPHRD_ values to DLT_FC_2 and
		 * DLT_FC_2_WITH_FRAME_DELIMS for raw Fibre Channel
		 * frames:
		 *
		 *	https://github.com/mcr/libpcap/pull/29
		 *
		 * There doesn't seem to be any network drivers that uses
		 * any of the ARPHRD_FC* values for IP-over-FC, and
		 * it's not exactly clear what the "Dummy types for non
		 * ARP hardware" are supposed to mean (link-layer
		 * header type?  Physical network type?), so it's
		 * not exactly clear why the ARPHRD_FC* types exist
		 * in the first place.
		 *
		 * For now, we map them to DLT_FC_2, and provide an
		 * option of DLT_FC_2_WITH_FRAME_DELIMS, as well as
		 * DLT_IP_OVER_FC just in case there's some old
		 * driver out there that uses one of those types for
		 * IP-over-FC on which somebody wants to capture
		 * packets.
		 */
		handle->dlt_list = (u_int *) malloc(sizeof(u_int) * 3);
		/*
		 * If that fails, just leave the list empty.
		 */
		if (handle->dlt_list != NULL) {
			handle->dlt_list[0] = DLT_FC_2;
			handle->dlt_list[1] = DLT_FC_2_WITH_FRAME_DELIMS;
			handle->dlt_list[2] = DLT_IP_OVER_FC;
			handle->dlt_count = 3;
		}
		handle->linktype = DLT_FC_2;
		break;

#ifndef ARPHRD_IRDA
#define ARPHRD_IRDA	783
#endif
	case ARPHRD_IRDA:
		/* Don't expect IP packet out of this interfaces... */
		handle->linktype = DLT_LINUX_IRDA;
		/* We need to save packet direction for IrDA decoding,
		 * so let's use "Linux-cooked" mode. Jean II
		 *
		 * XXX - this is handled in activate_new(). */
		/* handlep->cooked = 1; */
		break;

	/* ARPHRD_LAPD is unofficial and randomly allocated, if reallocation
	 * is needed, please report it to <daniele@orlandi.com> */
#ifndef ARPHRD_LAPD
#define ARPHRD_LAPD	8445
#endif
	case ARPHRD_LAPD:
		/* Don't expect IP packet out of this interfaces... */
		handle->linktype = DLT_LINUX_LAPD;
		break;

#ifndef ARPHRD_NONE
#define ARPHRD_NONE	0xFFFE
#endif
	case ARPHRD_NONE:
		/*
		 * No link-layer header; packets are just IP
		 * packets, so use DLT_RAW.
		 */
		handle->linktype = DLT_RAW;
		break;

#ifndef ARPHRD_IEEE802154
#define ARPHRD_IEEE802154      804
#endif
       case ARPHRD_IEEE802154:
               handle->linktype =  DLT_IEEE802_15_4_NOFCS;
               break;

#ifndef ARPHRD_NETLINK
#define ARPHRD_NETLINK	824
#endif
	case ARPHRD_NETLINK:
		handle->linktype = DLT_NETLINK;
		/*
		 * We need to use cooked mode, so that in sll_protocol we
		 * pick up the netlink protocol type such as NETLINK_ROUTE,
		 * NETLINK_GENERIC, NETLINK_FIB_LOOKUP, etc.
		 *
		 * XXX - this is handled in activate_new().
		 */
		/* handlep->cooked = 1; */
		break;

#ifndef ARPHRD_VSOCKMON
#define ARPHRD_VSOCKMON	826
#endif
	case ARPHRD_VSOCKMON:
		handle->linktype = DLT_VSOCK;
		break;

	default:
		handle->linktype = -1;
		break;
	}
}