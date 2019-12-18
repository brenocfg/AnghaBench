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
typedef  int u_char ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
atp_bitmap_print(netdissect_options *ndo,
                 register u_char bm)
{
	register char c;
	register int i;

	/*
	 * The '& 0xff' below is needed for compilers that want to sign
	 * extend a u_char, which is the case with the Ultrix compiler.
	 * (gcc is smart enough to eliminate it, at least on the Sparc).
	 */
	if ((bm + 1) & (bm & 0xff)) {
		c = '<';
		for (i = 0; bm; ++i) {
			if (bm & 1) {
				ND_PRINT((ndo, "%c%d", c, i));
				c = ',';
			}
			bm >>= 1;
		}
		ND_PRINT((ndo, ">"));
	} else {
		for (i = 0; bm; ++i)
			bm >>= 1;
		if (i > 1)
			ND_PRINT((ndo, "<0-%d>", i - 1));
		else
			ND_PRINT((ndo, "<0>"));
	}
}