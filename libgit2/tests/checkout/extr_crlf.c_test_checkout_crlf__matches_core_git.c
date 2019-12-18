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
 int /*<<< orphan*/  empty_workdir (char*) ; 
 int /*<<< orphan*/  test_checkout (char const*,char const*) ; 

void test_checkout_crlf__matches_core_git(void)
{
	const char *autocrlf[] = { "true", "false", "input", NULL };
	const char *attrs[] = { "", "-crlf", "-text", "eol=crlf", "eol=lf",
		"text", "text eol=crlf", "text eol=lf",
		"text=auto", "text=auto eol=crlf", "text=auto eol=lf",
		NULL };
	const char **a, **b;

	for (a = autocrlf; *a; a++) {
		for (b = attrs; *b; b++) {
			empty_workdir("crlf");
			test_checkout(*a, *b);
		}
	}
}