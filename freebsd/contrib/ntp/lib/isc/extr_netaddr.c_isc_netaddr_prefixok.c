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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_5__ {int family; TYPE_1__ type; } ;
typedef  TYPE_2__ isc_netaddr_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  ISC_R_FAILURE ; 
 int /*<<< orphan*/  ISC_R_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  ISC_R_RANGE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,unsigned int) ; 

isc_result_t
isc_netaddr_prefixok(const isc_netaddr_t *na, unsigned int prefixlen) {
	static const unsigned char zeros[16] = { 0 };
	unsigned int nbits, nbytes, ipbytes = 0;
	const unsigned char *p;

	switch (na->family) {
	case AF_INET:
		p = (const unsigned char *) &na->type.in;
		ipbytes = 4;
		if (prefixlen > 32)
			return (ISC_R_RANGE);
		break;
	case AF_INET6:
		p = (const unsigned char *) &na->type.in6;
		ipbytes = 16;
		if (prefixlen > 128)
			return (ISC_R_RANGE);
		break;
	default:
		return (ISC_R_NOTIMPLEMENTED);
	}
	nbytes = prefixlen / 8;
	nbits = prefixlen % 8;
	if (nbits != 0) {
		if ((p[nbytes] & (0xff>>nbits)) != 0U)
			return (ISC_R_FAILURE);
		nbytes++;
	}
	if (memcmp(p + nbytes, zeros, ipbytes - nbytes) != 0)
		return (ISC_R_FAILURE);
	return (ISC_R_SUCCESS);
}