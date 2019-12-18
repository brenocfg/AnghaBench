#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct rx_header {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AFSUUIDOUT () ; 
 int /*<<< orphan*/  DATEOUT () ; 
 void* EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FIDOUT () ; 
 int /*<<< orphan*/  INTOUT () ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ND_TCHECK_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cb_req ; 
 int /*<<< orphan*/  cb_types ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,unsigned long) ; 

__attribute__((used)) static void
cb_print(netdissect_options *ndo,
         register const u_char *bp, int length)
{
	int cb_op;
	unsigned long i;

	if (length <= (int)sizeof(struct rx_header))
		return;

	if (ndo->ndo_snapend - bp + 1 <= (int)(sizeof(struct rx_header) + sizeof(int32_t))) {
		goto trunc;
	}

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from fsint/afscbint.xg
	 */

	cb_op = EXTRACT_32BITS(bp + sizeof(struct rx_header));

	ND_PRINT((ndo, " cb call %s", tok2str(cb_req, "op#%d", cb_op)));

	bp += sizeof(struct rx_header) + 4;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from fsint/afscbint.xg
	 */

	switch (cb_op) {
		case 204:		/* Callback */
		{
			unsigned long j, t;
			ND_TCHECK2(bp[0], 4);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);

			for (i = 0; i < j; i++) {
				FIDOUT();
				if (i != j - 1)
					ND_PRINT((ndo, ","));
			}

			if (j == 0)
				ND_PRINT((ndo, " <none!>"));

			ND_TCHECK_32BITS(bp);
			j = EXTRACT_32BITS(bp);
			bp += sizeof(int32_t);

			if (j != 0)
				ND_PRINT((ndo, ";"));

			for (i = 0; i < j; i++) {
				ND_PRINT((ndo, " ver"));
				INTOUT();
				ND_PRINT((ndo, " expires"));
				DATEOUT();
				ND_TCHECK2(bp[0], 4);
				t = EXTRACT_32BITS(bp);
				bp += sizeof(int32_t);
				tok2str(cb_types, "type %d", t);
			}
		}
		case 214: {
			ND_PRINT((ndo, " afsuuid"));
			AFSUUIDOUT();
			break;
		}
		default:
			;
	}

	return;

trunc:
	ND_PRINT((ndo, " [|cb]"));
}