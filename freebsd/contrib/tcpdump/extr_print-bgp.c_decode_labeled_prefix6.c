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
typedef  int u_int ;
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EXTRACT_24BITS (int const*) ; 
 int /*<<< orphan*/  ITEMCHECK (int) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 char* ip6addr_string (int /*<<< orphan*/ *,struct in6_addr*) ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int const*,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int,char*) ; 

__attribute__((used)) static int
decode_labeled_prefix6(netdissect_options *ndo,
                       const u_char *pptr, u_int itemlen, char *buf, u_int buflen)
{
	struct in6_addr addr;
	u_int plen, plenbytes;

	/* prefix length and label = 4 bytes */
	ND_TCHECK2(pptr[0], 4);
	ITEMCHECK(4);
	plen = pptr[0]; /* get prefix length */

	if (24 > plen)
		return -1;

        plen-=24; /* adjust prefixlen - labellength */

	if (128 < plen)
		return -1;
	itemlen -= 4;

	memset(&addr, 0, sizeof(addr));
	plenbytes = (plen + 7) / 8;
	ND_TCHECK2(pptr[4], plenbytes);
	memcpy(&addr, &pptr[4], plenbytes);
	if (plen % 8) {
		addr.s6_addr[plenbytes - 1] &=
			((0xff00 >> (plen % 8)) & 0xff);
	}
        /* the label may get offsetted by 4 bits so lets shift it right */
	snprintf(buf, buflen, "%s/%d, label:%u %s",
                 ip6addr_string(ndo, &addr),
                 plen,
                 EXTRACT_24BITS(pptr+1)>>4,
                 ((pptr[3]&1)==0) ? "(BOGUS: Bottom of Stack NOT set!)" : "(bottom)" );

	return 4 + plenbytes;

trunc:
	return -2;

badtlv:
	return -3;
}