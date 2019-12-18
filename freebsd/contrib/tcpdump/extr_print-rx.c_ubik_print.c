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
struct rx_header {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DATEOUT () ; 
 int EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  INTOUT () ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ND_TCHECK_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  UBIK_VERSIONOUT () ; 
 int /*<<< orphan*/  UINTOUT () ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ubik_lock_types ; 
 int /*<<< orphan*/  ubik_req ; 

__attribute__((used)) static void
ubik_print(netdissect_options *ndo,
           register const u_char *bp)
{
	int ubik_op;
	int32_t temp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from ubik/ubik_int.xg
	 */

	/* Every function that calls this function first makes a bounds check
	 * for (sizeof(rx_header) + 4) bytes, so long as it remains this way
	 * the line below will not over-read.
	 */
	ubik_op = EXTRACT_32BITS(bp + sizeof(struct rx_header));

	ND_PRINT((ndo, " ubik call %s", tok2str(ubik_req, "op#%d", ubik_op)));

	/*
	 * Decode some of the arguments to the Ubik calls
	 */

	bp += sizeof(struct rx_header) + 4;

	switch (ubik_op) {
		case 10000:		/* Beacon */
			ND_TCHECK2(bp[0], 4);
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			ND_PRINT((ndo, " syncsite %s", temp ? "yes" : "no"));
			ND_PRINT((ndo, " votestart"));
			DATEOUT();
			ND_PRINT((ndo, " dbversion"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			break;
		case 10003:		/* Get sync site */
			ND_PRINT((ndo, " site"));
			UINTOUT();
			break;
		case 20000:		/* Begin */
		case 20001:		/* Commit */
		case 20007:		/* Abort */
		case 20008:		/* Release locks */
		case 20010:		/* Writev */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			break;
		case 20002:		/* Lock */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " pos"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			ND_TCHECK_32BITS(bp);
			temp = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			tok2str(ubik_lock_types, "type %d", temp);
			break;
		case 20003:		/* Write */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " pos"));
			INTOUT();
			break;
		case 20005:		/* Get file */
			ND_PRINT((ndo, " file"));
			INTOUT();
			break;
		case 20006:		/* Send file */
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			ND_PRINT((ndo, " dbversion"));
			UBIK_VERSIONOUT();
			break;
		case 20009:		/* Truncate */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " file"));
			INTOUT();
			ND_PRINT((ndo, " length"));
			INTOUT();
			break;
		case 20012:		/* Set version */
			ND_PRINT((ndo, " tid"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " oldversion"));
			UBIK_VERSIONOUT();
			ND_PRINT((ndo, " newversion"));
			UBIK_VERSIONOUT();
			break;
		default:
			;
	}

	return;

trunc:
	ND_PRINT((ndo, " [|ubik]"));
}