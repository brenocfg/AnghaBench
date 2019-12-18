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
struct tok {int const v; int /*<<< orphan*/ * s; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
of10_bitmap_print(netdissect_options *ndo,
                  const struct tok *t, const uint32_t v, const uint32_t u)
{
	const char *sep = " (";

	if (v == 0)
		return;
	/* assigned bits */
	for (; t->s != NULL; t++)
		if (v & t->v) {
			ND_PRINT((ndo, "%s%s", sep, t->s));
			sep = ", ";
		}
	/* unassigned bits? */
	ND_PRINT((ndo, v & u ? ") (bogus)" : ")"));
}