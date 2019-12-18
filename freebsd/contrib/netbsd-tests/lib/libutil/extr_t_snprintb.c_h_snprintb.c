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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_STREQ (char const*,char*) ; 
 int snprintb (char*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
h_snprintb(const char *fmt, uint64_t val, const char *res)
{
	char buf[1024];
	int len, slen;

	len = snprintb(buf, sizeof(buf), fmt, val);
	slen = (int) strlen(res);

	ATF_REQUIRE_STREQ(res, buf);
	ATF_REQUIRE_EQ(len, slen);
}