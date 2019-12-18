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
 int /*<<< orphan*/  ISC_R_MASKNONCONTIG ; 
 int /*<<< orphan*/  ISC_R_NOTIMPLEMENTED ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 

isc_result_t
isc_netaddr_masktoprefixlen(const isc_netaddr_t *s, unsigned int *lenp) {
	unsigned int nbits = 0, nbytes = 0, ipbytes = 0, i;
	const unsigned char *p;

	switch (s->family) {
	case AF_INET:
		p = (const unsigned char *) &s->type.in;
		ipbytes = 4;
		break;
	case AF_INET6:
		p = (const unsigned char *) &s->type.in6;
		ipbytes = 16;
		break;
	default:
		return (ISC_R_NOTIMPLEMENTED);
	}
	for (i = 0; i < ipbytes; i++) {
		if (p[i] != 0xFF)
			break;
	}
	nbytes = i;
	if (i < ipbytes) {
		unsigned int c = p[nbytes];
		while ((c & 0x80) != 0 && nbits < 8) {
			c <<= 1; nbits++;
		}
		if ((c & 0xFF) != 0)
			return (ISC_R_MASKNONCONTIG);
		i++;
	}
	for (; i < ipbytes; i++) {
		if (p[i] != 0)
			return (ISC_R_MASKNONCONTIG);
	}
	*lenp = nbytes * 8 + nbits;
	return (ISC_R_SUCCESS);
}