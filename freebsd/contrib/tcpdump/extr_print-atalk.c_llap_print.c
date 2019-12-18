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
typedef  int /*<<< orphan*/  u_short ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct atShortDDP {int /*<<< orphan*/  srcSkt; int /*<<< orphan*/  type; int /*<<< orphan*/  dstSkt; } ;
struct atDDP {int /*<<< orphan*/  srcSkt; int /*<<< orphan*/  srcNode; int /*<<< orphan*/  type; int /*<<< orphan*/  dstSkt; int /*<<< orphan*/  dstNode; int /*<<< orphan*/  dstNet; int /*<<< orphan*/  srcNet; } ;
struct LAP {int type; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ataddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ddpSSize ; 
 int ddpSize ; 
 int /*<<< orphan*/  ddp_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddpskt_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  klap_print (int /*<<< orphan*/  const*,int) ; 
#define  lapDDP 130 
#define  lapKLAP 129 
#define  lapShortDDP 128 

u_int
llap_print(netdissect_options *ndo,
           register const u_char *bp, u_int length)
{
	register const struct LAP *lp;
	register const struct atDDP *dp;
	register const struct atShortDDP *sdp;
	u_short snet;
	u_int hdrlen;

	if (length < sizeof(*lp)) {
		ND_PRINT((ndo, " [|llap %u]", length));
		return (length);
	}
	if (!ND_TTEST2(*bp, sizeof(*lp))) {
		ND_PRINT((ndo, " [|llap]"));
		return (0);	/* cut short by the snapshot length */
	}
	lp = (const struct LAP *)bp;
	bp += sizeof(*lp);
	length -= sizeof(*lp);
	hdrlen = sizeof(*lp);
	switch (lp->type) {

	case lapShortDDP:
		if (length < ddpSSize) {
			ND_PRINT((ndo, " [|sddp %u]", length));
			return (length);
		}
		if (!ND_TTEST2(*bp, ddpSSize)) {
			ND_PRINT((ndo, " [|sddp]"));
			return (0);	/* cut short by the snapshot length */
		}
		sdp = (const struct atShortDDP *)bp;
		ND_PRINT((ndo, "%s.%s",
		    ataddr_string(ndo, 0, lp->src), ddpskt_string(ndo, sdp->srcSkt)));
		ND_PRINT((ndo, " > %s.%s:",
		    ataddr_string(ndo, 0, lp->dst), ddpskt_string(ndo, sdp->dstSkt)));
		bp += ddpSSize;
		length -= ddpSSize;
		hdrlen += ddpSSize;
		ddp_print(ndo, bp, length, sdp->type, 0, lp->src, sdp->srcSkt);
		break;

	case lapDDP:
		if (length < ddpSize) {
			ND_PRINT((ndo, " [|ddp %u]", length));
			return (length);
		}
		if (!ND_TTEST2(*bp, ddpSize)) {
			ND_PRINT((ndo, " [|ddp]"));
			return (0);	/* cut short by the snapshot length */
		}
		dp = (const struct atDDP *)bp;
		snet = EXTRACT_16BITS(&dp->srcNet);
		ND_PRINT((ndo, "%s.%s", ataddr_string(ndo, snet, dp->srcNode),
		    ddpskt_string(ndo, dp->srcSkt)));
		ND_PRINT((ndo, " > %s.%s:",
		    ataddr_string(ndo, EXTRACT_16BITS(&dp->dstNet), dp->dstNode),
		    ddpskt_string(ndo, dp->dstSkt)));
		bp += ddpSize;
		length -= ddpSize;
		hdrlen += ddpSize;
		ddp_print(ndo, bp, length, dp->type, snet, dp->srcNode, dp->srcSkt);
		break;

#ifdef notdef
	case lapKLAP:
		klap_print(bp, length);
		break;
#endif

	default:
		ND_PRINT((ndo, "%d > %d at-lap#%d %u",
		    lp->src, lp->dst, lp->type, length));
		break;
	}
	return (hdrlen);
}