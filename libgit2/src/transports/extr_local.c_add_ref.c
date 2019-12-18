#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ direction; int /*<<< orphan*/  refs; int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ transport_local ;
typedef  int /*<<< orphan*/  git_tag ;
struct TYPE_10__ {int /*<<< orphan*/  oid; struct TYPE_10__* name; struct TYPE_10__* symref_target; } ;
typedef  TYPE_2__ git_remote_head ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 scalar_t__ GIT_DIRECTION_FETCH ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 scalar_t__ GIT_OBJECT_TAG ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  GIT_REFS_TAGS_DIR ; 
 int /*<<< orphan*/  free_head (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 scalar_t__ git__prefixcmp (char const*,int /*<<< orphan*/ ) ; 
 void* git__strdup (char const*) ; 
 TYPE_2__* git_buf_detach (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_join (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_object_id (int /*<<< orphan*/ *) ; 
 int git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_object_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int git_reference_resolve (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char const* git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ *) ; 
 int git_tag_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int git_vector_insert (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_ref(transport_local *t, const char *name)
{
	const char peeled[] = "^{}";
	git_reference *ref, *resolved;
	git_remote_head *head;
	git_oid obj_id;
	git_object *obj = NULL, *target = NULL;
	git_buf buf = GIT_BUF_INIT;
	int error;

	if ((error = git_reference_lookup(&ref, t->repo, name)) < 0)
		return error;

	error = git_reference_resolve(&resolved, ref);
	if (error < 0) {
		git_reference_free(ref);
		if (!strcmp(name, GIT_HEAD_FILE) && error == GIT_ENOTFOUND) {
			/* This is actually okay.  Empty repos often have a HEAD that
			 * points to a nonexistent "refs/heads/master". */
			git_error_clear();
			return 0;
		}
		return error;
	}

	git_oid_cpy(&obj_id, git_reference_target(resolved));
	git_reference_free(resolved);

	head = git__calloc(1, sizeof(git_remote_head));
	GIT_ERROR_CHECK_ALLOC(head);

	head->name = git__strdup(name);
	GIT_ERROR_CHECK_ALLOC(head->name);

	git_oid_cpy(&head->oid, &obj_id);

	if (git_reference_type(ref) == GIT_REFERENCE_SYMBOLIC) {
		head->symref_target = git__strdup(git_reference_symbolic_target(ref));
		GIT_ERROR_CHECK_ALLOC(head->symref_target);
	}
	git_reference_free(ref);

	if ((error = git_vector_insert(&t->refs, head)) < 0) {
		free_head(head);
		return error;
	}

	/* If it's not a tag, we don't need to try to peel it */
	if (git__prefixcmp(name, GIT_REFS_TAGS_DIR))
		return 0;

	if ((error = git_object_lookup(&obj, t->repo, &head->oid, GIT_OBJECT_ANY)) < 0)
		return error;

	head = NULL;

	/* If it's not an annotated tag, or if we're mocking
	 * git-receive-pack, just get out */
	if (git_object_type(obj) != GIT_OBJECT_TAG ||
		t->direction != GIT_DIRECTION_FETCH) {
		git_object_free(obj);
		return 0;
	}

	/* And if it's a tag, peel it, and add it to the list */
	head = git__calloc(1, sizeof(git_remote_head));
	GIT_ERROR_CHECK_ALLOC(head);

	if (git_buf_join(&buf, 0, name, peeled) < 0) {
		free_head(head);
		return -1;
	}
	head->name = git_buf_detach(&buf);

	if (!(error = git_tag_peel(&target, (git_tag *)obj))) {
		git_oid_cpy(&head->oid, git_object_id(target));

		if ((error = git_vector_insert(&t->refs, head)) < 0) {
			free_head(head);
		}
	}

	git_object_free(obj);
	git_object_free(target);

	return error;
}