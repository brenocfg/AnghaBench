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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ip6_print (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ip_print (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  tstr ; 

void
ipN_print(netdissect_options *ndo, register const u_char *bp, register u_int length)
{
	if (length < 1) {
		ND_PRINT((ndo, "truncated-ip %d", length));
		return;
	}

	ND_TCHECK(*bp);
	switch (*bp & 0xF0) {
	case 0x40:
		ip_print (ndo, bp, length);
		break;
	case 0x60:
		ip6_print (ndo, bp, length);
		break;
	default:
		ND_PRINT((ndo, "unknown ip %d", (*bp & 0xF0) >> 4));
		break;
	}
	return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return;
}