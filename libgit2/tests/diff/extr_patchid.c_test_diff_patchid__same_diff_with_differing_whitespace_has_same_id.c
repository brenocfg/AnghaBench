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
 int /*<<< orphan*/  verify_patch_id (char const*,char const*) ; 

void test_diff_patchid__same_diff_with_differing_whitespace_has_same_id(void)
{
	const char *tabs =
	    "diff --git a/file.txt b/file.txt\n"
	    "index 8fecc09..1d43a92 100644\n"
	    "--- a/file.txt\n"
	    "+++ b/file.txt\n"
	    "@@ -1 +1 @@\n"
	    "-old text\n"
	    "+		new text\n";
	const char *spaces =
	    "diff --git a/file.txt b/file.txt\n"
	    "index 8fecc09..1d43a92 100644\n"
	    "--- a/file.txt\n"
	    "+++ b/file.txt\n"
	    "@@ -1 +1 @@\n"
	    "-old text\n"
	    "+        new text\n";
	const char *id = "11efdd13c30f7a1056eac2ae2fb952da475e2c23";

	verify_patch_id(tabs, id);
	verify_patch_id(spaces, id);
}