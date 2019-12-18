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
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_lladdr(netdissect_options *ndo, const uint8_t *p, size_t l)
{
	const uint8_t *ep, *q;

	q = p;
	ep = p + l;
	while (l > 0 && q < ep) {
		if (q > p)
                        ND_PRINT((ndo,":"));
		ND_PRINT((ndo,"%02x", *q++));
		l--;
	}
}