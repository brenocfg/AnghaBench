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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK_16BITS (int const*) ; 
 int /*<<< orphan*/  rawprint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const u_char *
ikev1_attr_print(netdissect_options *ndo, const u_char *p, const u_char *ep2)
{
	int totlen;
	uint32_t t;

	ND_TCHECK(p[0]);
	if (p[0] & 0x80)
		totlen = 4;
	else {
		ND_TCHECK_16BITS(&p[2]);
		totlen = 4 + EXTRACT_16BITS(&p[2]);
	}
	if (ep2 < p + totlen) {
		ND_PRINT((ndo,"[|attr]"));
		return ep2 + 1;
	}

	ND_TCHECK_16BITS(&p[0]);
	ND_PRINT((ndo,"("));
	t = EXTRACT_16BITS(&p[0]) & 0x7fff;
	ND_PRINT((ndo,"type=#%d ", t));
	if (p[0] & 0x80) {
		ND_PRINT((ndo,"value="));
		t = p[2];
		if (!rawprint(ndo, (const uint8_t *)&p[2], 2)) {
			ND_PRINT((ndo,")"));
			goto trunc;
		}
	} else {
		ND_PRINT((ndo,"len=%d value=", totlen - 4));
		if (!rawprint(ndo, (const uint8_t *)&p[4], totlen - 4)) {
			ND_PRINT((ndo,")"));
			goto trunc;
		}
	}
	ND_PRINT((ndo,")"));
	return p + totlen;

trunc:
	return NULL;
}