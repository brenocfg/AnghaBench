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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_term_format (char const*,char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int error_errno (int /*<<< orphan*/ ) ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  git_path_bisect_terms () ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

__attribute__((used)) static int write_terms(const char *bad, const char *good)
{
	FILE *fp = NULL;
	int res;

	if (!strcmp(bad, good))
		return error(_("please use two different terms"));

	if (check_term_format(bad, "bad") || check_term_format(good, "good"))
		return -1;

	fp = fopen(git_path_bisect_terms(), "w");
	if (!fp)
		return error_errno(_("could not open the file BISECT_TERMS"));

	res = fprintf(fp, "%s\n%s\n", bad, good);
	res |= fclose(fp);
	return (res < 0) ? -1 : 0;
}