#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_blame_hunk ;
typedef  int /*<<< orphan*/  git_blame__origin ;
struct TYPE_15__ {scalar_t__ num_lines; scalar_t__ lno; scalar_t__ s_lno; struct TYPE_15__* next; int /*<<< orphan*/ * suspect; } ;
typedef  TYPE_2__ git_blame__entry ;
struct TYPE_14__ {scalar_t__ min_line; scalar_t__ max_line; int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {int /*<<< orphan*/  hunks; TYPE_2__* ent; TYPE_1__ options; int /*<<< orphan*/  final_blob; int /*<<< orphan*/  final_buf_size; int /*<<< orphan*/  final_buf; int /*<<< orphan*/  path; int /*<<< orphan*/  final; } ;
typedef  TYPE_3__ git_blame ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git_blame__free_entry (TYPE_2__*) ; 
 int git_blame__get_origin (int /*<<< orphan*/ **,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_blame__like_git (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_rawcontent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_rawsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hunk_from_entry (TYPE_2__*,TYPE_3__*) ; 
 scalar_t__ index_blob_lines (TYPE_3__*) ; 
 int load_blob (TYPE_3__*) ; 

__attribute__((used)) static int blame_internal(git_blame *blame)
{
	int error;
	git_blame__entry *ent = NULL;
	git_blame__origin *o;

	if ((error = load_blob(blame)) < 0 ||
	    (error = git_blame__get_origin(&o, blame, blame->final, blame->path)) < 0)
		goto cleanup;
	blame->final_buf = git_blob_rawcontent(blame->final_blob);
	blame->final_buf_size = git_blob_rawsize(blame->final_blob);

	ent = git__calloc(1, sizeof(git_blame__entry));
	GIT_ERROR_CHECK_ALLOC(ent);

	ent->num_lines = index_blob_lines(blame);
	ent->lno = blame->options.min_line - 1;
	ent->num_lines = ent->num_lines - blame->options.min_line + 1;
	if (blame->options.max_line > 0)
		ent->num_lines = blame->options.max_line - blame->options.min_line + 1;
	ent->s_lno = ent->lno;
	ent->suspect = o;

	blame->ent = ent;

	error = git_blame__like_git(blame, blame->options.flags);

cleanup:
	for (ent = blame->ent; ent; ) {
		git_blame__entry *e = ent->next;
		git_blame_hunk *h = hunk_from_entry(ent, blame);

		git_vector_insert(&blame->hunks, h);

		git_blame__free_entry(ent);
		ent = e;
	}

	return error;
}