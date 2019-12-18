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
typedef  int /*<<< orphan*/  uintmax_t ;
struct pfsync_upd_req {int /*<<< orphan*/  creatorid; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pfsync_print_upd_req(netdissect_options *ndo, const void *bp)
{
	const struct pfsync_upd_req *ur = bp;

	ND_PRINT((ndo, "\n\tid: %016jx creatorid: %08x",
	    (uintmax_t)be64toh(ur->id), ntohl(ur->creatorid)));
}