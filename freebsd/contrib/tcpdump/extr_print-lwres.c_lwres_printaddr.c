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
typedef  int uint16_t ;
struct in_addr {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
struct TYPE_3__ {int /*<<< orphan*/  family; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ lwres_addr_t ;

/* Variables and functions */
 int EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_TCHECK2 (char const,int) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int
lwres_printaddr(netdissect_options *ndo,
                const lwres_addr_t *ap)
{
	uint16_t l;
	const char *p;
	int i;

	ND_TCHECK(ap->length);
	l = EXTRACT_16BITS(&ap->length);
	/* XXX ap points to packed struct */
	p = (const char *)&ap->length + sizeof(ap->length);
	ND_TCHECK2(*p, l);

	switch (EXTRACT_32BITS(&ap->family)) {
	case 1:	/* IPv4 */
		if (l < 4)
			return -1;
		ND_PRINT((ndo, " %s", ipaddr_string(ndo, p)));
		p += sizeof(struct in_addr);
		break;
	case 2:	/* IPv6 */
		if (l < 16)
			return -1;
		ND_PRINT((ndo, " %s", ip6addr_string(ndo, p)));
		p += sizeof(struct in6_addr);
		break;
	default:
		ND_PRINT((ndo, " %u/", EXTRACT_32BITS(&ap->family)));
		for (i = 0; i < l; i++)
			ND_PRINT((ndo, "%02x", *p++));
	}

	return p - (const char *)ap;

  trunc:
	return -1;
}