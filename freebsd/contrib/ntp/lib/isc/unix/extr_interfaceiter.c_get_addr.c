#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone16 ;
struct TYPE_15__ {struct TYPE_15__* s6_addr; } ;
struct sockaddr_in6 {TYPE_8__ sin6_addr; int /*<<< orphan*/  sin6_scope_id; } ;
struct sockaddr_in {TYPE_8__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_13__ {int /*<<< orphan*/ * s6_addr; } ;
typedef  TYPE_2__ isc_uint16_t ;
struct TYPE_12__ {TYPE_2__ in6; TYPE_2__ in; } ;
struct TYPE_14__ {unsigned int family; TYPE_1__ type; } ;
typedef  TYPE_3__ isc_netaddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  IN6_IS_ADDR_LINKLOCAL (TYPE_8__*) ; 
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (char*) ; 
 unsigned int if_nametoindex (char*) ; 
 int /*<<< orphan*/  isc_netaddr_setzone (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ ntohs (TYPE_2__) ; 

__attribute__((used)) static void
get_addr(unsigned int family, isc_netaddr_t *dst, struct sockaddr *src,
	 char *ifname)
{
	struct sockaddr_in6 *sa6;

#if !defined(ISC_PLATFORM_HAVEIFNAMETOINDEX) || \
    !defined(ISC_PLATFORM_HAVESCOPEID)
	UNUSED(ifname);
#endif

	/* clear any remaining value for safety */
	memset(dst, 0, sizeof(*dst));

	dst->family = family;
	switch (family) {
	case AF_INET:
		memcpy(&dst->type.in,
		       &((struct sockaddr_in *)(void *)src)->sin_addr,
		       sizeof(struct in_addr));
		break;
	case AF_INET6:
		sa6 = (struct sockaddr_in6 *)(void *)src;
		memcpy(&dst->type.in6, &sa6->sin6_addr,
		       sizeof(struct in6_addr));
#ifdef ISC_PLATFORM_HAVESCOPEID
		if (sa6->sin6_scope_id != 0)
			isc_netaddr_setzone(dst, sa6->sin6_scope_id);
		else {
			/*
			 * BSD variants embed scope zone IDs in the 128bit
			 * address as a kernel internal form.  Unfortunately,
			 * the embedded IDs are not hidden from applications
			 * when getting access to them by sysctl or ioctl.
			 * We convert the internal format to the pure address
			 * part and the zone ID part.
			 * Since multicast addresses should not appear here
			 * and they cannot be distinguished from netmasks,
			 * we only consider unicast link-local addresses.
			 */
			if (IN6_IS_ADDR_LINKLOCAL(&sa6->sin6_addr)) {
				isc_uint16_t zone16;

				memcpy(&zone16, &sa6->sin6_addr.s6_addr[2],
				       sizeof(zone16));
				zone16 = ntohs(zone16);
				if (zone16 != 0) {
					/* the zone ID is embedded */
					isc_netaddr_setzone(dst,
							    (isc_uint32_t)zone16);
					dst->type.in6.s6_addr[2] = 0;
					dst->type.in6.s6_addr[3] = 0;
#ifdef ISC_PLATFORM_HAVEIFNAMETOINDEX
				} else if (ifname != NULL) {
					unsigned int zone;

					/*
					 * sin6_scope_id is still not provided,
					 * but the corresponding interface name
					 * is know.  Use the interface ID as
					 * the link ID.
					 */
					zone = if_nametoindex(ifname);
					if (zone != 0) {
						isc_netaddr_setzone(dst,
								    (isc_uint32_t)zone);
					}
#endif
				}
			}
		}
#endif
		break;
	default:
		INSIST(0);
		break;
	}
}