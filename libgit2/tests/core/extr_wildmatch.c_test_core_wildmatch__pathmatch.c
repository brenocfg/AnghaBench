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

void test_core_wildmatch__pathmatch(void)
{
	assert_matches("foo", "fo", 0, 0, 0, 0);
	assert_matches("foo/bar", "foo/bar", 1, 1, 1, 1);
	assert_matches("foo/bar", "foo/*", 1, 1, 1, 1);
	assert_matches("foo/bba/arr", "foo/*", 0, 0, 1, 1);
	assert_matches("foo/bba/arr", "foo/**", 1, 1, 1, 1);
	assert_matches("foo/bba/arr", "foo*", 0, 0, 1, 1);
	assert_matches("foo/bba/arr", "foo**", 0, 0, 1, 1);
	assert_matches("foo/bba/arr", "foo/*arr", 0, 0, 1, 1);
	assert_matches("foo/bba/arr", "foo/**arr", 0, 0, 1, 1);
	assert_matches("foo/bba/arr", "foo/*z", 0, 0, 0, 0);
	assert_matches("foo/bba/arr", "foo/**z", 0, 0, 0, 0);
	assert_matches("foo/bar", "foo?bar", 0, 0, 1, 1);
	assert_matches("foo/bar", "foo[/]bar", 0, 0, 1, 1);
	assert_matches("foo/bar", "foo[^a-z]bar", 0, 0, 1, 1);
	assert_matches("ab/cXd/efXg/hi", "*Xg*i", 0, 0, 1, 1);
}