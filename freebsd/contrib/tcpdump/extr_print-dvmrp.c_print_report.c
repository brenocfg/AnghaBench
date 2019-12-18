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
typedef  int uint32_t ;
typedef  int u_int ;
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  intoa (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
print_report(netdissect_options *ndo,
             register const u_char *bp, register const u_char *ep,
             register u_int len)
{
	register uint32_t mask, origin;
	register int metric, done;
	register u_int i, width;

	while (len > 0) {
		if (len < 3) {
			ND_PRINT((ndo, " [|]"));
			return (0);
		}
		ND_TCHECK2(bp[0], 3);
		mask = (uint32_t)0xff << 24 | bp[0] << 16 | bp[1] << 8 | bp[2];
		width = 1;
		if (bp[0])
			width = 2;
		if (bp[1])
			width = 3;
		if (bp[2])
			width = 4;

		ND_PRINT((ndo, "\n\tMask %s", intoa(htonl(mask))));
		bp += 3;
		len -= 3;
		do {
			if (bp + width + 1 > ep) {
				ND_PRINT((ndo, " [|]"));
				return (0);
			}
			if (len < width + 1) {
				ND_PRINT((ndo, "\n\t  [Truncated Report]"));
				return (0);
			}
			origin = 0;
			for (i = 0; i < width; ++i) {
				ND_TCHECK(*bp);
				origin = origin << 8 | *bp++;
			}
			for ( ; i < 4; ++i)
				origin <<= 8;

			ND_TCHECK(*bp);
			metric = *bp++;
			done = metric & 0x80;
			metric &= 0x7f;
			ND_PRINT((ndo, "\n\t  %s metric %d", intoa(htonl(origin)),
				metric));
			len -= width + 1;
		} while (!done);
	}
	return (0);
trunc:
	return (-1);
}