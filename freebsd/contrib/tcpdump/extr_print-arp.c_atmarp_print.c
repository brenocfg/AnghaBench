#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct atmarp_pkthdr {int dummy; } ;
struct TYPE_7__ {scalar_t__ ndo_vflag; int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  ARPOP_INVREPLY 132 
#define  ARPOP_INVREQUEST 131 
#define  ARPOP_NAK 130 
#define  ARPOP_REPLY 129 
#define  ARPOP_REQUEST 128 
 scalar_t__ ATMHRD (struct atmarp_pkthdr const*) ; 
 scalar_t__ ATMOP (struct atmarp_pkthdr const*) ; 
 scalar_t__ ATMPRO (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMSHA (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMSHRD_LEN (struct atmarp_pkthdr const*) ; 
 int ATMSPROTO_LEN (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMSSA (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMSSLN (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMTHA (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMTHRD_LEN (struct atmarp_pkthdr const*) ; 
 int ATMTPROTO_LEN (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMTSA (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  ATMTSLN (struct atmarp_pkthdr const*) ; 
 scalar_t__ ETHERTYPE_IP ; 
 scalar_t__ ETHERTYPE_TRAIL ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct atmarp_pkthdr const) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * aar_tpa (struct atmarp_pkthdr const*) ; 
 int /*<<< orphan*/  arphrd_values ; 
 int /*<<< orphan*/  arpop_values ; 
 int /*<<< orphan*/  atmarp_addr_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmarp_spaddr_print (TYPE_1__*,struct atmarp_pkthdr const*,scalar_t__) ; 
 int /*<<< orphan*/  atmarp_tpaddr_print (TYPE_1__*,struct atmarp_pkthdr const*,scalar_t__) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
atmarp_print(netdissect_options *ndo,
	     const u_char *bp, u_int length, u_int caplen)
{
	const struct atmarp_pkthdr *ap;
	u_short pro, hrd, op;

	ap = (const struct atmarp_pkthdr *)bp;
	ND_TCHECK(*ap);

	hrd = ATMHRD(ap);
	pro = ATMPRO(ap);
	op = ATMOP(ap);

	if (!ND_TTEST2(*aar_tpa(ap), ATMTPROTO_LEN(ap))) {
		ND_PRINT((ndo, "%s", tstr));
		ND_DEFAULTPRINT((const u_char *)ap, length);
		return;
	}

        if (!ndo->ndo_eflag) {
            ND_PRINT((ndo, "ARP, "));
        }

	if ((pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL) ||
	    ATMSPROTO_LEN(ap) != 4 ||
            ATMTPROTO_LEN(ap) != 4 ||
            ndo->ndo_vflag) {
                ND_PRINT((ndo, "%s, %s (len %u/%u)",
                          tok2str(arphrd_values, "Unknown Hardware (%u)", hrd),
                          tok2str(ethertype_values, "Unknown Protocol (0x%04x)", pro),
                          ATMSPROTO_LEN(ap),
                          ATMTPROTO_LEN(ap)));

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
		atmarp_tpaddr_print(ndo, ap, pro);
		if (ATMTHRD_LEN(ap) != 0) {
			ND_PRINT((ndo, " ("));
			atmarp_addr_print(ndo, ATMTHA(ap), ATMTHRD_LEN(ap),
			    ATMTSA(ap), ATMTSLN(ap));
			ND_PRINT((ndo, ")"));
		}
		ND_PRINT((ndo, " tell "));
		atmarp_spaddr_print(ndo, ap, pro);
		break;

	case ARPOP_REPLY:
		atmarp_spaddr_print(ndo, ap, pro);
		ND_PRINT((ndo, " is-at "));
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
                                  ATMSSLN(ap));
		break;

	case ARPOP_INVREQUEST:
		ND_PRINT((ndo, "who-is "));
		atmarp_addr_print(ndo, ATMTHA(ap), ATMTHRD_LEN(ap), ATMTSA(ap),
		    ATMTSLN(ap));
		ND_PRINT((ndo, " tell "));
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
		    ATMSSLN(ap));
		break;

	case ARPOP_INVREPLY:
		atmarp_addr_print(ndo, ATMSHA(ap), ATMSHRD_LEN(ap), ATMSSA(ap),
		    ATMSSLN(ap));
		ND_PRINT((ndo, "at "));
		atmarp_spaddr_print(ndo, ap, pro);
		break;

	case ARPOP_NAK:
		ND_PRINT((ndo, "for "));
		atmarp_spaddr_print(ndo, ap, pro);
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