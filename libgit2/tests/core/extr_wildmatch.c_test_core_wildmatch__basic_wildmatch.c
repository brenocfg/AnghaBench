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
 int /*<<< orphan*/  assert_matches (char*,char*,int,int,int,int) ; 

void test_core_wildmatch__basic_wildmatch(void)
{
	assert_matches("foo", "foo", 1, 1, 1, 1);
	assert_matches("foo", "bar", 0, 0, 0, 0);
	assert_matches("", "", 1, 1, 1, 1);
	assert_matches("foo", "???", 1, 1, 1, 1);
	assert_matches("foo", "??", 0, 0, 0, 0);
	assert_matches("foo", "*", 1, 1, 1, 1);
	assert_matches("foo", "f*", 1, 1, 1, 1);
	assert_matches("foo", "*f", 0, 0, 0, 0);
	assert_matches("foo", "*foo*", 1, 1, 1, 1);
	assert_matches("foobar", "*ob*a*r*", 1, 1, 1, 1);
	assert_matches("aaaaaaabababab", "*ab", 1, 1, 1, 1);
	assert_matches("foo*", "foo\\*", 1, 1, 1, 1);
	assert_matches("foobar", "foo\\*bar", 0, 0, 0, 0);
	assert_matches("f\\oo", "f\\\\oo", 1, 1, 1, 1);
	assert_matches("ball", "*[al]?", 1, 1, 1, 1);
	assert_matches("ten", "[ten]", 0, 0, 0, 0);
	assert_matches("ten", "**[!te]", 1, 1, 1, 1);
	assert_matches("ten", "**[!ten]", 0, 0, 0, 0);
	assert_matches("ten", "t[a-g]n", 1, 1, 1, 1);
	assert_matches("ten", "t[!a-g]n", 0, 0, 0, 0);
	assert_matches("ton", "t[!a-g]n", 1, 1, 1, 1);
	assert_matches("ton", "t[^a-g]n", 1, 1, 1, 1);
	assert_matches("a]b", "a[]]b", 1, 1, 1, 1);
	assert_matches("a-b", "a[]-]b", 1, 1, 1, 1);
	assert_matches("a]b", "a[]-]b", 1, 1, 1, 1);
	assert_matches("aab", "a[]-]b", 0, 0, 0, 0);
	assert_matches("aab", "a[]a-]b", 1, 1, 1, 1);
	assert_matches("]", "]", 1, 1, 1, 1);
}