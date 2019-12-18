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
typedef  scalar_t__ u_short ;
struct atmarp_pkthdr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ATMTPA (struct atmarp_pkthdr const*) ; 
 int ATMTPROTO_LEN (struct atmarp_pkthdr const*) ; 
 scalar_t__ ETHERTYPE_IP ; 
 scalar_t__ ETHERTYPE_TRAIL ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atmarp_tpaddr_print(netdissect_options *ndo,
		    const struct atmarp_pkthdr *ap, u_short pro)
{
	if (pro != ETHERTYPE_IP && pro != ETHERTYPE_TRAIL)
		ND_PRINT((ndo, "<wrong proto type>"));
	else if (ATMTPROTO_LEN(ap) != 4)
		ND_PRINT((ndo, "<wrong tplen>"));
	else
		ND_PRINT((ndo, "%s", ipaddr_string(ndo, ATMTPA(ap))));
}