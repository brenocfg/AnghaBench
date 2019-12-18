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
typedef  int u_int ;
typedef  int u_char ;
struct in_addr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int const*) ; 
 int EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ND_TTEST (int const) ; 
#define  PIMV1_TYPE_ASSERT 135 
#define  PIMV1_TYPE_GRAFT 134 
#define  PIMV1_TYPE_GRAFT_ACK 133 
#define  PIMV1_TYPE_JOIN_PRUNE 132 
#define  PIMV1_TYPE_QUERY 131 
#define  PIMV1_TYPE_REGISTER 130 
#define  PIMV1_TYPE_REGISTER_STOP 129 
#define  PIMV1_TYPE_RP_REACHABILITY 128 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  pimv1_join_prune_print (TYPE_1__*,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pimv1_type_str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  unsigned_relts_print (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
pimv1_print(netdissect_options *ndo,
            register const u_char *bp, register u_int len)
{
	register u_char type;

	ND_TCHECK(bp[1]);
	type = bp[1];

	ND_PRINT((ndo, " %s", tok2str(pimv1_type_str, "[type %u]", type)));
	switch (type) {
	case PIMV1_TYPE_QUERY:
		if (ND_TTEST(bp[8])) {
			switch (bp[8] >> 4) {
			case 0:
				ND_PRINT((ndo, " Dense-mode"));
				break;
			case 1:
				ND_PRINT((ndo, " Sparse-mode"));
				break;
			case 2:
				ND_PRINT((ndo, " Sparse-Dense-mode"));
				break;
			default:
				ND_PRINT((ndo, " mode-%d", bp[8] >> 4));
				break;
			}
		}
		if (ndo->ndo_vflag) {
			ND_TCHECK2(bp[10],2);
			ND_PRINT((ndo, " (Hold-time "));
			unsigned_relts_print(ndo, EXTRACT_16BITS(&bp[10]));
			ND_PRINT((ndo, ")"));
		}
		break;

	case PIMV1_TYPE_REGISTER:
		ND_TCHECK2(bp[8], 20);			/* ip header */
		ND_PRINT((ndo, " for %s > %s", ipaddr_string(ndo, &bp[20]),
		    ipaddr_string(ndo, &bp[24])));
		break;
	case PIMV1_TYPE_REGISTER_STOP:
		ND_TCHECK2(bp[12], sizeof(struct in_addr));
		ND_PRINT((ndo, " for %s > %s", ipaddr_string(ndo, &bp[8]),
		    ipaddr_string(ndo, &bp[12])));
		break;
	case PIMV1_TYPE_RP_REACHABILITY:
		if (ndo->ndo_vflag) {
			ND_TCHECK2(bp[22], 2);
			ND_PRINT((ndo, " group %s", ipaddr_string(ndo, &bp[8])));
			if (EXTRACT_32BITS(&bp[12]) != 0xffffffff)
				ND_PRINT((ndo, "/%s", ipaddr_string(ndo, &bp[12])));
			ND_PRINT((ndo, " RP %s hold ", ipaddr_string(ndo, &bp[16])));
			unsigned_relts_print(ndo, EXTRACT_16BITS(&bp[22]));
		}
		break;
	case PIMV1_TYPE_ASSERT:
		ND_TCHECK2(bp[16], sizeof(struct in_addr));
		ND_PRINT((ndo, " for %s > %s", ipaddr_string(ndo, &bp[16]),
		    ipaddr_string(ndo, &bp[8])));
		if (EXTRACT_32BITS(&bp[12]) != 0xffffffff)
			ND_PRINT((ndo, "/%s", ipaddr_string(ndo, &bp[12])));
		ND_TCHECK2(bp[24], 4);
		ND_PRINT((ndo, " %s pref %d metric %d",
		    (bp[20] & 0x80) ? "RP-tree" : "SPT",
		EXTRACT_32BITS(&bp[20]) & 0x7fffffff,
		EXTRACT_32BITS(&bp[24])));
		break;
	case PIMV1_TYPE_JOIN_PRUNE:
	case PIMV1_TYPE_GRAFT:
	case PIMV1_TYPE_GRAFT_ACK:
		if (ndo->ndo_vflag) {
			if (len < 8)
				goto trunc;
			pimv1_join_prune_print(ndo, &bp[8], len - 8);
		}
		break;
	}
	ND_TCHECK(bp[4]);
	if ((bp[4] >> 4) != 1)
		ND_PRINT((ndo, " [v%d]", bp[4] >> 4));
	return;

trunc:
	ND_PRINT((ndo, "[|pim]"));
	return;
}