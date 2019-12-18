#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct TYPE_11__ {int ndo_vflag; scalar_t__ ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
#define  DVMRP_ASK_NEIGHBORS 136 
#define  DVMRP_ASK_NEIGHBORS2 135 
#define  DVMRP_GRAFT 134 
#define  DVMRP_GRAFT_ACK 133 
#define  DVMRP_NEIGHBORS 132 
#define  DVMRP_NEIGHBORS2 131 
#define  DVMRP_PROBE 130 
#define  DVMRP_PRUNE 129 
#define  DVMRP_REPORT 128 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  print_graft (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  print_graft_ack (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  print_neighbors (TYPE_1__*,int const*,int const*,int) ; 
 int /*<<< orphan*/  print_neighbors2 (TYPE_1__*,int const*,int const*,int) ; 
 int /*<<< orphan*/  print_probe (TYPE_1__*,int const*,int const*,int) ; 
 int /*<<< orphan*/  print_prune (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  print_report (TYPE_1__*,int const*,int const*,int) ; 
 int target_level ; 

void
dvmrp_print(netdissect_options *ndo,
            register const u_char *bp, register u_int len)
{
	register const u_char *ep;
	register u_char type;

	ep = (const u_char *)ndo->ndo_snapend;
	if (bp >= ep)
		return;

	ND_TCHECK(bp[1]);
	type = bp[1];

	/* Skip IGMP header */
	bp += 8;
	len -= 8;

	switch (type) {

	case DVMRP_PROBE:
		ND_PRINT((ndo, " Probe"));
		if (ndo->ndo_vflag) {
			if (print_probe(ndo, bp, ep, len) < 0)
				goto trunc;
		}
		break;

	case DVMRP_REPORT:
		ND_PRINT((ndo, " Report"));
		if (ndo->ndo_vflag > 1) {
			if (print_report(ndo, bp, ep, len) < 0)
				goto trunc;
		}
		break;

	case DVMRP_ASK_NEIGHBORS:
		ND_PRINT((ndo, " Ask-neighbors(old)"));
		break;

	case DVMRP_NEIGHBORS:
		ND_PRINT((ndo, " Neighbors(old)"));
		if (print_neighbors(ndo, bp, ep, len) < 0)
			goto trunc;
		break;

	case DVMRP_ASK_NEIGHBORS2:
		ND_PRINT((ndo, " Ask-neighbors2"));
		break;

	case DVMRP_NEIGHBORS2:
		ND_PRINT((ndo, " Neighbors2"));
		/*
		 * extract version and capabilities from IGMP group
		 * address field
		 */
		bp -= 4;
		ND_TCHECK2(bp[0], 4);
		target_level = (bp[0] << 24) | (bp[1] << 16) |
		    (bp[2] << 8) | bp[3];
		bp += 4;
		if (print_neighbors2(ndo, bp, ep, len) < 0)
			goto trunc;
		break;

	case DVMRP_PRUNE:
		ND_PRINT((ndo, " Prune"));
		if (print_prune(ndo, bp) < 0)
			goto trunc;
		break;

	case DVMRP_GRAFT:
		ND_PRINT((ndo, " Graft"));
		if (print_graft(ndo, bp) < 0)
			goto trunc;
		break;

	case DVMRP_GRAFT_ACK:
		ND_PRINT((ndo, " Graft-ACK"));
		if (print_graft_ack(ndo, bp) < 0)
			goto trunc;
		break;

	default:
		ND_PRINT((ndo, " [type %d]", type));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "[|dvmrp]"));
	return;
}