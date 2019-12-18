#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ u_char ;
struct TYPE_5__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int AHCP1_BODY_MIN_LEN ; 
 int EXTRACT_16BITS (scalar_t__ const*) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK2 (scalar_t__ const,int) ; 
 int /*<<< orphan*/  ahcp1_msg_str ; 
 int /*<<< orphan*/  ahcp1_options_print (TYPE_1__*,scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
ahcp1_body_print(netdissect_options *ndo, const u_char *cp, const u_char *ep)
{
	uint8_t type, mbz;
	uint16_t body_len;

	if (cp + AHCP1_BODY_MIN_LEN > ep)
		goto invalid;
	/* Type */
	ND_TCHECK2(*cp, 1);
	type = *cp;
	cp += 1;
	/* MBZ */
	ND_TCHECK2(*cp, 1);
	mbz = *cp;
	cp += 1;
	/* Length */
	ND_TCHECK2(*cp, 2);
	body_len = EXTRACT_16BITS(cp);
	cp += 2;

	if (ndo->ndo_vflag) {
		ND_PRINT((ndo, "\n\t%s", tok2str(ahcp1_msg_str, "Unknown-%u", type)));
		if (mbz != 0)
			ND_PRINT((ndo, ", MBZ %u", mbz));
		ND_PRINT((ndo, ", Length %u", body_len));
	}
	if (cp + body_len > ep)
		goto invalid;

	/* Options */
	if (ndo->ndo_vflag >= 2)
		ahcp1_options_print(ndo, cp, cp + body_len); /* not ep (ignore extra data) */
	else
		ND_TCHECK2(*cp, body_len);
	return;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return;
trunc:
	ND_PRINT((ndo, "%s", tstr));
}