#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct progress {int dummy; } ;
struct packed_git {scalar_t__ num_objects; struct packed_git* next; } ;
struct object_id {int dummy; } ;
struct object_directory {char* path; struct object_directory* next; } ;
struct object {int flags; } ;
struct decoration {int dummy; } ;
struct child_process {char const** argv; int git_cmd; } ;
struct blob {struct object object; } ;
struct TYPE_16__ {int strict; int /*<<< orphan*/  error_func; int /*<<< orphan*/  walk; } ;
struct TYPE_15__ {int /*<<< orphan*/  object_names; int /*<<< orphan*/  walk; } ;
struct TYPE_14__ {TYPE_1__* objects; } ;
struct TYPE_13__ {struct object_directory* odb; } ;
struct TYPE_12__ {unsigned int ce_mode; int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 struct child_process CHILD_PROCESS_INIT ; 
 int ERROR_COMMIT_GRAPH ; 
 int ERROR_OBJECT ; 
 int ERROR_PACK ; 
 int HAS_OBJ ; 
 scalar_t__ S_ISGITLINK (unsigned int) ; 
 int USED ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_11__** active_cache ; 
 scalar_t__ active_cache_tree ; 
 int active_nr ; 
 int /*<<< orphan*/  add_decoration (int /*<<< orphan*/ ,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_connectivity () ; 
 int check_full ; 
 scalar_t__ check_strict ; 
 int /*<<< orphan*/  child_process_init (struct child_process*) ; 
 scalar_t__ connectivity_only ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char const*) ; 
 int errors_found ; 
 scalar_t__ fetch_if_missing ; 
 int /*<<< orphan*/  for_each_loose_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_each_packed_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsck_cache_tree (scalar_t__) ; 
 int /*<<< orphan*/  fsck_config ; 
 int /*<<< orphan*/  fsck_error_func ; 
 scalar_t__ fsck_finish (TYPE_9__*) ; 
 int /*<<< orphan*/  fsck_obj_buffer ; 
 TYPE_9__ fsck_obj_options ; 
 int /*<<< orphan*/  fsck_object_dir (char*) ; 
 int /*<<< orphan*/  fsck_opts ; 
 int /*<<< orphan*/  fsck_usage ; 
 TYPE_8__ fsck_walk_options ; 
 struct packed_git* get_all_packs (TYPE_2__*) ; 
 int /*<<< orphan*/  get_default_heads () ; 
 int /*<<< orphan*/  get_oid (char const*,struct object_id*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (char*,int*) ; 
 scalar_t__ include_reflogs ; 
 scalar_t__ is_promisor_object (struct object_id*) ; 
 int isatty (int) ; 
 int keep_cache_objects ; 
 struct blob* lookup_blob (TYPE_2__*,int /*<<< orphan*/ *) ; 
 struct object* lookup_object (TYPE_2__*,struct object_id*) ; 
 int /*<<< orphan*/  mark_loose_for_connectivity ; 
 int /*<<< orphan*/  mark_object ; 
 int /*<<< orphan*/  mark_object_reachable (struct object*) ; 
 int /*<<< orphan*/  mark_packed_for_connectivity ; 
 int /*<<< orphan*/  mark_used ; 
 scalar_t__ name_objects ; 
 char const* oid_to_hex (struct object_id*) ; 
 scalar_t__ open_pack_index (struct packed_git*) ; 
 int parse_options (int,char const**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prepare_alt_odb (TYPE_2__*) ; 
 int /*<<< orphan*/  read_cache () ; 
 scalar_t__ read_replace_refs ; 
 scalar_t__ run_command (struct child_process*) ; 
 int show_progress ; 
 struct progress* start_progress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_progress (struct progress**) ; 
 TYPE_2__* the_repository ; 
 scalar_t__ verbose ; 
 int verify_ce_order ; 
 int verify_index_checksum ; 
 scalar_t__ verify_pack (TYPE_2__*,struct packed_git*,int /*<<< orphan*/ ,struct progress*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_lost_and_found ; 
 int /*<<< orphan*/  xcalloc (int,int) ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrfmt (char*,int /*<<< orphan*/ ) ; 

int cmd_fsck(int argc, const char **argv, const char *prefix)
{
	int i;
	struct object_directory *odb;

	/* fsck knows how to handle missing promisor objects */
	fetch_if_missing = 0;

	errors_found = 0;
	read_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, fsck_opts, fsck_usage, 0);

	fsck_walk_options.walk = mark_object;
	fsck_obj_options.walk = mark_used;
	fsck_obj_options.error_func = fsck_error_func;
	if (check_strict)
		fsck_obj_options.strict = 1;

	if (show_progress == -1)
		show_progress = isatty(2);
	if (verbose)
		show_progress = 0;

	if (write_lost_and_found) {
		check_full = 1;
		include_reflogs = 0;
	}

	if (name_objects)
		fsck_walk_options.object_names =
			xcalloc(1, sizeof(struct decoration));

	git_config(fsck_config, NULL);

	if (connectivity_only) {
		for_each_loose_object(mark_loose_for_connectivity, NULL, 0);
		for_each_packed_object(mark_packed_for_connectivity, NULL, 0);
	} else {
		prepare_alt_odb(the_repository);
		for (odb = the_repository->objects->odb; odb; odb = odb->next)
			fsck_object_dir(odb->path);

		if (check_full) {
			struct packed_git *p;
			uint32_t total = 0, count = 0;
			struct progress *progress = NULL;

			if (show_progress) {
				for (p = get_all_packs(the_repository); p;
				     p = p->next) {
					if (open_pack_index(p))
						continue;
					total += p->num_objects;
				}

				progress = start_progress(_("Checking objects"), total);
			}
			for (p = get_all_packs(the_repository); p;
			     p = p->next) {
				/* verify gives error messages itself */
				if (verify_pack(the_repository,
						p, fsck_obj_buffer,
						progress, count))
					errors_found |= ERROR_PACK;
				count += p->num_objects;
			}
			stop_progress(&progress);
		}

		if (fsck_finish(&fsck_obj_options))
			errors_found |= ERROR_OBJECT;
	}

	for (i = 0; i < argc; i++) {
		const char *arg = argv[i];
		struct object_id oid;
		if (!get_oid(arg, &oid)) {
			struct object *obj = lookup_object(the_repository,
							   &oid);

			if (!obj || !(obj->flags & HAS_OBJ)) {
				if (is_promisor_object(&oid))
					continue;
				error(_("%s: object missing"), oid_to_hex(&oid));
				errors_found |= ERROR_OBJECT;
				continue;
			}

			obj->flags |= USED;
			if (name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj, xstrdup(arg));
			mark_object_reachable(obj);
			continue;
		}
		error(_("invalid parameter: expected sha1, got '%s'"), arg);
		errors_found |= ERROR_OBJECT;
	}

	/*
	 * If we've not been given any explicit head information, do the
	 * default ones from .git/refs. We also consider the index file
	 * in this case (ie this implies --cache).
	 */
	if (!argc) {
		get_default_heads();
		keep_cache_objects = 1;
	}

	if (keep_cache_objects) {
		verify_index_checksum = 1;
		verify_ce_order = 1;
		read_cache();
		for (i = 0; i < active_nr; i++) {
			unsigned int mode;
			struct blob *blob;
			struct object *obj;

			mode = active_cache[i]->ce_mode;
			if (S_ISGITLINK(mode))
				continue;
			blob = lookup_blob(the_repository,
					   &active_cache[i]->oid);
			if (!blob)
				continue;
			obj = &blob->object;
			obj->flags |= USED;
			if (name_objects)
				add_decoration(fsck_walk_options.object_names,
					obj,
					xstrfmt(":%s", active_cache[i]->name));
			mark_object_reachable(obj);
		}
		if (active_cache_tree)
			fsck_cache_tree(active_cache_tree);
	}

	check_connectivity();

	if (!git_config_get_bool("core.commitgraph", &i) && i) {
		struct child_process commit_graph_verify = CHILD_PROCESS_INIT;
		const char *verify_argv[] = { "commit-graph", "verify", NULL, NULL, NULL };

		prepare_alt_odb(the_repository);
		for (odb = the_repository->objects->odb; odb; odb = odb->next) {
			child_process_init(&commit_graph_verify);
			commit_graph_verify.argv = verify_argv;
			commit_graph_verify.git_cmd = 1;
			verify_argv[2] = "--object-dir";
			verify_argv[3] = odb->path;
			if (run_command(&commit_graph_verify))
				errors_found |= ERROR_COMMIT_GRAPH;
		}
	}

	if (!git_config_get_bool("core.multipackindex", &i) && i) {
		struct child_process midx_verify = CHILD_PROCESS_INIT;
		const char *midx_argv[] = { "multi-pack-index", "verify", NULL, NULL, NULL };

		prepare_alt_odb(the_repository);
		for (odb = the_repository->objects->odb; odb; odb = odb->next) {
			child_process_init(&midx_verify);
			midx_verify.argv = midx_argv;
			midx_verify.git_cmd = 1;
			midx_argv[2] = "--object-dir";
			midx_argv[3] = odb->path;
			if (run_command(&midx_verify))
				errors_found |= ERROR_COMMIT_GRAPH;
		}
	}

	return errors_found;
}