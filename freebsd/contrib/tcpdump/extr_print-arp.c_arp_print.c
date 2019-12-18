#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct arp_pkthdr {int dummy; } ;
struct TYPE_8__ {scalar_t__ ndo_vflag; int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ARPHRD_ATM2225 135 
#define  ARPHRD_FRELAY 134 
#define  ARPOP_INVREPLY 133 
#define  ARPOP_INVREQUEST 132 
#define  ARPOP_REPLY 131 
#define  ARPOP_REQUEST 130 
#define  ARPOP_REVREPLY 129 
#define  ARPOP_REVREQUEST 128 
 int ETHERTYPE_IP ; 
 int ETHERTYPE_TRAIL ; 
 int HRD (struct arp_pkthdr const*) ; 
 scalar_t__ HRD_LEN (struct arp_pkthdr const*) ; 
 int LINKADDR_ETHER ; 
 int LINKADDR_FRELAY ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct arp_pkthdr const) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/ ,int) ; 
 int OP (struct arp_pkthdr const*) ; 
 int PRO (struct arp_pkthdr const*) ; 
 int PROTO_LEN (struct arp_pkthdr const*) ; 
 scalar_t__ SHA (struct arp_pkthdr const*) ; 
 scalar_t__ THA (struct arp_pkthdr const*) ; 
 int /*<<< orphan*/ * TPA (struct arp_pkthdr const*) ; 
 int /*<<< orphan*/  arphrd_values ; 
 int /*<<< orphan*/  arpop_values ; 
 int /*<<< orphan*/  atmarp_print (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  isnonzero (int /*<<< orphan*/  const*,scalar_t__) ; 
 int /*<<< orphan*/  linkaddr_string (TYPE_1__*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  spaddr_print_ip (TYPE_1__*,struct arp_pkthdr const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tpaddr_print_ip (TYPE_1__*,struct arp_pkthdr const*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
arp_print(netdissect_options *ndo,
	  const u_char *bp, u_int length, u_int caplen)
{
	const struct arp_pkthdr *ap;
	u_short pro, hrd, op, linkaddr;

	ap = (const struct arp_pkthdr *)bp;
	ND_TCHECK(*ap);

	hrd = HRD(ap);
	pro = PRO(ap);
	op = OP(ap);


        /* if its ATM then call the ATM ARP printer
           for Frame-relay ARP most of the fields
           are similar to Ethernet so overload the Ethernet Printer
           and set the linkaddr type for linkaddr_string(ndo, ) accordingly */

        switch(hrd) {
        case ARPHRD_ATM2225:
            atmarp_print(ndo, bp, length, caplen);
            return;
        case ARPHRD_FRELAY:
            linkaddr = LINKADDR_FRELAY;
            break;
        default:
            linkaddr = LINKADDR_ETHER;
            break;
	}

	if (!ND_TTEST2(*TPA(ap), PROTO_LEN(ap))) {
		ND_PRINT((ndo, "%s", tstr));
		ND_DEFAULTPRINT((const u_char *)ap, length);
		return;
	}

        if (!ndo->ndo_eflag) {
            ND_PRINT((ndo, "ARP, "));
        }

        /* print hardware type/len and proto type/len */
        if ((pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL) ||
	    PROTO_LEN(ap) != 4 ||
            HRD_LEN(ap) == 0 ||
            ndo->ndo_vflag) {
            ND_PRINT((ndo, "%s (len %u), %s (len %u)",
                      tok2str(arphrd_values, "Unknown Hardware (%u)", hrd),
                      HRD_LEN(ap),
                      tok2str(ethertype_values, "Unknown Protocol (0x%04x)", pro),
                      PROTO_LEN(ap)));

            /* don't know know about the address formats */
            if (!ndo->ndo_vflag) {
                goto out;
            }
	}

        /* print operation */
        ND_PRINT((ndo, "%s%s ",
               ndo->ndo_vflag ? ", " : "",
               tok2str(arpop_values, "Unknown (%u)", op)));

	switch (op) {

	case ARPOP_REQUEST:
		ND_PRINT((ndo, "who-has "));
		tpaddr_print_ip(ndo, ap, pro);
		if (isnonzero((const u_char *)THA(ap), HRD_LEN(ap)))
			ND_PRINT((ndo, " (%s)",
				  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap))));
		ND_PRINT((ndo, " tell "));
		spaddr_print_ip(ndo, ap, pro);
		break;

	case ARPOP_REPLY:
		spaddr_print_ip(ndo, ap, pro);
		ND_PRINT((ndo, " is-at %s",
                          linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_REVREQUEST:
		ND_PRINT((ndo, "who-is %s tell %s",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap)),
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_REVREPLY:
		ND_PRINT((ndo, "%s at ",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap))));
		tpaddr_print_ip(ndo, ap, pro);
		break;

	case ARPOP_INVREQUEST:
		ND_PRINT((ndo, "who-is %s tell %s",
			  linkaddr_string(ndo, THA(ap), linkaddr, HRD_LEN(ap)),
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		break;

	case ARPOP_INVREPLY:
		ND_PRINT((ndo,"%s at ",
			  linkaddr_string(ndo, SHA(ap), linkaddr, HRD_LEN(ap))));
		spaddr_print_ip(ndo, ap, pro);
		break;

	default:
		ND_DEFAULTPRINT((const u_char *)ap, caplen);
		return;
	}

 out:
        ND_PRINT((ndo, ", length %u", length));

	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}