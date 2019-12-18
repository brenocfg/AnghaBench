#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct string_list_item {struct rerere_id* util; } ;
struct string_list {int dummy; } ;
struct rerere_id {scalar_t__ variant; TYPE_1__* collection; } ;
struct index_state {int dummy; } ;
struct TYPE_8__ {struct rerere_id* ptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_2__ mmfile_t ;
struct TYPE_9__ {struct rerere_id* ptr; int /*<<< orphan*/  member_1; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_3__ mmbuffer_t ;
struct TYPE_7__ {scalar_t__ status_nr; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int GIT_MAX_RAWSZ ; 
 char* _ (char*) ; 
 scalar_t__ errno ; 
 int error (char*,char const*) ; 
 int /*<<< orphan*/  error_errno (char*,char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (struct rerere_id*) ; 
 int /*<<< orphan*/  free_rerere_id (struct string_list_item*) ; 
 int handle_cache (struct index_state*,char const*,unsigned char*,char*) ; 
 int /*<<< orphan*/  has_rerere_resolution (struct rerere_id*) ; 
 struct rerere_id* new_rerere_id (unsigned char*) ; 
 scalar_t__ read_mmfile (TYPE_2__*,char*) ; 
 char* rerere_path (struct rerere_id*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 struct string_list_item* string_list_insert (struct string_list*,char const*) ; 
 int /*<<< orphan*/  try_merge (struct index_state*,struct rerere_id*,char const*,TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static int rerere_forget_one_path(struct index_state *istate,
				  const char *path,
				  struct string_list *rr)
{
	const char *filename;
	struct rerere_id *id;
	unsigned char hash[GIT_MAX_RAWSZ];
	int ret;
	struct string_list_item *item;

	/*
	 * Recreate the original conflict from the stages in the
	 * index and compute the conflict ID
	 */
	ret = handle_cache(istate, path, hash, NULL);
	if (ret < 1)
		return error(_("could not parse conflict hunks in '%s'"), path);

	/* Nuke the recorded resolution for the conflict */
	id = new_rerere_id(hash);

	for (id->variant = 0;
	     id->variant < id->collection->status_nr;
	     id->variant++) {
		mmfile_t cur = { NULL, 0 };
		mmbuffer_t result = {NULL, 0};
		int cleanly_resolved;

		if (!has_rerere_resolution(id))
			continue;

		handle_cache(istate, path, hash, rerere_path(id, "thisimage"));
		if (read_mmfile(&cur, rerere_path(id, "thisimage"))) {
			free(cur.ptr);
			error(_("failed to update conflicted state in '%s'"), path);
			goto fail_exit;
		}
		cleanly_resolved = !try_merge(istate, id, path, &cur, &result);
		free(result.ptr);
		free(cur.ptr);
		if (cleanly_resolved)
			break;
	}

	if (id->collection->status_nr <= id->variant) {
		error(_("no remembered resolution for '%s'"), path);
		goto fail_exit;
	}

	filename = rerere_path(id, "postimage");
	if (unlink(filename)) {
		if (errno == ENOENT)
			error(_("no remembered resolution for '%s'"), path);
		else
			error_errno(_("cannot unlink '%s'"), filename);
		goto fail_exit;
	}

	/*
	 * Update the preimage so that the user can resolve the
	 * conflict in the working tree, run us again to record
	 * the postimage.
	 */
	handle_cache(istate, path, hash, rerere_path(id, "preimage"));
	fprintf_ln(stderr, _("Updated preimage for '%s'"), path);

	/*
	 * And remember that we can record resolution for this
	 * conflict when the user is done.
	 */
	item = string_list_insert(rr, path);
	free_rerere_id(item);
	item->util = id;
	fprintf(stderr, _("Forgot resolution for '%s'\n"), path);
	return 0;

fail_exit:
	free(id);
	return -1;
}