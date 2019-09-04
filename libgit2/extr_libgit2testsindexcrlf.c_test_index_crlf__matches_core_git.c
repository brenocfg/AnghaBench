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
 int /*<<< orphan*/  set_up_workingdir (char*) ; 
 int /*<<< orphan*/  test_add_index (char const*,char const*,char const*) ; 

void test_index_crlf__matches_core_git(void)
{
	const char *safecrlf[] = { "true", "false", "warn", NULL };
	const char *autocrlf[] = { "true", "false", "input", NULL };
	const char *attrs[] = { "", "-crlf", "-text", "eol=crlf", "eol=lf",
		"text", "text eol=crlf", "text eol=lf",
		"text=auto", "text=auto eol=crlf", "text=auto eol=lf",
		NULL };
	const char **a, **b, **c;

	for (a = safecrlf; *a; a++) {
		for (b = autocrlf; *b; b++) {
			for (c = attrs; *c; c++) {
				set_up_workingdir("crlf");
				test_add_index(*a, *b, *c);
			}
		}
	}
}