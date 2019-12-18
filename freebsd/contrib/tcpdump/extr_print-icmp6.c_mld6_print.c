#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct mld6_hdr {int /*<<< orphan*/  mld6_addr; int /*<<< orphan*/  mld6_maxdelay; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ip6addr_string (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mld6_print(netdissect_options *ndo, const u_char *bp)
{
	const struct mld6_hdr *mp = (const struct mld6_hdr *)bp;
	const u_char *ep;

	/* 'ep' points to the end of available data. */
	ep = ndo->ndo_snapend;

	if ((const u_char *)mp + sizeof(*mp) > ep)
		return;

	ND_PRINT((ndo,"max resp delay: %d ", EXTRACT_16BITS(&mp->mld6_maxdelay)));
	ND_PRINT((ndo,"addr: %s", ip6addr_string(ndo, &mp->mld6_addr)));
}