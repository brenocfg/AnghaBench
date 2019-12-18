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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct medsa_pkthdr {int /*<<< orphan*/  ether_type; } ;
struct lladdr_info {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_suppress_default_print; scalar_t__ ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ ETHERMTU ; 
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct medsa_pkthdr const) ; 
 int /*<<< orphan*/  SRC_DEV (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  SRC_PORT (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  VID (struct medsa_pkthdr const*) ; 
 scalar_t__ ethertype_print (TYPE_1__*,scalar_t__,int /*<<< orphan*/  const*,int,int,struct lladdr_info const*,struct lladdr_info const*) ; 
 int /*<<< orphan*/  ethertype_values ; 
 scalar_t__ llc_print (TYPE_1__*,int /*<<< orphan*/  const*,int,int,struct lladdr_info const*,struct lladdr_info const*) ; 
 int /*<<< orphan*/  medsa_print_full (TYPE_1__*,struct medsa_pkthdr const*,int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

void
medsa_print(netdissect_options *ndo,
	    const u_char *bp, u_int length, u_int caplen,
	    const struct lladdr_info *src, const struct lladdr_info *dst)
{
	const struct medsa_pkthdr *medsa;
	u_short ether_type;

	medsa = (const struct medsa_pkthdr *)bp;
	ND_TCHECK(*medsa);

	if (!ndo->ndo_eflag)
		ND_PRINT((ndo, "MEDSA %d.%d:%d: ",
			  SRC_DEV(medsa), SRC_PORT(medsa), VID(medsa)));
	else
		medsa_print_full(ndo, medsa, caplen);

	bp += 8;
	length -= 8;
	caplen -= 8;

	ether_type = EXTRACT_16BITS(&medsa->ether_type);
	if (ether_type <= ETHERMTU) {
		/* Try to print the LLC-layer header & higher layers */
		if (llc_print(ndo, bp, length, caplen, src, dst) < 0) {
			/* packet type not known, print raw packet */
			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(bp, caplen);
		}
	} else {
		if (ndo->ndo_eflag)
			ND_PRINT((ndo, "ethertype %s (0x%04x) ",
				  tok2str(ethertype_values, "Unknown",
					  ether_type),
				  ether_type));
		if (ethertype_print(ndo, ether_type, bp, length, caplen, src, dst) == 0) {
			/* ether_type not known, print raw packet */
			if (!ndo->ndo_eflag)
				ND_PRINT((ndo, "ethertype %s (0x%04x) ",
					  tok2str(ethertype_values, "Unknown",
						  ether_type),
					  ether_type));

			if (!ndo->ndo_suppress_default_print)
				ND_DEFAULTPRINT(bp, caplen);
		}
	}
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}