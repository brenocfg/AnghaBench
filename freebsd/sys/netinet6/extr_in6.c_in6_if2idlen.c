#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ifnet {int if_type; } ;

/* Variables and functions */
#define  IFT_BRIDGE 137 
#define  IFT_ETHER 136 
#define  IFT_FRELAY 135 
#define  IFT_GIF 134 
#define  IFT_IEEE1394 133 
#define  IFT_INFINIBAND 132 
#define  IFT_L2VLAN 131 
#define  IFT_LOOP 130 
#define  IFT_PPP 129 
#define  IFT_PROPVIRTUAL 128 
 int /*<<< orphan*/  printf (char*,int) ; 

int
in6_if2idlen(struct ifnet *ifp)
{
	switch (ifp->if_type) {
	case IFT_ETHER:		/* RFC2464 */
	case IFT_PROPVIRTUAL:	/* XXX: no RFC. treat it as ether */
	case IFT_L2VLAN:	/* ditto */
	case IFT_BRIDGE:	/* bridge(4) only does Ethernet-like links */
	case IFT_INFINIBAND:
		return (64);
	case IFT_PPP:		/* RFC2472 */
		return (64);
	case IFT_FRELAY:	/* RFC2590 */
		return (64);
	case IFT_IEEE1394:	/* RFC3146 */
		return (64);
	case IFT_GIF:
		return (64);	/* draft-ietf-v6ops-mech-v2-07 */
	case IFT_LOOP:
		return (64);	/* XXX: is this really correct? */
	default:
		/*
		 * Unknown link type:
		 * It might be controversial to use the today's common constant
		 * of 64 for these cases unconditionally.  For full compliance,
		 * we should return an error in this case.  On the other hand,
		 * if we simply miss the standard for the link type or a new
		 * standard is defined for a new link type, the IFID length
		 * is very likely to be the common constant.  As a compromise,
		 * we always use the constant, but make an explicit notice
		 * indicating the "unknown" case.
		 */
		printf("in6_if2idlen: unknown link type (%d)\n", ifp->if_type);
		return (64);
	}
}