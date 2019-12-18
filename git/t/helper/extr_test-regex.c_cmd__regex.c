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
struct reg_flag {char* name; int flag; } ;
typedef  int /*<<< orphan*/  regmatch_t ;
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  git_setup_gettext () ; 
 struct reg_flag* reg_flags ; 
 scalar_t__ regcomp (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int test_regex_bug () ; 
 int /*<<< orphan*/  usage (char*) ; 

int cmd__regex(int argc, const char **argv)
{
	const char *pat;
	const char *str;
	int flags = 0;
	regex_t r;
	regmatch_t m[1];

	if (argc == 2 && !strcmp(argv[1], "--bug"))
		return test_regex_bug();
	else if (argc < 3)
		usage("test-tool regex --bug\n"
		      "test-tool regex <pattern> <string> [<options>]");

	argv++;
	pat = *argv++;
	str = *argv++;
	while (*argv) {
		struct reg_flag *rf;
		for (rf = reg_flags; rf->name; rf++)
			if (!strcmp(*argv, rf->name)) {
				flags |= rf->flag;
				break;
			}
		if (!rf->name)
			die("do not recognize %s", *argv);
		argv++;
	}
	git_setup_gettext();

	if (regcomp(&r, pat, flags))
		die("failed regcomp() for pattern '%s'", pat);
	if (regexec(&r, str, 1, m, 0))
		return 1;

	return 0;
}