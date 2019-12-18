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
typedef  int /*<<< orphan*/  uint128_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK_MSG (int /*<<< orphan*/ ,char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  formatu128 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uint128_equals (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
u128_check_equality(uint128_t a, uint128_t b, const char *descr)
{
	char fmtbufa[52], fmtbufb[52];

	formatu128(fmtbufa, a);
	formatu128(fmtbufb, b);

	ATF_CHECK_MSG(uint128_equals(a, b),
	    "Expected: [%s] != Actual: [%s]: %s", fmtbufa, fmtbufb, descr);
}