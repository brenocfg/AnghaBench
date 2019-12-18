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
typedef  int /*<<< orphan*/  zbuf ;
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {char* un; int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {int family; int zone; TYPE_1__ type; } ;
typedef  TYPE_2__ isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;
typedef  int /*<<< orphan*/  abuf ;

/* Variables and functions */
#define  AF_INET 130 
#define  AF_INET6 129 
#define  AF_UNIX 128 
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  ISC_R_FAILURE ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 char* inet_ntop (int,void const*,char*,int) ; 
 unsigned int isc_buffer_availablelength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_buffer_putmem (int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int snprintf (char*,int,char*,int) ; 
 unsigned int strlen (char*) ; 

isc_result_t
isc_netaddr_totext(const isc_netaddr_t *netaddr, isc_buffer_t *target) {
	char abuf[sizeof("xxxx:xxxx:xxxx:xxxx:xxxx:xxxx:255.255.255.255")];
	char zbuf[sizeof("%4294967295")];
	unsigned int alen;
	int zlen;
	const char *r;
	const void *type;

	REQUIRE(netaddr != NULL);

	switch (netaddr->family) {
	case AF_INET:
		type = &netaddr->type.in;
		break;
	case AF_INET6:
		type = &netaddr->type.in6;
		break;
#ifdef ISC_PLATFORM_HAVESYSUNH
	case AF_UNIX:
		alen = strlen(netaddr->type.un);
		if (alen > isc_buffer_availablelength(target))
			return (ISC_R_NOSPACE);
		isc_buffer_putmem(target,
				  (const unsigned char *)(netaddr->type.un),
				  alen);
		return (ISC_R_SUCCESS);
#endif
	default:
		return (ISC_R_FAILURE);
	}
	r = inet_ntop(netaddr->family, type, abuf, sizeof(abuf));
	if (r == NULL)
		return (ISC_R_FAILURE);

	alen = (unsigned int)strlen(abuf); /* no overflow possible */
	INSIST(alen < sizeof(abuf));

	zlen = 0;
	if (netaddr->family == AF_INET6 && netaddr->zone != 0) {
		zlen = snprintf(zbuf, sizeof(zbuf), "%%%u", netaddr->zone);
		if (zlen < 0)
			return (ISC_R_FAILURE);
		INSIST((unsigned int)zlen < sizeof(zbuf));
	}

	if (alen + zlen > isc_buffer_availablelength(target))
		return (ISC_R_NOSPACE);

	isc_buffer_putmem(target, (unsigned char *)abuf, alen);
	isc_buffer_putmem(target, (unsigned char *)zbuf, zlen);

	return (ISC_R_SUCCESS);
}