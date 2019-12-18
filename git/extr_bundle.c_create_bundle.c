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
struct rev_info {int /*<<< orphan*/  pending; } ;
struct repository {int dummy; } ;
struct lock_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct lock_file LOCK_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bundle_signature ; 
 scalar_t__ commit_lock_file (struct lock_file*) ; 
 scalar_t__ compute_and_write_prerequisites (int,struct rev_info*,int,char const**) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int hold_lock_file_for_update (struct lock_file*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  object_array_remove_duplicates (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rollback_lock_file (struct lock_file*) ; 
 scalar_t__ save_commit_buffer ; 
 int setup_revisions (int,char const**,struct rev_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int write_bundle_refs (int,struct rev_info*) ; 
 int /*<<< orphan*/  write_or_die (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_pack_data (int,struct rev_info*) ; 

int create_bundle(struct repository *r, const char *path,
		  int argc, const char **argv)
{
	struct lock_file lock = LOCK_INIT;
	int bundle_fd = -1;
	int bundle_to_stdout;
	int ref_count = 0;
	struct rev_info revs;

	bundle_to_stdout = !strcmp(path, "-");
	if (bundle_to_stdout)
		bundle_fd = 1;
	else
		bundle_fd = hold_lock_file_for_update(&lock, path,
						      LOCK_DIE_ON_ERROR);

	/* write signature */
	write_or_die(bundle_fd, bundle_signature, strlen(bundle_signature));

	/* init revs to list objects for pack-objects later */
	save_commit_buffer = 0;
	repo_init_revisions(r, &revs, NULL);

	/* write prerequisites */
	if (compute_and_write_prerequisites(bundle_fd, &revs, argc, argv))
		goto err;

	argc = setup_revisions(argc, argv, &revs, NULL);

	if (argc > 1) {
		error(_("unrecognized argument: %s"), argv[1]);
		goto err;
	}

	object_array_remove_duplicates(&revs.pending);

	ref_count = write_bundle_refs(bundle_fd, &revs);
	if (!ref_count)
		die(_("Refusing to create empty bundle."));
	else if (ref_count < 0)
		goto err;

	/* write pack */
	if (write_pack_data(bundle_fd, &revs))
		goto err;

	if (!bundle_to_stdout) {
		if (commit_lock_file(&lock))
			die_errno(_("cannot create '%s'"), path);
	}
	return 0;
err:
	rollback_lock_file(&lock);
	return -1;
}