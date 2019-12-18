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
struct sockaddr_dl {unsigned int sdl_nlen; int /*<<< orphan*/  sdl_data; int /*<<< orphan*/  sdl_index; } ;
struct sockaddr {int sa_family; int sa_len; } ;
struct ifa_msghdr {scalar_t__ ifam_version; scalar_t__ ifam_type; int ifam_flags; int ifam_addrs; } ;
struct if_msghdr {int dummy; } ;
typedef  scalar_t__ sa ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {int flags; int af; struct TYPE_8__* name; int /*<<< orphan*/  broadcast; int /*<<< orphan*/  dstaddress; int /*<<< orphan*/  netmask; int /*<<< orphan*/  address; int /*<<< orphan*/  ifindex; } ;
struct TYPE_7__ {unsigned int pos; int bufused; TYPE_2__ current; scalar_t__ buf; } ;
typedef  TYPE_1__ isc_interfaceiter_t ;

/* Variables and functions */
 int AF_INET ; 
 int AF_INET6 ; 
 int IFF_BROADCAST ; 
 int IFF_LOOPBACK ; 
 int IFF_MULTICAST ; 
 int IFF_POINTOPOINT ; 
 int IFF_UP ; 
 int /*<<< orphan*/  INSIST (int) ; 
 int INTERFACE_F_BROADCAST ; 
 int INTERFACE_F_LOOPBACK ; 
 int INTERFACE_F_MULTICAST ; 
 int INTERFACE_F_POINTTOPOINT ; 
 int INTERFACE_F_UP ; 
 int /*<<< orphan*/  ISC_MSGSET_IFITERSYSCTL ; 
 int /*<<< orphan*/  ISC_MSG_UNEXPECTEDTYPE ; 
 int /*<<< orphan*/  ISC_R_IGNORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ ROUNDUP (int) ; 
#define  RTAX_BRD 130 
#define  RTAX_IFA 129 
 int RTAX_MAX ; 
#define  RTAX_NETMASK 128 
 scalar_t__ RTM_IFINFO ; 
 scalar_t__ RTM_NEWADDR ; 
 scalar_t__ RTM_VERSION ; 
 int VALID_IFITER (TYPE_1__*) ; 
 int _FAKE_SA_LEN_DST (struct sockaddr*) ; 
 int /*<<< orphan*/  get_addr (int,int /*<<< orphan*/ *,struct sockaddr*,TYPE_2__*) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static isc_result_t
internal_current(isc_interfaceiter_t *iter) {
	struct ifa_msghdr *ifam, *ifam_end;

	REQUIRE(VALID_IFITER(iter));
	REQUIRE (iter->pos < (unsigned int) iter->bufused);

	ifam = (struct ifa_msghdr *) ((char *) iter->buf + iter->pos);
	ifam_end = (struct ifa_msghdr *) ((char *) iter->buf + iter->bufused);

	// Skip wrong RTM version headers
	if (ifam->ifam_version != RTM_VERSION)
		return (ISC_R_IGNORE);

	if (ifam->ifam_type == RTM_IFINFO) {
		struct if_msghdr *ifm = (struct if_msghdr *) ifam;
		struct sockaddr_dl *sdl = (struct sockaddr_dl *) (ifm + 1);
		unsigned int namelen;

		memset(&iter->current, 0, sizeof(iter->current));

		iter->current.ifindex = sdl->sdl_index;
		namelen = sdl->sdl_nlen;
		if (namelen > sizeof(iter->current.name) - 1)
			namelen = sizeof(iter->current.name) - 1;

		memset(iter->current.name, 0, sizeof(iter->current.name));
		memcpy(iter->current.name, sdl->sdl_data, namelen);

		iter->current.flags = 0;

		if ((ifam->ifam_flags & IFF_UP) != 0)
			iter->current.flags |= INTERFACE_F_UP;

		if ((ifam->ifam_flags & IFF_POINTOPOINT) != 0)
			iter->current.flags |= INTERFACE_F_POINTTOPOINT;

		if ((ifam->ifam_flags & IFF_LOOPBACK) != 0)
			iter->current.flags |= INTERFACE_F_LOOPBACK;

		if ((ifam->ifam_flags & IFF_BROADCAST) != 0)
			iter->current.flags |= INTERFACE_F_BROADCAST;

#ifdef IFF_MULTICAST
		if ((ifam->ifam_flags & IFF_MULTICAST) != 0)
			iter->current.flags |= INTERFACE_F_MULTICAST;
#endif

		/*
		 * This is not an interface address.
		 * Force another iteration.
		 */
		return (ISC_R_IGNORE);
	} else if (ifam->ifam_type == RTM_NEWADDR) {
		int i;
		int family;
		struct sockaddr *mask_sa = NULL;
		struct sockaddr *addr_sa = NULL;
		struct sockaddr *dst_sa = NULL;

		struct sockaddr *sa = (struct sockaddr *)(ifam + 1);
		family = sa->sa_family;

		for (i = 0; i < RTAX_MAX; i++)
		{
			if ((ifam->ifam_addrs & (1 << i)) == 0)
				continue;

			INSIST(sa < (struct sockaddr *) ifam_end);

			switch (i) {
			case RTAX_NETMASK: /* Netmask */
				mask_sa = sa;
				break;
			case RTAX_IFA: /* Interface address */
				addr_sa = sa;
				break;
			case RTAX_BRD: /* Broadcast or destination address */
				dst_sa = sa;
				break;
			}
#ifdef ISC_PLATFORM_HAVESALEN
			sa = (struct sockaddr *)((char*)(sa)
					 + ROUNDUP(sa->sa_len));
#else
#ifdef sgi
			/*
			 * Do as the contributed SGI code does.
			 */
			sa = (struct sockaddr *)((char*)(sa)
					 + ROUNDUP(_FAKE_SA_LEN_DST(sa)));
#else
			/* XXX untested. */
			sa = (struct sockaddr *)((char*)(sa)
					 + ROUNDUP(sizeof(struct sockaddr)));
#endif
#endif
		}

		if (addr_sa == NULL)
			return (ISC_R_IGNORE);

		family = addr_sa->sa_family;
		if (family != AF_INET && family != AF_INET6)
			return (ISC_R_IGNORE);

		iter->current.af = family;

		get_addr(family, &iter->current.address, addr_sa,
			 iter->current.name);

		if (mask_sa != NULL)
			get_addr(family, &iter->current.netmask, mask_sa,
				 iter->current.name);

		if (dst_sa != NULL &&
		    (iter->current.flags & INTERFACE_F_POINTTOPOINT) != 0)
			get_addr(family, &iter->current.dstaddress, dst_sa,
				 iter->current.name);

		if (dst_sa != NULL &&
		    (iter->current.flags & INTERFACE_F_BROADCAST) != 0)
			get_addr(family, &iter->current.broadcast, dst_sa,
				 iter->current.name);

		return (ISC_R_SUCCESS);
	} else {
		printf("%s", isc_msgcat_get(isc_msgcat,
					    ISC_MSGSET_IFITERSYSCTL,
					    ISC_MSG_UNEXPECTEDTYPE,
					    "warning: unexpected interface "
					    "list message type\n"));
		return (ISC_R_IGNORE);
	}
}