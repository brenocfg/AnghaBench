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
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int int32_t ;

/* Variables and functions */
 unsigned long EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  INTOUT () ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  PRNAMEMAX ; 
 scalar_t__ RX_PACKET_TYPE_DATA ; 
 int /*<<< orphan*/  VECOUT (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ubik (int) ; 
 int /*<<< orphan*/  pt_req ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ubik_reply_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int) ; 

__attribute__((used)) static void
prot_reply_print(netdissect_options *ndo,
                 register const u_char *bp, int length, int32_t opcode)
{
	const struct rx_header *rxh;
	unsigned long i;

	if (length < (int)sizeof(struct rx_header))
		return;

	rxh = (const struct rx_header *) bp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from ptserver/ptint.xg.  Check to see if it's a
	 * Ubik call, however.
	 */

	ND_PRINT((ndo, " pt"));

	if (is_ubik(opcode)) {
		ubik_reply_print(ndo, bp, length, opcode);
		return;
	}

	ND_PRINT((ndo, " reply %s", tok2str(pt_req, "op#%d", opcode)));

	bp += sizeof(struct rx_header);

	/*
	 * If it was a data packet, interpret the response
	 */

	if (rxh->type == RX_PACKET_TYPE_DATA)
		switch (opcode) {
		case 504:		/* Name to ID */
		{
			unsigned long j;
			ND_PRINT((ndo, " ids:"));
			ND_TCHECK2(bp[0], 4);
			i = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			for (j = 0; j < i; j++)
				INTOUT();
			if (j == 0)
				ND_PRINT((ndo, " <none!>"));
		}
			break;
		case 505:		/* ID to name */
		{
			unsigned long j;
			ND_TCHECK2(bp[0], 4);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);

			/*
			 * Who designed this chicken-shit protocol?
			 *
			 * Each character is stored as a 32-bit
			 * integer!
			 */

			for (i = 0; i < j; i++) {
				VECOUT(PRNAMEMAX);
			}
			if (j == 0)
				ND_PRINT((ndo, " <none!>"));
		}
			break;
		case 508:		/* Get CPS */
		case 514:		/* List elements */
		case 517:		/* List owned */
		case 518:		/* Get CPS2 */
		case 519:		/* Get host CPS */
		{
			unsigned long j;
			ND_TCHECK2(bp[0], 4);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);
			for (i = 0; i < j; i++) {
				INTOUT();
			}
			if (j == 0)
				ND_PRINT((ndo, " <none!>"));
		}
			break;
		case 510:		/* List max */
			ND_PRINT((ndo, " maxuid"));
			INTOUT();
			ND_PRINT((ndo, " maxgid"));
			INTOUT();
			break;
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
	ND_PRINT((ndo, " [|pt]"));
}