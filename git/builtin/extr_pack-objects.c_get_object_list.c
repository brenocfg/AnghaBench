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
struct setup_revision_opt {int allow_exclude_promisor_objects; } ;
struct rev_info {int ignore_missing_links; } ;
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  line ;

/* Variables and functions */
 int /*<<< orphan*/  REVARG_CANNOT_BE_FILENAME ; 
 int UNINTERESTING ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_objects_in_unpacked_packs () ; 
 int /*<<< orphan*/  add_unreachable_loose_objects () ; 
 scalar_t__ add_unseen_recent_objects_to_traversal (struct rev_info*,scalar_t__) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filter_options ; 
 scalar_t__ fn_show_object ; 
 int /*<<< orphan*/  get_object_list_from_bitmap (struct rev_info*) ; 
 scalar_t__ get_oid_hex (char*,struct object_id*) ; 
 scalar_t__ handle_revision_arg (char*,struct rev_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_repository_shallow (int /*<<< orphan*/ ) ; 
 scalar_t__ keep_unreachable ; 
 int /*<<< orphan*/  load_delta_islands (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loosen_unused_packed_objects () ; 
 int /*<<< orphan*/  mark_edges_uninteresting (struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_array_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ pack_loose_unreachable ; 
 scalar_t__ prepare_revision_walk (struct rev_info*) ; 
 int /*<<< orphan*/  progress ; 
 int /*<<< orphan*/  recent_objects ; 
 int /*<<< orphan*/  record_recent_commit ; 
 int /*<<< orphan*/  record_recent_object ; 
 int /*<<< orphan*/  register_shallow (int /*<<< orphan*/ ,struct object_id*) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 
 scalar_t__ save_commit_buffer ; 
 int /*<<< orphan*/  setup_revisions (int,char const**,struct rev_info*,struct setup_revision_opt*) ; 
 int /*<<< orphan*/  show_commit ; 
 int /*<<< orphan*/  show_edge ; 
 scalar_t__ show_object ; 
 int /*<<< orphan*/  sparse ; 
 scalar_t__ starts_with (char*,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  traverse_commit_list (struct rev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  traverse_commit_list_filtered (int /*<<< orphan*/ *,struct rev_info*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unpack_unreachable ; 
 scalar_t__ unpack_unreachable_expiration ; 
 scalar_t__ use_bitmap_index ; 
 scalar_t__ use_delta_islands ; 
 int warn_on_object_refname_ambiguity ; 
 scalar_t__ write_bitmap_index ; 

__attribute__((used)) static void get_object_list(int ac, const char **av)
{
	struct rev_info revs;
	struct setup_revision_opt s_r_opt = {
		.allow_exclude_promisor_objects = 1,
	};
	char line[1000];
	int flags = 0;
	int save_warning;

	repo_init_revisions(the_repository, &revs, NULL);
	save_commit_buffer = 0;
	setup_revisions(ac, av, &revs, &s_r_opt);

	/* make sure shallows are read */
	is_repository_shallow(the_repository);

	save_warning = warn_on_object_refname_ambiguity;
	warn_on_object_refname_ambiguity = 0;

	while (fgets(line, sizeof(line), stdin) != NULL) {
		int len = strlen(line);
		if (len && line[len - 1] == '\n')
			line[--len] = 0;
		if (!len)
			break;
		if (*line == '-') {
			if (!strcmp(line, "--not")) {
				flags ^= UNINTERESTING;
				write_bitmap_index = 0;
				continue;
			}
			if (starts_with(line, "--shallow ")) {
				struct object_id oid;
				if (get_oid_hex(line + 10, &oid))
					die("not an SHA-1 '%s'", line + 10);
				register_shallow(the_repository, &oid);
				use_bitmap_index = 0;
				continue;
			}
			die(_("not a rev '%s'"), line);
		}
		if (handle_revision_arg(line, &revs, flags, REVARG_CANNOT_BE_FILENAME))
			die(_("bad revision '%s'"), line);
	}

	warn_on_object_refname_ambiguity = save_warning;

	if (use_bitmap_index && !get_object_list_from_bitmap(&revs))
		return;

	if (use_delta_islands)
		load_delta_islands(the_repository, progress);

	if (prepare_revision_walk(&revs))
		die(_("revision walk setup failed"));
	mark_edges_uninteresting(&revs, show_edge, sparse);

	if (!fn_show_object)
		fn_show_object = show_object;
	traverse_commit_list_filtered(&filter_options, &revs,
				      show_commit, fn_show_object, NULL,
				      NULL);

	if (unpack_unreachable_expiration) {
		revs.ignore_missing_links = 1;
		if (add_unseen_recent_objects_to_traversal(&revs,
				unpack_unreachable_expiration))
			die(_("unable to add recent objects"));
		if (prepare_revision_walk(&revs))
			die(_("revision walk setup failed"));
		traverse_commit_list(&revs, record_recent_commit,
				     record_recent_object, NULL);
	}

	if (keep_unreachable)
		add_objects_in_unpacked_packs();
	if (pack_loose_unreachable)
		add_unreachable_loose_objects();
	if (unpack_unreachable)
		loosen_unused_packed_objects();

	oid_array_clear(&recent_objects);
}