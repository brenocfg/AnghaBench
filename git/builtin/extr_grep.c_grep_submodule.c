#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subopt ;
struct tree_desc {int dummy; } ;
struct submodule {int dummy; } ;
struct strbuf {int /*<<< orphan*/  len; } ;
struct repository {TYPE_2__* objects; } ;
struct pathspec {int dummy; } ;
struct object_id {int dummy; } ;
struct object {scalar_t__ type; struct object_id const oid; } ;
struct grep_opt {struct repository* repo; } ;
struct TYPE_4__ {TYPE_1__* odb; } ;
struct TYPE_3__ {int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ OBJ_COMMIT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_to_alternates_memory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 
 int grep_cache (struct grep_opt*,struct pathspec const*,int) ; 
 int /*<<< orphan*/  grep_read_lock () ; 
 int /*<<< orphan*/  grep_read_unlock () ; 
 int grep_tree (struct grep_opt*,struct pathspec const*,struct tree_desc*,struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,void*,unsigned long) ; 
 int /*<<< orphan*/  is_submodule_active (struct repository*,char const*) ; 
 int /*<<< orphan*/  memcpy (struct grep_opt*,struct grep_opt*,int) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 struct object* parse_object_or_die (struct object_id const*,int /*<<< orphan*/ ) ; 
 void* read_object_with_reference (struct repository*,struct object_id const*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo_clear (struct repository*) ; 
 int /*<<< orphan*/  repo_read_gitmodules (struct repository*) ; 
 scalar_t__ repo_submodule_init (struct repository*,struct repository*,struct submodule const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 struct submodule* submodule_from_path (struct repository*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  tree_type ; 

__attribute__((used)) static int grep_submodule(struct grep_opt *opt,
			  const struct pathspec *pathspec,
			  const struct object_id *oid,
			  const char *filename, const char *path, int cached)
{
	struct repository subrepo;
	struct repository *superproject = opt->repo;
	const struct submodule *sub = submodule_from_path(superproject,
							  &null_oid, path);
	struct grep_opt subopt;
	int hit;

	/*
	 * NEEDSWORK: submodules functions need to be protected because they
	 * access the object store via config_from_gitmodules(): the latter
	 * uses get_oid() which, for now, relies on the global the_repository
	 * object.
	 */
	grep_read_lock();

	if (!is_submodule_active(superproject, path)) {
		grep_read_unlock();
		return 0;
	}

	if (repo_submodule_init(&subrepo, superproject, sub)) {
		grep_read_unlock();
		return 0;
	}

	repo_read_gitmodules(&subrepo);

	/*
	 * NEEDSWORK: This adds the submodule's object directory to the list of
	 * alternates for the single in-memory object store.  This has some bad
	 * consequences for memory (processed objects will never be freed) and
	 * performance (this increases the number of pack files git has to pay
	 * attention to, to the sum of the number of pack files in all the
	 * repositories processed so far).  This can be removed once the object
	 * store is no longer global and instead is a member of the repository
	 * object.
	 */
	add_to_alternates_memory(subrepo.objects->odb->path);
	grep_read_unlock();

	memcpy(&subopt, opt, sizeof(subopt));
	subopt.repo = &subrepo;

	if (oid) {
		struct object *object;
		struct tree_desc tree;
		void *data;
		unsigned long size;
		struct strbuf base = STRBUF_INIT;

		object = parse_object_or_die(oid, oid_to_hex(oid));

		grep_read_lock();
		data = read_object_with_reference(&subrepo,
						  &object->oid, tree_type,
						  &size, NULL);
		grep_read_unlock();

		if (!data)
			die(_("unable to read tree (%s)"), oid_to_hex(&object->oid));

		strbuf_addstr(&base, filename);
		strbuf_addch(&base, '/');

		init_tree_desc(&tree, data, size);
		hit = grep_tree(&subopt, pathspec, &tree, &base, base.len,
				object->type == OBJ_COMMIT);
		strbuf_release(&base);
		free(data);
	} else {
		hit = grep_cache(&subopt, pathspec, cached);
	}

	repo_clear(&subrepo);
	return hit;
}