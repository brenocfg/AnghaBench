#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int u_char ;
struct TYPE_9__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ARCTYPE_ARP 135 
#define  ARCTYPE_ARP_OLD 134 
#define  ARCTYPE_ATALK 133 
#define  ARCTYPE_INET6 132 
#define  ARCTYPE_IP 131 
#define  ARCTYPE_IPX 130 
#define  ARCTYPE_IP_OLD 129 
#define  ARCTYPE_REVARP 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  arp_print (TYPE_1__*,int const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atalk_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip6_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipx_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arcnet_encap_print(netdissect_options *ndo, u_char arctype, const u_char *p,
    u_int length, u_int caplen)
{
	switch (arctype) {

	case ARCTYPE_IP_OLD:
	case ARCTYPE_IP:
	        ip_print(ndo, p, length);
		return (1);

	case ARCTYPE_INET6:
		ip6_print(ndo, p, length);
		return (1);

	case ARCTYPE_ARP_OLD:
	case ARCTYPE_ARP:
	case ARCTYPE_REVARP:
		arp_print(ndo, p, length, caplen);
		return (1);

	case ARCTYPE_ATALK:	/* XXX was this ever used? */
		if (ndo->ndo_vflag)
			ND_PRINT((ndo, "et1 "));
		atalk_print(ndo, p, length);
		return (1);

	case ARCTYPE_IPX:
		ipx_print(ndo, p, length);
		return (1);

	default:
		return (0);
	}
}