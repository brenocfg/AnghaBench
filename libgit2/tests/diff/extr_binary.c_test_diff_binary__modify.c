#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;

/* Variables and functions */
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_SHOW_BINARY ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  test_patch (char*,char*,TYPE_1__*,char const*) ; 

void test_diff_binary__modify(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	const char *expected =
		"diff --git a/binary.bin b/binary.bin\n" \
		"index bd474b2519cc15eab801ff851cc7d50f0dee49a1..9ac35ff15cd8864aeafd889e4826a3150f0b06c4 100644\n" \
		"GIT binary patch\n" \
		"literal 5\n" \
		"Mc${NkU}WL~000&M4gdfE\n" \
		"\n" \
		"literal 3\n" \
		"Kc${Nk-~s>u4FC%O\n" \
		"\n";

	opts.flags = GIT_DIFF_SHOW_BINARY;

	repo = cl_git_sandbox_init("diff_format_email");
	test_patch(
		"897d3af16ca9e420cd071b1c4541bd2b91d04c8c",
		"8d7523f6fcb2404257889abe0d96f093d9f524f9",
		&opts,
		expected);
}