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
struct option {char** value; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT_NO_DATE ; 
 int /*<<< orphan*/  free (char*) ; 
 char const* git_committer_info (int /*<<< orphan*/ ) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static int from_callback(const struct option *opt, const char *arg, int unset)
{
	char **from = opt->value;

	free(*from);

	if (unset)
		*from = NULL;
	else if (arg)
		*from = xstrdup(arg);
	else
		*from = xstrdup(git_committer_info(IDENT_NO_DATE));
	return 0;
}