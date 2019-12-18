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
struct netinfo6 {int /*<<< orphan*/  rip6_metric; scalar_t__ rip6_tag; int /*<<< orphan*/  rip6_plen; int /*<<< orphan*/  rip6_dest; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (scalar_t__*) ; 
 int ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip6addr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rip6_entry_print(netdissect_options *ndo, register const struct netinfo6 *ni, int metric)
{
	int l;
	l = ND_PRINT((ndo, "%s/%d", ip6addr_string(ndo, &ni->rip6_dest), ni->rip6_plen));
	if (ni->rip6_tag)
		l += ND_PRINT((ndo, " [%d]", EXTRACT_16BITS(&ni->rip6_tag)));
	if (metric)
		l += ND_PRINT((ndo, " (%d)", ni->rip6_metric));
	return l;
}