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
struct TYPE_4__ {int /*<<< orphan*/  words; int /*<<< orphan*/  flags; int /*<<< orphan*/  fns; } ;
typedef  TYPE_1__ git_diff_driver_definition ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* builtin_defs ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_compile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regex ; 

void test_core_regexp__compile_userdiff_regexps(void)
{
	size_t idx;

	for (idx = 0; idx < ARRAY_SIZE(builtin_defs); ++idx) {
		git_diff_driver_definition ddef = builtin_defs[idx];

		cl_git_pass(git_regexp_compile(&regex, ddef.fns, ddef.flags));
		git_regexp_dispose(&regex);

		cl_git_pass(git_regexp_compile(&regex, ddef.words, 0));
		git_regexp_dispose(&regex);
	}
}