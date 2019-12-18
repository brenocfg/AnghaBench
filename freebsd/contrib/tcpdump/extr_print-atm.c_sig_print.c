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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 size_t CALL_REF_POS ; 
 int /*<<< orphan*/  EXTRACT_24BITS (scalar_t__ const*) ; 
 size_t MSG_TYPE_POS ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (scalar_t__ const) ; 
 size_t PROTO_POS ; 
 scalar_t__ const Q2931 ; 
 int /*<<< orphan*/  msgtype2str ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__ const) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
sig_print(netdissect_options *ndo,
          const u_char *p)
{
	uint32_t call_ref;

	ND_TCHECK(p[PROTO_POS]);
	if (p[PROTO_POS] == Q2931) {
		/*
		 * protocol:Q.2931 for User to Network Interface
		 * (UNI 3.1) signalling
		 */
		ND_PRINT((ndo, "Q.2931"));
		ND_TCHECK(p[MSG_TYPE_POS]);
		ND_PRINT((ndo, ":%s ",
		    tok2str(msgtype2str, "msgtype#%d", p[MSG_TYPE_POS])));

		/*
		 * The call reference comes before the message type,
		 * so if we know we have the message type, which we
		 * do from the caplen test above, we also know we have
		 * the call reference.
		 */
		call_ref = EXTRACT_24BITS(&p[CALL_REF_POS]);
		ND_PRINT((ndo, "CALL_REF:0x%06x", call_ref));
	} else {
		/* SCCOP with some unknown protocol atop it */
		ND_PRINT((ndo, "SSCOP, proto %d ", p[PROTO_POS]));
	}
	return;

trunc:
	ND_PRINT((ndo, " %s", tstr));
}