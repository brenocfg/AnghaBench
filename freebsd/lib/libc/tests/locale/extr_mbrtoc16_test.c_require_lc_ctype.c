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

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  atf_tc_fail (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 char* setlocale (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static void
require_lc_ctype(const char *locale_name)
{
	char *lc_ctype_set;

	lc_ctype_set = setlocale(LC_CTYPE, locale_name);
	if (lc_ctype_set == NULL)
		atf_tc_fail("setlocale(LC_CTYPE, \"%s\") failed; errno=%d",
		    locale_name, errno);

	ATF_REQUIRE(strcmp(lc_ctype_set, locale_name) == 0);
}