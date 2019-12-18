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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int DESC_STR_LEN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,scalar_t__ const) ; 
 scalar_t__ const OF_DESC_STATS_LEN ; 
 int SERIAL_NUM_LEN ; 
 int /*<<< orphan*/  fn_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  istr ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static const u_char *
of10_desc_stats_reply_print(netdissect_options *ndo,
                            const u_char *cp, const u_char *ep, const u_int len)
{
	if (len != OF_DESC_STATS_LEN)
		goto invalid;
	/* mfr_desc */
	ND_TCHECK2(*cp, DESC_STR_LEN);
	ND_PRINT((ndo, "\n\t  mfr_desc '"));
	fn_print(ndo, cp, cp + DESC_STR_LEN);
	ND_PRINT((ndo, "'"));
	cp += DESC_STR_LEN;
	/* hw_desc */
	ND_TCHECK2(*cp, DESC_STR_LEN);
	ND_PRINT((ndo, "\n\t  hw_desc '"));
	fn_print(ndo, cp, cp + DESC_STR_LEN);
	ND_PRINT((ndo, "'"));
	cp += DESC_STR_LEN;
	/* sw_desc */
	ND_TCHECK2(*cp, DESC_STR_LEN);
	ND_PRINT((ndo, "\n\t  sw_desc '"));
	fn_print(ndo, cp, cp + DESC_STR_LEN);
	ND_PRINT((ndo, "'"));
	cp += DESC_STR_LEN;
	/* serial_num */
	ND_TCHECK2(*cp, SERIAL_NUM_LEN);
	ND_PRINT((ndo, "\n\t  serial_num '"));
	fn_print(ndo, cp, cp + SERIAL_NUM_LEN);
	ND_PRINT((ndo, "'"));
	cp += SERIAL_NUM_LEN;
	/* dp_desc */
	ND_TCHECK2(*cp, DESC_STR_LEN);
	ND_PRINT((ndo, "\n\t  dp_desc '"));
	fn_print(ndo, cp, cp + DESC_STR_LEN);
	ND_PRINT((ndo, "'"));
	return cp + DESC_STR_LEN;

invalid: /* skip the message body */
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, len);
	return cp + len;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return ep;
}