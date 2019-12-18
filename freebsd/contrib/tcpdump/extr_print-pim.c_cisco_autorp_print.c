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
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int const*) ; 
 int /*<<< orphan*/  unsigned_relts_print (int /*<<< orphan*/ *,int) ; 

void
cisco_autorp_print(netdissect_options *ndo,
                   register const u_char *bp, register u_int len)
{
	int type;
	int numrps;
	int hold;

	if (len < 8)
		goto trunc;
	ND_TCHECK(bp[0]);
	ND_PRINT((ndo, " auto-rp "));
	type = bp[0];
	switch (type) {
	case 0x11:
		ND_PRINT((ndo, "candidate-advert"));
		break;
	case 0x12:
		ND_PRINT((ndo, "mapping"));
		break;
	default:
		ND_PRINT((ndo, "type-0x%02x", type));
		break;
	}

	ND_TCHECK(bp[1]);
	numrps = bp[1];

	ND_TCHECK2(bp[2], 2);
	ND_PRINT((ndo, " Hold "));
	hold = EXTRACT_16BITS(&bp[2]);
	if (hold)
		unsigned_relts_print(ndo, EXTRACT_16BITS(&bp[2]));
	else
		ND_PRINT((ndo, "FOREVER"));

	/* Next 4 bytes are reserved. */

	bp += 8; len -= 8;

	/*XXX skip unless -v? */

	/*
	 * Rest of packet:
	 * numrps entries of the form:
	 * 32 bits: RP
	 * 6 bits: reserved
	 * 2 bits: PIM version supported, bit 0 is "supports v1", 1 is "v2".
	 * 8 bits: # of entries for this RP
	 * each entry: 7 bits: reserved, 1 bit: negative,
	 *	       8 bits: mask 32 bits: source
	 * lather, rinse, repeat.
	 */
	while (numrps--) {
		int nentries;
		char s;

		if (len < 4)
			goto trunc;
		ND_TCHECK2(bp[0], 4);
		ND_PRINT((ndo, " RP %s", ipaddr_string(ndo, bp)));
		bp += 4;
		len -= 4;
		if (len < 1)
			goto trunc;
		ND_TCHECK(bp[0]);
		switch (bp[0] & 0x3) {
		case 0: ND_PRINT((ndo, " PIMv?"));
			break;
		case 1:	ND_PRINT((ndo, " PIMv1"));
			break;
		case 2:	ND_PRINT((ndo, " PIMv2"));
			break;
		case 3:	ND_PRINT((ndo, " PIMv1+2"));
			break;
		}
		if (bp[0] & 0xfc)
			ND_PRINT((ndo, " [rsvd=0x%02x]", bp[0] & 0xfc));
		bp += 1;
		len -= 1;
		if (len < 1)
			goto trunc;
		ND_TCHECK(bp[0]);
		nentries = bp[0];
		bp += 1;
		len -= 1;
		s = ' ';
		for (; nentries; nentries--) {
			if (len < 6)
				goto trunc;
			ND_TCHECK2(bp[0], 6);
			ND_PRINT((ndo, "%c%s%s/%d", s, bp[0] & 1 ? "!" : "",
			          ipaddr_string(ndo, &bp[2]), bp[1]));
			if (bp[0] & 0x02) {
				ND_PRINT((ndo, " bidir"));
			}
			if (bp[0] & 0xfc) {
				ND_PRINT((ndo, "[rsvd=0x%02x]", bp[0] & 0xfc));
			}
			s = ',';
			bp += 6; len -= 6;
		}
	}
	return;

trunc:
	ND_PRINT((ndo, "[|autorp]"));
	return;
}