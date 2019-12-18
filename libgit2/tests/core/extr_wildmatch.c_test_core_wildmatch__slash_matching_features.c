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

void test_core_wildmatch__slash_matching_features(void)
{
	assert_matches("foo/baz/bar", "foo*bar", 0, 0, 1, 1);
	assert_matches("foo/baz/bar", "foo**bar", 0, 0, 1, 1);
	assert_matches("foobazbar", "foo**bar", 1, 1, 1, 1);
	assert_matches("foo/baz/bar", "foo/**/bar", 1, 1, 1, 1);
	assert_matches("foo/baz/bar", "foo/**/**/bar", 1, 1, 0, 0);
	assert_matches("foo/b/a/z/bar", "foo/**/bar", 1, 1, 1, 1);
	assert_matches("foo/b/a/z/bar", "foo/**/**/bar", 1, 1, 1, 1);
	assert_matches("foo/bar", "foo/**/bar", 1, 1, 0, 0);
	assert_matches("foo/bar", "foo/**/**/bar", 1, 1, 0, 0);
	assert_matches("foo/bar", "foo?bar", 0, 0, 1, 1);
	assert_matches("foo/bar", "foo[/]bar", 0, 0, 1, 1);
	assert_matches("foo/bar", "foo[^a-z]bar", 0, 0, 1, 1);
	assert_matches("foo/bar", "f[^eiu][^eiu][^eiu][^eiu][^eiu]r", 0, 0, 1, 1);
	assert_matches("foo-bar", "f[^eiu][^eiu][^eiu][^eiu][^eiu]r", 1, 1, 1, 1);
	assert_matches("foo", "**/foo", 1, 1, 0, 0);
	assert_matches("XXX/foo", "**/foo", 1, 1, 1, 1);
	assert_matches("bar/baz/foo", "**/foo", 1, 1, 1, 1);
	assert_matches("bar/baz/foo", "*/foo", 0, 0, 1, 1);
	assert_matches("foo/bar/baz", "**/bar*", 0, 0, 1, 1);
	assert_matches("deep/foo/bar/baz", "**/bar/*", 1, 1, 1, 1);
	assert_matches("deep/foo/bar/baz/", "**/bar/*", 0, 0, 1, 1);
	assert_matches("deep/foo/bar/baz/", "**/bar/**", 1, 1, 1, 1);
	assert_matches("deep/foo/bar", "**/bar/*", 0, 0, 0, 0);
	assert_matches("deep/foo/bar/", "**/bar/**", 1, 1, 1, 1);
	assert_matches("foo/bar/baz", "**/bar**", 0, 0, 1, 1);
	assert_matches("foo/bar/baz/x", "*/bar/**", 1, 1, 1, 1);
	assert_matches("deep/foo/bar/baz/x", "*/bar/**", 0, 0, 1, 1);
	assert_matches("deep/foo/bar/baz/x", "**/bar/*/*", 1, 1, 1, 1);
}