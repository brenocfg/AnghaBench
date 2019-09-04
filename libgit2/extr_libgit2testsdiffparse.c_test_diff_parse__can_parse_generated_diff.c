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
 int GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED ; 
 int GIT_DIFF_FIND_EXACT_MATCH_ONLY ; 
 int GIT_DIFF_FIND_RENAMES ; 
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_DIFF_SHOW_BINARY ; 
 int /*<<< orphan*/  test_tree_to_tree_computed_to_parsed (char*,char*,char*,int /*<<< orphan*/ ,int) ; 

void test_diff_parse__can_parse_generated_diff(void)
{
	test_tree_to_tree_computed_to_parsed(
		"diff", "d70d245e", "7a9e0b02", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"unsymlinked.git", "806999", "a8595c", 0, 0);
	test_tree_to_tree_computed_to_parsed("diff",
		"d70d245ed97ed2aa596dd1af6536e4bfdb047b69",
		"7a9e0b02e63179929fed24f0a3e0f19168114d10", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"unsymlinked.git", "7fccd7", "806999", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"unsymlinked.git", "7fccd7", "a8595c", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"attr", "605812a", "370fe9ec22", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"attr", "f5b0af1fb4f5c", "370fe9ec22", 0, 0);
	test_tree_to_tree_computed_to_parsed(
		"diff", "d70d245e", "d70d245e", 0, 0);
	test_tree_to_tree_computed_to_parsed("diff_format_email",
		"873806f6f27e631eb0b23e4b56bea2bfac14a373",
		"897d3af16ca9e420cd071b1c4541bd2b91d04c8c",
		GIT_DIFF_SHOW_BINARY, 0);
	test_tree_to_tree_computed_to_parsed("diff_format_email",
		"897d3af16ca9e420cd071b1c4541bd2b91d04c8c",
		"873806f6f27e631eb0b23e4b56bea2bfac14a373",
		GIT_DIFF_SHOW_BINARY, 0);
	test_tree_to_tree_computed_to_parsed("renames",
		"31e47d8c1fa36d7f8d537b96158e3f024de0a9f2",
		"2bc7f351d20b53f1c72c16c4b036e491c478c49a",
		0, GIT_DIFF_FIND_RENAMES);
	test_tree_to_tree_computed_to_parsed("renames",
		"31e47d8c1fa36d7f8d537b96158e3f024de0a9f2",
		"2bc7f351d20b53f1c72c16c4b036e491c478c49a",
		GIT_DIFF_INCLUDE_UNMODIFIED,
		0);
	test_tree_to_tree_computed_to_parsed("renames",
		"31e47d8c1fa36d7f8d537b96158e3f024de0a9f2",
		"2bc7f351d20b53f1c72c16c4b036e491c478c49a",
		GIT_DIFF_INCLUDE_UNMODIFIED,
		GIT_DIFF_FIND_COPIES_FROM_UNMODIFIED | GIT_DIFF_FIND_EXACT_MATCH_ONLY);
}