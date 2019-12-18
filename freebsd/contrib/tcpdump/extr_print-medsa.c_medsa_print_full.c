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
struct medsa_pkthdr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  CFI (struct medsa_pkthdr const*) ; 
 int CODE (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  ND_DEFAULTPRINT (int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRI (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  SRC_DEV (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  SRC_PORT (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  SRC_TAG (struct medsa_pkthdr const*) ; 
 int TAG (struct medsa_pkthdr const*) ; 
#define  TAG_FORWARD 130 
#define  TAG_FROM_CPU 129 
#define  TAG_TO_CPU 128 
 int /*<<< orphan*/  TRUNK (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  VID (struct medsa_pkthdr const*) ; 
 int /*<<< orphan*/  code_values ; 
 int /*<<< orphan*/  tag_values ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
medsa_print_full(netdissect_options *ndo,
		 const struct medsa_pkthdr *medsa,
		 u_int caplen)
{
	u_char tag = TAG(medsa);

	ND_PRINT((ndo, "%s",
		  tok2str(tag_values, "Unknown (%u)", tag)));

	switch (tag) {
	case TAG_TO_CPU:
		ND_PRINT((ndo, ", %stagged", SRC_TAG(medsa) ? "" : "un"));
		ND_PRINT((ndo, ", dev.port:vlan %d.%d:%d",
			  SRC_DEV(medsa), SRC_PORT(medsa), VID(medsa)));

		ND_PRINT((ndo, ", %s",
			  tok2str(code_values, "Unknown (%u)", CODE(medsa))));
		if (CFI(medsa))
			ND_PRINT((ndo, ", CFI"));

		ND_PRINT((ndo, ", pri %d: ", PRI(medsa)));
		break;
	case TAG_FROM_CPU:
		ND_PRINT((ndo, ", %stagged", SRC_TAG(medsa) ? "" : "un"));
		ND_PRINT((ndo, ", dev.port:vlan %d.%d:%d",
			  SRC_DEV(medsa), SRC_PORT(medsa), VID(medsa)));

		if (CFI(medsa))
			ND_PRINT((ndo, ", CFI"));

		ND_PRINT((ndo, ", pri %d: ", PRI(medsa)));
		break;
	case TAG_FORWARD:
		ND_PRINT((ndo, ", %stagged", SRC_TAG(medsa) ? "" : "un"));
		if (TRUNK(medsa))
			ND_PRINT((ndo, ", dev.trunk:vlan %d.%d:%d",
				  SRC_DEV(medsa), SRC_PORT(medsa), VID(medsa)));
		else
			ND_PRINT((ndo, ", dev.port:vlan %d.%d:%d",
				  SRC_DEV(medsa), SRC_PORT(medsa), VID(medsa)));

		if (CFI(medsa))
			ND_PRINT((ndo, ", CFI"));

		ND_PRINT((ndo, ", pri %d: ", PRI(medsa)));
		break;
	default:
		ND_DEFAULTPRINT((const u_char *)medsa, caplen);
		return;
	}
}