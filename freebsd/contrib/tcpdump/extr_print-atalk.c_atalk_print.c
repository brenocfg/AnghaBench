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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct atDDP {int /*<<< orphan*/  srcSkt; int /*<<< orphan*/  srcNode; int /*<<< orphan*/  type; int /*<<< orphan*/  dstSkt; int /*<<< orphan*/  dstNode; int /*<<< orphan*/  dstNet; int /*<<< orphan*/  srcNet; } ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_eflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  ataddr_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ddpSize ; 
 int /*<<< orphan*/  ddp_print (TYPE_1__*,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddpskt_string (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
atalk_print(netdissect_options *ndo,
            register const u_char *bp, u_int length)
{
	register const struct atDDP *dp;
	u_short snet;

        if(!ndo->ndo_eflag)
            ND_PRINT((ndo, "AT "));

	if (length < ddpSize) {
		ND_PRINT((ndo, " [|ddp %u]", length));
		return;
	}
	if (!ND_TTEST2(*bp, ddpSize)) {
		ND_PRINT((ndo, " [|ddp]"));
		return;
	}
	dp = (const struct atDDP *)bp;
	snet = EXTRACT_16BITS(&dp->srcNet);
	ND_PRINT((ndo, "%s.%s", ataddr_string(ndo, snet, dp->srcNode),
	       ddpskt_string(ndo, dp->srcSkt)));
	ND_PRINT((ndo, " > %s.%s: ",
	       ataddr_string(ndo, EXTRACT_16BITS(&dp->dstNet), dp->dstNode),
	       ddpskt_string(ndo, dp->dstSkt)));
	bp += ddpSize;
	length -= ddpSize;
	ddp_print(ndo, bp, length, dp->type, snet, dp->srcNode, dp->srcSkt);
}