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
typedef  int uint8_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 char* isonsap_string (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  memcpy (int**,int const*,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int) ; 

__attribute__((used)) static int
decode_clnp_prefix(netdissect_options *ndo,
                   const u_char *pptr, char *buf, u_int buflen)
{
        uint8_t addr[19];
	u_int plen;

	ND_TCHECK(pptr[0]);
	plen = pptr[0]; /* get prefix length */

	if (152 < plen)
		return -1;

	memset(&addr, 0, sizeof(addr));
	ND_TCHECK2(pptr[4], (plen + 7) / 8);
	memcpy(&addr, &pptr[4], (plen + 7) / 8);
	if (plen % 8) {
		addr[(plen + 7) / 8 - 1] &=
			((0xff00 >> (plen % 8)) & 0xff);
	}
	snprintf(buf, buflen, "%s/%d",
                 isonsap_string(ndo, addr,(plen + 7) / 8),
                 plen);

	return 1 + (plen + 7) / 8;

trunc:
	return -2;
}