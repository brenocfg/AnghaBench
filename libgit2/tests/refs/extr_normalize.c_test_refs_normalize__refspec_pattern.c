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
 int /*<<< orphan*/  GIT_REFERENCE_FORMAT_REFSPEC_PATTERN ; 
 int /*<<< orphan*/  ONE_LEVEL_AND_REFSPEC ; 
 int /*<<< orphan*/  ensure_refname_invalid (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ensure_refname_normalized (int /*<<< orphan*/ ,char*,char*) ; 

void test_refs_normalize__refspec_pattern(void)
{
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "heads/*foo/bar", "heads/*foo/bar");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "heads/foo*/bar", "heads/foo*/bar");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "heads/f*o/bar", "heads/f*o/bar");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "foo");
	ensure_refname_normalized(
		ONE_LEVEL_AND_REFSPEC, "FOO", "FOO");

	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "foo/bar", "foo/bar");
	ensure_refname_normalized(
		ONE_LEVEL_AND_REFSPEC, "foo/bar", "foo/bar");

	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "*/foo", "*/foo");
	ensure_refname_normalized(
		ONE_LEVEL_AND_REFSPEC, "*/foo", "*/foo");

	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "foo/*/bar", "foo/*/bar");
	ensure_refname_normalized(
		ONE_LEVEL_AND_REFSPEC, "foo/*/bar", "foo/*/bar");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "*");
	ensure_refname_normalized(
		ONE_LEVEL_AND_REFSPEC, "*", "*");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "foo/*/*");
	ensure_refname_invalid(
		ONE_LEVEL_AND_REFSPEC, "foo/*/*");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "*/foo/*");
	ensure_refname_invalid(
		ONE_LEVEL_AND_REFSPEC, "*/foo/*");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_REFSPEC_PATTERN, "*/*/foo");
	ensure_refname_invalid(
		ONE_LEVEL_AND_REFSPEC, "*/*/foo");
}