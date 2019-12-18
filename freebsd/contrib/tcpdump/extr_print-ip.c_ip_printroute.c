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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
ip_printroute(netdissect_options *ndo,
              register const u_char *cp, u_int length)
{
	register u_int ptr;
	register u_int len;

	if (length < 3) {
		ND_PRINT((ndo, " [bad length %u]", length));
		return (0);
	}
	if ((length + 1) & 3)
		ND_PRINT((ndo, " [bad length %u]", length));
	ND_TCHECK(cp[2]);
	ptr = cp[2] - 1;
	if (ptr < 3 || ((ptr + 1) & 3) || ptr > length + 1)
		ND_PRINT((ndo, " [bad ptr %u]", cp[2]));

	for (len = 3; len < length; len += 4) {
		ND_TCHECK2(cp[len], 4);
		ND_PRINT((ndo, " %s", ipaddr_string(ndo, &cp[len])));
		if (ptr > len)
			ND_PRINT((ndo, ","));
	}
	return (0);

trunc:
	return (-1);
}