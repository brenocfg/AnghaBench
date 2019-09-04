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
typedef  int /*<<< orphan*/  regex_t ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  words; int /*<<< orphan*/  fns; } ;
typedef  TYPE_1__ git_diff_driver_definition ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int REG_EXTENDED ; 
 TYPE_1__* builtin_defs ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int p_regcomp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 

void test_core_posix__p_regcomp_compile_userdiff_regexps(void)
{
	size_t idx;

	for (idx = 0; idx < ARRAY_SIZE(builtin_defs); ++idx) {
		git_diff_driver_definition ddef = builtin_defs[idx];
		int error = 0;
		regex_t preg;

		error = p_regcomp(&preg, ddef.fns, REG_EXTENDED | ddef.flags);
		regfree(&preg);
		cl_must_pass(error);

		error = p_regcomp(&preg, ddef.words, REG_EXTENDED);
		regfree(&preg);
		cl_must_pass(error);
	}
}