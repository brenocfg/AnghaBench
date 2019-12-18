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
struct tree {int dummy; } ;
struct tag {TYPE_1__* tagged; int /*<<< orphan*/  tag; } ;
struct rev_info {int limited; int /*<<< orphan*/  blob_objects; int /*<<< orphan*/  repo; int /*<<< orphan*/  tree_objects; scalar_t__ sources; int /*<<< orphan*/  topo_order; scalar_t__ exclude_promisor_objects; scalar_t__ ignore_missing_links; scalar_t__ tag_objects; } ;
struct object_array_entry {char* name; char* path; unsigned int mode; struct object* item; } ;
struct object {unsigned long flags; scalar_t__ type; } ;
struct commit {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ OBJ_BLOB ; 
 scalar_t__ OBJ_COMMIT ; 
 scalar_t__ OBJ_TAG ; 
 scalar_t__ OBJ_TREE ; 
 unsigned long UNINTERESTING ; 
 int /*<<< orphan*/  add_pending_object (struct rev_info*,struct object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_pending_object_with_path (struct rev_info*,struct object*,char const*,unsigned int,char const*) ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  generation_numbers_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_tagged_oid (struct tag*) ; 
 scalar_t__ is_promisor_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_parents_uninteresting (struct commit*) ; 
 int /*<<< orphan*/  mark_tree_contents_uninteresting (int /*<<< orphan*/ ,struct tree*) ; 
 char const* oid_to_hex (int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 struct object* parse_object (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** revision_sources_at (scalar_t__,struct commit*) ; 
 int /*<<< orphan*/  the_repository ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static struct commit *handle_commit(struct rev_info *revs,
				    struct object_array_entry *entry)
{
	struct object *object = entry->item;
	const char *name = entry->name;
	const char *path = entry->path;
	unsigned int mode = entry->mode;
	unsigned long flags = object->flags;

	/*
	 * Tag object? Look what it points to..
	 */
	while (object->type == OBJ_TAG) {
		struct tag *tag = (struct tag *) object;
		if (revs->tag_objects && !(flags & UNINTERESTING))
			add_pending_object(revs, object, tag->tag);
		object = parse_object(revs->repo, get_tagged_oid(tag));
		if (!object) {
			if (revs->ignore_missing_links || (flags & UNINTERESTING))
				return NULL;
			if (revs->exclude_promisor_objects &&
			    is_promisor_object(&tag->tagged->oid))
				return NULL;
			die("bad object %s", oid_to_hex(&tag->tagged->oid));
		}
		object->flags |= flags;
		/*
		 * We'll handle the tagged object by looping or dropping
		 * through to the non-tag handlers below. Do not
		 * propagate path data from the tag's pending entry.
		 */
		path = NULL;
		mode = 0;
	}

	/*
	 * Commit object? Just return it, we'll do all the complex
	 * reachability crud.
	 */
	if (object->type == OBJ_COMMIT) {
		struct commit *commit = (struct commit *)object;

		if (parse_commit(commit) < 0)
			die("unable to parse commit %s", name);
		if (flags & UNINTERESTING) {
			mark_parents_uninteresting(commit);

			if (!revs->topo_order || !generation_numbers_enabled(the_repository))
				revs->limited = 1;
		}
		if (revs->sources) {
			char **slot = revision_sources_at(revs->sources, commit);

			if (!*slot)
				*slot = xstrdup(name);
		}
		return commit;
	}

	/*
	 * Tree object? Either mark it uninteresting, or add it
	 * to the list of objects to look at later..
	 */
	if (object->type == OBJ_TREE) {
		struct tree *tree = (struct tree *)object;
		if (!revs->tree_objects)
			return NULL;
		if (flags & UNINTERESTING) {
			mark_tree_contents_uninteresting(revs->repo, tree);
			return NULL;
		}
		add_pending_object_with_path(revs, object, name, mode, path);
		return NULL;
	}

	/*
	 * Blob object? You know the drill by now..
	 */
	if (object->type == OBJ_BLOB) {
		if (!revs->blob_objects)
			return NULL;
		if (flags & UNINTERESTING)
			return NULL;
		add_pending_object_with_path(revs, object, name, mode, path);
		return NULL;
	}
	die("%s is unknown object", name);
}