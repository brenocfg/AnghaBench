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
typedef  int /*<<< orphan*/  u_char ;
struct rx_header {scalar_t__ type; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFSUUIDOUT () ; 
 unsigned long EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  INTOUT () ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 scalar_t__ RX_PACKET_TYPE_DATA ; 
 int /*<<< orphan*/  UINTOUT () ; 
 int /*<<< orphan*/  VECOUT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLNAMEMAX ; 
 int /*<<< orphan*/  intoa (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ubik (int) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ubik_reply_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  vldb_req ; 

__attribute__((used)) static void
vldb_reply_print(netdissect_options *ndo,
                 register const u_char *bp, int length, int32_t opcode)
{
	const struct rx_header *rxh;
	unsigned long i;

	if (length < (int)sizeof(struct rx_header))
		return;

	rxh = (const struct rx_header *) bp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from vlserver/vldbint.xg.  Check to see if it's a
	 * Ubik call, however.
	 */

	ND_PRINT((ndo, " vldb"));

	if (is_ubik(opcode)) {
		ubik_reply_print(ndo, bp, length, opcode);
		return;
	}

	ND_PRINT((ndo, " reply %s", tok2str(vldb_req, "op#%d", opcode)));

	bp += sizeof(struct rx_header);

	/*
	 * If it was a data packet, interpret the response
	 */

	if (rxh->type == RX_PACKET_TYPE_DATA)
		switch (opcode) {
		case 510:	/* List entry */
			ND_PRINT((ndo, " count"));
			INTOUT();
			ND_PRINT((ndo, " nextindex"));
			INTOUT();
		case 503:	/* Get entry by id */
		case 504:	/* Get entry by name */
		{	unsigned long nservers, j;
			VECOUT(VLNAMEMAX);
			ND_TCHECK2(bp[0], sizeof(int32_t));
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " numservers"));
			ND_TCHECK2(bp[0], sizeof(int32_t));
			nservers = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " %lu", nservers));
			ND_PRINT((ndo, " servers"));
			for (i = 0; i < 8; i++) {
				ND_TCHECK2(bp[0], sizeof(int32_t));
				if (i < nservers)
					ND_PRINT((ndo, " %s",
					   intoa(((const struct in_addr *) bp)->s_addr)));
				bp += sizeof(int32_t);
			}
			ND_PRINT((ndo, " partitions"));
			for (i = 0; i < 8; i++) {
				ND_TCHECK2(bp[0], sizeof(int32_t));
				j = EXTRACT_32BITS(bp);
				if (i < nservers && j <= 26)
					ND_PRINT((ndo, " %c", 'a' + (int)j));
				else if (i < nservers)
					ND_PRINT((ndo, " %lu", j));
				bp += sizeof(int32_t);
			}
			ND_TCHECK2(bp[0], 8 * sizeof(int32_t));
			bp += 8 * sizeof(int32_t);
			ND_PRINT((ndo, " rwvol"));
			UINTOUT();
			ND_PRINT((ndo, " rovol"));
			UINTOUT();
			ND_PRINT((ndo, " backup"));
			UINTOUT();
		}
			break;
		case 505:	/* Get new volume ID */
			ND_PRINT((ndo, " newvol"));
			UINTOUT();
			break;
		case 521:	/* List entry */
		case 529:	/* List entry U */
			ND_PRINT((ndo, " count"));
			INTOUT();
			ND_PRINT((ndo, " nextindex"));
			INTOUT();
		case 518:	/* Get entry by ID N */
		case 519:	/* Get entry by name N */
		{	unsigned long nservers, j;
			VECOUT(VLNAMEMAX);
			ND_PRINT((ndo, " numservers"));
			ND_TCHECK2(bp[0], sizeof(int32_t));
			nservers = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " %lu", nservers));
			ND_PRINT((ndo, " servers"));
			for (i = 0; i < 13; i++) {
				ND_TCHECK2(bp[0], sizeof(int32_t));
				if (i < nservers)
					ND_PRINT((ndo, " %s",
					   intoa(((const struct in_addr *) bp)->s_addr)));
				bp += sizeof(int32_t);
			}
			ND_PRINT((ndo, " partitions"));
			for (i = 0; i < 13; i++) {
				ND_TCHECK2(bp[0], sizeof(int32_t));
				j = EXTRACT_32BITS(bp);
				if (i < nservers && j <= 26)
					ND_PRINT((ndo, " %c", 'a' + (int)j));
				else if (i < nservers)
					ND_PRINT((ndo, " %lu", j));
				bp += sizeof(int32_t);
			}
			ND_TCHECK2(bp[0], 13 * sizeof(int32_t));
			bp += 13 * sizeof(int32_t);
			ND_PRINT((ndo, " rwvol"));
			UINTOUT();
			ND_PRINT((ndo, " rovol"));
			UINTOUT();
			ND_PRINT((ndo, " backup"));
			UINTOUT();
		}
			break;
		case 526:	/* Get entry by ID U */
		case 527:	/* Get entry by name U */
		{	unsigned long nservers, j;
			VECOUT(VLNAMEMAX);
			ND_PRINT((ndo, " numservers"));
			ND_TCHECK2(bp[0], sizeof(int32_t));
			nservers = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " %lu", nservers));
			ND_PRINT((ndo, " servers"));
			for (i = 0; i < 13; i++) {
				if (i < nservers) {
					ND_PRINT((ndo, " afsuuid"));
					AFSUUIDOUT();
				} else {
					ND_TCHECK2(bp[0], 44);
					bp += 44;
				}
			}
			ND_TCHECK2(bp[0], 4 * 13);
			bp += 4 * 13;
			ND_PRINT((ndo, " partitions"));
			for (i = 0; i < 13; i++) {
				ND_TCHECK2(bp[0], sizeof(int32_t));
				j = EXTRACT_32BITS(bp);
				if (i < nservers && j <= 26)
					ND_PRINT((ndo, " %c", 'a' + (int)j));
				else if (i < nservers)
					ND_PRINT((ndo, " %lu", j));
				bp += sizeof(int32_t);
			}
			ND_TCHECK2(bp[0], 13 * sizeof(int32_t));
			bp += 13 * sizeof(int32_t);
			ND_PRINT((ndo, " rwvol"));
			UINTOUT();
			ND_PRINT((ndo, " rovol"));
			UINTOUT();
			ND_PRINT((ndo, " backup"));
			UINTOUT();
		}
		default:
			;
		}

	else {
		/*
		 * Otherwise, just print out the return code
		 */
		ND_PRINT((ndo, " errcode"));
		INTOUT();
	}

	return;

trunc:
	ND_PRINT((ndo, " [|vldb]"));
}