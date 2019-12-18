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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int u_int ;
struct egp_packet {int egp_sourcenet; int egp_intgw; int egp_extgw; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ IN_CLASSA (int) ; 
 int IN_CLASSA_NET ; 
 scalar_t__ IN_CLASSB (int) ; 
 int IN_CLASSB_NET ; 
 scalar_t__ IN_CLASSC (int) ; 
 int IN_CLASSC_NET ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
egpnrprint(netdissect_options *ndo,
           register const struct egp_packet *egp, u_int length)
{
	register const uint8_t *cp;
	uint32_t addr;
	register uint32_t net;
	register u_int netlen;
	int gateways, distances, networks;
	int t_gateways;
	const char *comma;

	addr = egp->egp_sourcenet;
	if (IN_CLASSA(addr)) {
		net = addr & IN_CLASSA_NET;
		netlen = 1;
	} else if (IN_CLASSB(addr)) {
		net = addr & IN_CLASSB_NET;
		netlen = 2;
	} else if (IN_CLASSC(addr)) {
		net = addr & IN_CLASSC_NET;
		netlen = 3;
	} else {
		net = 0;
		netlen = 0;
	}
	cp = (const uint8_t *)(egp + 1);
	length -= sizeof(*egp);

	t_gateways = egp->egp_intgw + egp->egp_extgw;
	for (gateways = 0; gateways < t_gateways; ++gateways) {
		/* Pickup host part of gateway address */
		addr = 0;
		if (length < 4 - netlen)
			goto trunc;
		ND_TCHECK2(cp[0], 4 - netlen);
		switch (netlen) {

		case 1:
			addr = *cp++;
			/* fall through */
		case 2:
			addr = (addr << 8) | *cp++;
			/* fall through */
		case 3:
			addr = (addr << 8) | *cp++;
		}
		addr |= net;
		length -= 4 - netlen;
		if (length < 1)
			goto trunc;
		ND_TCHECK2(cp[0], 1);
		distances = *cp++;
		length--;
		ND_PRINT((ndo, " %s %s ",
		       gateways < (int)egp->egp_intgw ? "int" : "ext",
		       ipaddr_string(ndo, &addr)));

		comma = "";
		ND_PRINT((ndo, "("));
		while (--distances >= 0) {
			if (length < 2)
				goto trunc;
			ND_TCHECK2(cp[0], 2);
			ND_PRINT((ndo, "%sd%d:", comma, (int)*cp++));
			comma = ", ";
			networks = *cp++;
			length -= 2;
			while (--networks >= 0) {
				/* Pickup network number */
				if (length < 1)
					goto trunc;
				ND_TCHECK2(cp[0], 1);
				addr = (uint32_t)*cp++ << 24;
				length--;
				if (IN_CLASSB(addr)) {
					if (length < 1)
						goto trunc;
					ND_TCHECK2(cp[0], 1);
					addr |= (uint32_t)*cp++ << 16;
					length--;
				} else if (!IN_CLASSA(addr)) {
					if (length < 2)
						goto trunc;
					ND_TCHECK2(cp[0], 2);
					addr |= (uint32_t)*cp++ << 16;
					addr |= (uint32_t)*cp++ << 8;
					length -= 2;
				}
				ND_PRINT((ndo, " %s", ipaddr_string(ndo, &addr)));
			}
		}
		ND_PRINT((ndo, ")"));
	}
	return;
trunc:
	ND_PRINT((ndo, "[|]"));
}