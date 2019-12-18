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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTOUT () ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 scalar_t__ RX_PACKET_TYPE_DATA ; 
 scalar_t__ is_ubik (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_req ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubik_reply_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kauth_reply_print(netdissect_options *ndo,
                  register const u_char *bp, int length, int32_t opcode)
{
	const struct rx_header *rxh;

	if (length <= (int)sizeof(struct rx_header))
		return;

	rxh = (const struct rx_header *) bp;

	/*
	 * Print out the afs call we're invoking.  The table used here was
	 * gleaned from kauth/kauth.rg
	 */

	ND_PRINT((ndo, " kauth"));

	if (is_ubik(opcode)) {
		ubik_reply_print(ndo, bp, length, opcode);
		return;
	}

	ND_PRINT((ndo, " reply %s", tok2str(kauth_req, "op#%d", opcode)));

	bp += sizeof(struct rx_header);

	/*
	 * If it was a data packet, interpret the response.
	 */

	if (rxh->type == RX_PACKET_TYPE_DATA)
		/* Well, no, not really.  Leave this for later */
		;
	else {
		/*
		 * Otherwise, just print out the return code
		 */
		ND_PRINT((ndo, " errcode"));
		INTOUT();
	}

	return;

trunc:
	ND_PRINT((ndo, " [|kauth]"));
}