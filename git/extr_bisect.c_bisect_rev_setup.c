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
struct rev_info {int /*<<< orphan*/  commit_format; scalar_t__ abbrev; } ;
struct repository {int dummy; } ;
struct argv_array {int /*<<< orphan*/  argv; int /*<<< orphan*/  argc; } ;
struct TYPE_2__ {int nr; scalar_t__ oid; } ;

/* Variables and functions */
 struct argv_array ARGV_ARRAY_INIT ; 
 int /*<<< orphan*/  CMIT_FMT_UNSPECIFIED ; 
 int /*<<< orphan*/  argv_array_push (struct argv_array*,char*) ; 
 int /*<<< orphan*/  argv_array_pushf (struct argv_array*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ current_bad_oid ; 
 TYPE_1__ good_revs ; 
 int /*<<< orphan*/  oid_to_hex (scalar_t__) ; 
 int /*<<< orphan*/  read_bisect_paths (struct argv_array*) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,char const*) ; 
 int /*<<< orphan*/  setup_revisions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bisect_rev_setup(struct repository *r, struct rev_info *revs,
			     const char *prefix,
			     const char *bad_format, const char *good_format,
			     int read_paths)
{
	struct argv_array rev_argv = ARGV_ARRAY_INIT;
	int i;

	repo_init_revisions(r, revs, prefix);
	revs->abbrev = 0;
	revs->commit_format = CMIT_FMT_UNSPECIFIED;

	/* rev_argv.argv[0] will be ignored by setup_revisions */
	argv_array_push(&rev_argv, "bisect_rev_setup");
	argv_array_pushf(&rev_argv, bad_format, oid_to_hex(current_bad_oid));
	for (i = 0; i < good_revs.nr; i++)
		argv_array_pushf(&rev_argv, good_format,
				 oid_to_hex(good_revs.oid + i));
	argv_array_push(&rev_argv, "--");
	if (read_paths)
		read_bisect_paths(&rev_argv);

	setup_revisions(rev_argv.argc, rev_argv.argv, revs, NULL);
	/* XXX leak rev_argv, as "revs" may still be pointing to it */
}