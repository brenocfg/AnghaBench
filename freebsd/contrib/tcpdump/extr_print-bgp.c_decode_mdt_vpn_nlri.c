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
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int MDT_VPN_NLRI_LEN ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 char* bgp_vpn_rd_print (int /*<<< orphan*/ *,int const*) ; 
 char* ipaddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static int
decode_mdt_vpn_nlri(netdissect_options *ndo,
                    const u_char *pptr, char *buf, u_int buflen)
{

    const u_char *rd;
    const u_char *vpn_ip;

    ND_TCHECK(pptr[0]);

    /* if the NLRI is not predefined length, quit.*/
    if (*pptr != MDT_VPN_NLRI_LEN * 8)
	return -1;
    pptr++;

    /* RD */
    ND_TCHECK2(pptr[0], 8);
    rd = pptr;
    pptr+=8;

    /* IPv4 address */
    ND_TCHECK2(pptr[0], sizeof(struct in_addr));
    vpn_ip = pptr;
    pptr+=sizeof(struct in_addr);

    /* MDT Group Address */
    ND_TCHECK2(pptr[0], sizeof(struct in_addr));

    snprintf(buf, buflen, "RD: %s, VPN IP Address: %s, MC Group Address: %s",
	     bgp_vpn_rd_print(ndo, rd), ipaddr_string(ndo, vpn_ip), ipaddr_string(ndo, pptr));

    return MDT_VPN_NLRI_LEN + 1;

 trunc:

return -2;
}