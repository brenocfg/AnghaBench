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
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
print_neighbors(netdissect_options *ndo,
                register const u_char *bp, register const u_char *ep,
                register u_int len)
{
	const u_char *laddr;
	register u_char metric;
	register u_char thresh;
	register int ncount;

	while (len > 0 && bp < ep) {
		ND_TCHECK2(bp[0], 7);
		laddr = bp;
		bp += 4;
		metric = *bp++;
		thresh = *bp++;
		ncount = *bp++;
		len -= 7;
		while (--ncount >= 0) {
			ND_TCHECK2(bp[0], 4);
			ND_PRINT((ndo, " [%s ->", ipaddr_string(ndo, laddr)));
			ND_PRINT((ndo, " %s, (%d/%d)]",
				   ipaddr_string(ndo, bp), metric, thresh));
			bp += 4;
			len -= 4;
		}
	}
	return (0);
trunc:
	return (-1);
}