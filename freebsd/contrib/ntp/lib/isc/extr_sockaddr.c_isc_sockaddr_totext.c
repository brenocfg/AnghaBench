#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbuf ;
struct TYPE_14__ {char* sun_path; } ;
struct TYPE_13__ {int /*<<< orphan*/  sin6_port; } ;
struct TYPE_12__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_11__ {int sa_family; } ;
struct TYPE_15__ {TYPE_4__ sunix; TYPE_3__ sin6; TYPE_2__ sin; TYPE_1__ sa; } ;
struct TYPE_16__ {TYPE_5__ type; } ;
typedef  TYPE_6__ isc_sockaddr_t ;
typedef  scalar_t__ isc_result_t ;
struct TYPE_17__ {int length; char* base; } ;
typedef  TYPE_7__ isc_region_t ;
typedef  int /*<<< orphan*/  isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ ISC_R_FAILURE ; 
 scalar_t__ ISC_R_NOSPACE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_availableregion (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  isc_buffer_putmem (int /*<<< orphan*/ *,unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,TYPE_6__ const*) ; 
 scalar_t__ isc_netaddr_totext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (char*) ; 

isc_result_t
isc_sockaddr_totext(const isc_sockaddr_t *sockaddr, isc_buffer_t *target) {
	isc_result_t result;
	isc_netaddr_t netaddr;
	char pbuf[sizeof("65000")];
	unsigned int plen;
	isc_region_t avail;

	REQUIRE(sockaddr != NULL);

	/*
	 * Do the port first, giving us the opportunity to check for
	 * unsupported address families before calling
	 * isc_netaddr_fromsockaddr().
	 */
	switch (sockaddr->type.sa.sa_family) {
	case AF_INET:
		snprintf(pbuf, sizeof(pbuf), "%u", ntohs(sockaddr->type.sin.sin_port));
		break;
	case AF_INET6:
		snprintf(pbuf, sizeof(pbuf), "%u", ntohs(sockaddr->type.sin6.sin6_port));
		break;
#ifdef ISC_PLAFORM_HAVESYSUNH
	case AF_UNIX:
		plen = (unsigned int)strlen(sockaddr->type.sunix.sun_path);
		if (plen >= isc_buffer_availablelength(target))
			return (ISC_R_NOSPACE);

		isc_buffer_putmem(target, sockaddr->type.sunix.sun_path, plen);

		/*
		 * Null terminate after used region.
		 */
		isc_buffer_availableregion(target, &avail);
		INSIST(avail.length >= 1);
		avail.base[0] = '\0';

		return (ISC_R_SUCCESS);
#endif
	default:
		return (ISC_R_FAILURE);
	}

	plen = (unsigned int)strlen(pbuf);
	INSIST(plen < sizeof(pbuf));

	isc_netaddr_fromsockaddr(&netaddr, sockaddr);
	result = isc_netaddr_totext(&netaddr, target);
	if (result != ISC_R_SUCCESS)
		return (result);

	if (1 + plen + 1 > isc_buffer_availablelength(target))
		return (ISC_R_NOSPACE);

	isc_buffer_putmem(target, (const unsigned char *)"#", 1);
	isc_buffer_putmem(target, (const unsigned char *)pbuf, plen);

	/*
	 * Null terminate after used region.
	 */
	isc_buffer_availableregion(target, &avail);
	INSIST(avail.length >= 1);
	avail.base[0] = '\0';

	return (ISC_R_SUCCESS);
}