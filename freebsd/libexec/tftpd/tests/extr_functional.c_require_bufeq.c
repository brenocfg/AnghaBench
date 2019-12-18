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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (char const,char const,char*,char const,size_t,...) ; 

__attribute__((used)) static void
require_bufeq(const char *expected, ssize_t expected_len, const char *actual,
    ssize_t len)
{
	ssize_t i;

	ATF_REQUIRE_EQ_MSG(expected_len, len,
	    "Expected %zd bytes but got %zd", expected_len, len);
	for (i = 0; i < len; i++) {
		ATF_REQUIRE_EQ_MSG(actual[i], expected[i],
		    "Expected %#hhx at position %zd; got %hhx instead",
		    expected[i], i, actual[i]);
	}
}