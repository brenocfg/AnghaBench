#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct repository {int dummy; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr; } ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ check_ancestors (struct repository*,int,struct commit**,char const*) ; 
 int /*<<< orphan*/  check_merge_bases (int,struct commit**,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  current_bad_oid ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct commit** get_bad_and_good_commits (struct repository*,int*) ; 
 char* git_pathdup (char*) ; 
 TYPE_1__ good_revs ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  term_bad ; 
 int /*<<< orphan*/  warning_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void check_good_are_ancestors_of_bad(struct repository *r,
					    const char *prefix,
					    int no_checkout)
{
	char *filename = git_pathdup("BISECT_ANCESTORS_OK");
	struct stat st;
	int fd, rev_nr;
	struct commit **rev;

	if (!current_bad_oid)
		die(_("a %s revision is needed"), term_bad);

	/* Check if file BISECT_ANCESTORS_OK exists. */
	if (!stat(filename, &st) && S_ISREG(st.st_mode))
		goto done;

	/* Bisecting with no good rev is ok. */
	if (good_revs.nr == 0)
		goto done;

	/* Check if all good revs are ancestor of the bad rev. */
	rev = get_bad_and_good_commits(r, &rev_nr);
	if (check_ancestors(r, rev_nr, rev, prefix))
		check_merge_bases(rev_nr, rev, no_checkout);
	free(rev);

	/* Create file BISECT_ANCESTORS_OK. */
	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0600);
	if (fd < 0)
		warning_errno(_("could not create file '%s'"),
			      filename);
	else
		close(fd);
 done:
	free(filename);
}