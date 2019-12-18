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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int EXTRACT_24BITS (int const*) ; 
 int /*<<< orphan*/  ITEMCHECK (int) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 char* ipaddr_string (int /*<<< orphan*/ *,struct in_addr*) ; 
 int /*<<< orphan*/  memcpy (struct in_addr*,int const*,int) ; 
 int /*<<< orphan*/  memset (struct in_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int,char*) ; 

__attribute__((used)) static int
decode_labeled_prefix4(netdissect_options *ndo,
                       const u_char *pptr, u_int itemlen, char *buf, u_int buflen)
{
	struct in_addr addr;
	u_int plen, plenbytes;

	/* prefix length and label = 4 bytes */
	ND_TCHECK2(pptr[0], 4);
	ITEMCHECK(4);
	plen = pptr[0];   /* get prefix length */

        /* this is one of the weirdnesses of rfc3107
           the label length (actually the label + COS bits)
           is added to the prefix length;
           we also do only read out just one label -
           there is no real application for advertisement of
           stacked labels in a single BGP message
        */

	if (24 > plen)
		return -1;

        plen-=24; /* adjust prefixlen - labellength */

	if (32 < plen)
		return -1;
	itemlen -= 4;

	memset(&addr, 0, sizeof(addr));
	plenbytes = (plen + 7) / 8;
	ND_TCHECK2(pptr[4], plenbytes);
	ITEMCHECK(plenbytes);
	memcpy(&addr, &pptr[4], plenbytes);
	if (plen % 8) {
		((u_char *)&addr)[plenbytes - 1] &=
			((0xff00 >> (plen % 8)) & 0xff);
	}
        /* the label may get offsetted by 4 bits so lets shift it right */
	snprintf(buf, buflen, "%s/%d, label:%u %s",
                 ipaddr_string(ndo, &addr),
                 plen,
                 EXTRACT_24BITS(pptr+1)>>4,
                 ((pptr[3]&1)==0) ? "(BOGUS: Bottom of Stack NOT set!)" : "(bottom)" );

	return 4 + plenbytes;

trunc:
	return -2;

badtlv:
	return -3;
}