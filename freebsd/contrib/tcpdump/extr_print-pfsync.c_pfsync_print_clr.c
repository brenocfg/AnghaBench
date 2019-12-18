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
struct pfsync_clr {char* ifname; int /*<<< orphan*/  creatorid; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfsync_print_clr(netdissect_options *ndo, const void *bp)
{
	const struct pfsync_clr *clr = bp;

	ND_PRINT((ndo, "\n\tcreatorid: %08x", htonl(clr->creatorid)));
	if (clr->ifname[0] != '\0')
		ND_PRINT((ndo, " interface: %s", clr->ifname));
}