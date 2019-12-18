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
typedef  scalar_t__ iconv_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ICONV_TRIVIALP ; 
 int iconv_close (scalar_t__) ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int iconvctl (scalar_t__,int /*<<< orphan*/ ,int*) ; 

void
test_trivialp(const char *src, const char *dst, int expected)
{
	iconv_t ic;
	int actual, status;

	ic = iconv_open(dst, src);
	ATF_REQUIRE(ic != (iconv_t)-1);

	status = iconvctl(ic, ICONV_TRIVIALP, &actual);
	ATF_REQUIRE(status == 0);

	ATF_REQUIRE(actual == expected);

	status = iconv_close(ic);
	ATF_REQUIRE(status == 0);
}