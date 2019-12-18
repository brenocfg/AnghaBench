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
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_regexp_compile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regex ; 
 int /*<<< orphan*/  try_set_locale (int /*<<< orphan*/ ) ; 

void test_core_regexp__compile_ignores_global_locale_ctype(void)
{
	try_set_locale(LC_CTYPE);
	cl_git_pass(git_regexp_compile(&regex, "[\xc0-\xff][\x80-\xbf]", 0));
}