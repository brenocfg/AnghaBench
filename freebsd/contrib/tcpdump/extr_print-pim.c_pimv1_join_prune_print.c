#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct in_addr {int dummy; } ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int EXTRACT_32BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 scalar_t__ ND_TTEST2 (int const,int) ; 
 int /*<<< orphan*/  ipaddr_string (TYPE_1__*,int const*) ; 
 int /*<<< orphan*/  unsigned_relts_print (TYPE_1__*,int) ; 

__attribute__((used)) static void
pimv1_join_prune_print(netdissect_options *ndo,
                       register const u_char *bp, register u_int len)
{
	int ngroups, njoin, nprune;
	int njp;

	/* If it's a single group and a single source, use 1-line output. */
	if (ND_TTEST2(bp[0], 30) && bp[11] == 1 &&
	    ((njoin = EXTRACT_16BITS(&bp[20])) + EXTRACT_16BITS(&bp[22])) == 1) {
		int hold;

		ND_PRINT((ndo, " RPF %s ", ipaddr_string(ndo, bp)));
		hold = EXTRACT_16BITS(&bp[6]);
		if (hold != 180) {
			ND_PRINT((ndo, "Hold "));
			unsigned_relts_print(ndo, hold);
		}
		ND_PRINT((ndo, "%s (%s/%d, %s", njoin ? "Join" : "Prune",
		ipaddr_string(ndo, &bp[26]), bp[25] & 0x3f,
		ipaddr_string(ndo, &bp[12])));
		if (EXTRACT_32BITS(&bp[16]) != 0xffffffff)
			ND_PRINT((ndo, "/%s", ipaddr_string(ndo, &bp[16])));
		ND_PRINT((ndo, ") %s%s %s",
		    (bp[24] & 0x01) ? "Sparse" : "Dense",
		    (bp[25] & 0x80) ? " WC" : "",
		    (bp[25] & 0x40) ? "RP" : "SPT"));
		return;
	}

	if (len < sizeof(struct in_addr))
		goto trunc;
	ND_TCHECK2(bp[0], sizeof(struct in_addr));
	if (ndo->ndo_vflag > 1)
		ND_PRINT((ndo, "\n"));
	ND_PRINT((ndo, " Upstream Nbr: %s", ipaddr_string(ndo, bp)));
	bp += 4;
	len -= 4;
	if (len < 4)
		goto trunc;
	ND_TCHECK2(bp[2], 2);
	if (ndo->ndo_vflag > 1)
		ND_PRINT((ndo, "\n"));
	ND_PRINT((ndo, " Hold time: "));
	unsigned_relts_print(ndo, EXTRACT_16BITS(&bp[2]));
	if (ndo->ndo_vflag < 2)
		return;
	bp += 4;
	len -= 4;

	if (len < 4)
		goto trunc;
	ND_TCHECK2(bp[0], 4);
	ngroups = bp[3];
	bp += 4;
	len -= 4;
	while (ngroups--) {
		/*
		 * XXX - does the address have length "addrlen" and the
		 * mask length "maddrlen"?
		 */
		if (len < 4)
			goto trunc;
		ND_TCHECK2(bp[0], sizeof(struct in_addr));
		ND_PRINT((ndo, "\n\tGroup: %s", ipaddr_string(ndo, bp)));
		bp += 4;
		len -= 4;
		if (len < 4)
			goto trunc;
		ND_TCHECK2(bp[0], sizeof(struct in_addr));
		if (EXTRACT_32BITS(&bp[0]) != 0xffffffff)
			ND_PRINT((ndo, "/%s", ipaddr_string(ndo, &bp[0])));
		bp += 4;
		len -= 4;
		if (len < 4)
			goto trunc;
		ND_TCHECK2(bp[0], 4);
		njoin = EXTRACT_16BITS(&bp[0]);
		nprune = EXTRACT_16BITS(&bp[2]);
		ND_PRINT((ndo, " joined: %d pruned: %d", njoin, nprune));
		bp += 4;
		len -= 4;
		for (njp = 0; njp < (njoin + nprune); njp++) {
			const char *type;

			if (njp < njoin)
				type = "Join ";
			else
				type = "Prune";
			if (len < 6)
				goto trunc;
			ND_TCHECK2(bp[0], 6);
			ND_PRINT((ndo, "\n\t%s %s%s%s%s/%d", type,
			    (bp[0] & 0x01) ? "Sparse " : "Dense ",
			    (bp[1] & 0x80) ? "WC " : "",
			    (bp[1] & 0x40) ? "RP " : "SPT ",
			    ipaddr_string(ndo, &bp[2]),
			    bp[1] & 0x3f));
			bp += 6;
			len -= 6;
		}
	}
	return;
trunc:
	ND_PRINT((ndo, "[|pim]"));
	return;
}