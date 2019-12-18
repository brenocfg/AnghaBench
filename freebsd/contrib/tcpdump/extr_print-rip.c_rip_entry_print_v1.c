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
typedef  scalar_t__ u_short ;
struct rip_netinfo {int /*<<< orphan*/  rip_metric; int /*<<< orphan*/  rip_dest; int /*<<< orphan*/  rip_family; int /*<<< orphan*/  rip_router; int /*<<< orphan*/  rip_dest_mask; int /*<<< orphan*/  rip_tag; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 scalar_t__ BSD_AFNUM_INET ; 
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RIP_ROUTELEN ; 
 int /*<<< orphan*/  bsd_af_values ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_unknown_data (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
rip_entry_print_v1(netdissect_options *ndo,
                   register const struct rip_netinfo *ni)
{
	register u_short family;

	/* RFC 1058 */
	family = EXTRACT_16BITS(&ni->rip_family);
	if (family != BSD_AFNUM_INET && family != 0) {
		ND_PRINT((ndo, "\n\t AFI %s, ", tok2str(bsd_af_values, "Unknown (%u)", family)));
		print_unknown_data(ndo, (const uint8_t *)&ni->rip_family, "\n\t  ", RIP_ROUTELEN);
		return;
	}
	if (EXTRACT_16BITS(&ni->rip_tag) ||
	    EXTRACT_32BITS(&ni->rip_dest_mask) ||
	    EXTRACT_32BITS(&ni->rip_router)) {
		/* MBZ fields not zero */
                print_unknown_data(ndo, (const uint8_t *)&ni->rip_family, "\n\t  ", RIP_ROUTELEN);
		return;
	}
	if (family == 0) {
		ND_PRINT((ndo, "\n\t  AFI 0, %s, metric: %u",
			ipaddr_string(ndo, &ni->rip_dest),
			EXTRACT_32BITS(&ni->rip_metric)));
		return;
	} /* BSD_AFNUM_INET */
	ND_PRINT((ndo, "\n\t  %s, metric: %u",
               ipaddr_string(ndo, &ni->rip_dest),
	       EXTRACT_32BITS(&ni->rip_metric)));
}