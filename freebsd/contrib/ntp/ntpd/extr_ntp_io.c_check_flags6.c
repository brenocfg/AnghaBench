#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32 ;
struct TYPE_5__ {int ifru_flags6; } ;
struct in6_ifreq {TYPE_1__ ifr_ifru; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifr_addr; } ;
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {int /*<<< orphan*/  sa6; TYPE_2__ sa; } ;
typedef  TYPE_3__ sockaddr_u ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  SIOCGIFAFLAG_IN6 ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  ZERO (struct in6_ifreq) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct in6_ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static isc_boolean_t
check_flags6(
	sockaddr_u *psau,
	const char *name,
	u_int32 flags6
	)
{
#if defined(INCLUDE_IPV6_SUPPORT) && defined(SIOCGIFAFLAG_IN6)
	struct in6_ifreq ifr6;
	int fd;

	if (psau->sa.sa_family != AF_INET6)
		return ISC_FALSE;
	if ((fd = socket(AF_INET6, SOCK_DGRAM, 0)) < 0)
		return ISC_FALSE;
	ZERO(ifr6);
	memcpy(&ifr6.ifr_addr, &psau->sa6, sizeof(ifr6.ifr_addr));
	strlcpy(ifr6.ifr_name, name, sizeof(ifr6.ifr_name));
	if (ioctl(fd, SIOCGIFAFLAG_IN6, &ifr6) < 0) {
		close(fd);
		return ISC_FALSE;
	}
	close(fd);
	if ((ifr6.ifr_ifru.ifru_flags6 & flags6) != 0)
		return ISC_TRUE;
#endif	/* INCLUDE_IPV6_SUPPORT && SIOCGIFAFLAG_IN6 */
	return ISC_FALSE;
}