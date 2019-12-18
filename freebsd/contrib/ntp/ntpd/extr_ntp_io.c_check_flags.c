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
typedef  int u_int32 ;
struct ifreq {int ifr_addrflags; int /*<<< orphan*/  ifr_name; int /*<<< orphan*/  ifr_addr; } ;
struct TYPE_5__ {scalar_t__ sa_family; } ;
struct TYPE_4__ {TYPE_2__ sa; } ;
typedef  TYPE_1__ sockaddr_u ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  SIOCGIFAFLAG_IN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  ZERO (struct ifreq) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ifreq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static isc_boolean_t
check_flags(
	sockaddr_u *psau,
	const char *name,
	u_int32 flags
	)
{
#if defined(SIOCGIFAFLAG_IN)
	struct ifreq ifr;
	int fd;

	if (psau->sa.sa_family != AF_INET)
		return ISC_FALSE;
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		return ISC_FALSE;
	ZERO(ifr);
	memcpy(&ifr.ifr_addr, &psau->sa, sizeof(ifr.ifr_addr));
	strlcpy(ifr.ifr_name, name, sizeof(ifr.ifr_name));
	if (ioctl(fd, SIOCGIFAFLAG_IN, &ifr) < 0) {
		close(fd);
		return ISC_FALSE;
	}
	close(fd);
	if ((ifr.ifr_addrflags & flags) != 0)
		return ISC_TRUE;
#endif	/* SIOCGIFAFLAG_IN */
	return ISC_FALSE;
}