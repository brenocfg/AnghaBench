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
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  unsigned int int32_t ;

/* Variables and functions */
 unsigned int INT32_MIN ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsigned_relts_print (int /*<<< orphan*/ *,unsigned int) ; 

void
signed_relts_print(netdissect_options *ndo,
                   int32_t secs)
{
	if (secs < 0) {
		ND_PRINT((ndo, "-"));
		if (secs == INT32_MIN) {
			/*
			 * -2^31; you can't fit its absolute value into
			 * a 32-bit signed integer.
			 *
			 * Just directly pass said absolute value to
			 * unsigned_relts_print() directly.
			 *
			 * (XXX - does ISO C guarantee that -(-2^n),
			 * when calculated and cast to an n-bit unsigned
			 * integer type, will have the value 2^n?)
			 */
			unsigned_relts_print(ndo, 2147483648U);
		} else {
			/*
			 * We now know -secs will fit into an int32_t;
			 * negate it and pass that to unsigned_relts_print().
			 */
			unsigned_relts_print(ndo, -secs);
		}
		return;
	}
	unsigned_relts_print(ndo, secs);
}