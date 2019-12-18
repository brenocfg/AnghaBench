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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rawprint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int ike_show_somedata(netdissect_options *ndo,
			     const u_char *cp, const u_char *ep)
{
	/* there is too much data, just show some of it */
	const u_char *end = ep - 20;
	int  elen = 20;
	int   len = ep - cp;
	if(len > 10) {
		len = 10;
	}

	/* really shouldn't happen because of above */
	if(end < cp + len) {
		end = cp+len;
		elen = ep - end;
	}

	ND_PRINT((ndo," data=("));
	if(!rawprint(ndo, (const uint8_t *)(cp), len)) goto trunc;
	ND_PRINT((ndo, "..."));
	if(elen) {
		if(!rawprint(ndo, (const uint8_t *)(end), elen)) goto trunc;
	}
	ND_PRINT((ndo,")"));
	return 1;

trunc:
	return 0;
}