#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {unsigned int length; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_32__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_remote_head ;
struct TYPE_33__ {scalar_t__ (* update_tips ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;
typedef  TYPE_3__ git_remote_callbacks ;
typedef  scalar_t__ git_remote_autotag_option_t ;
struct TYPE_34__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_4__ git_remote ;
struct TYPE_35__ {scalar_t__ dst; } ;
typedef  TYPE_5__ git_refspec ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
struct TYPE_36__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_6__ git_buf ;

/* Variables and functions */
 TYPE_6__ GIT_BUF_INIT ; 
 int GIT_EEXISTS ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OID_RAWSZ ; 
 int /*<<< orphan*/  GIT_REFSPEC_TAGS ; 
 scalar_t__ GIT_REMOTE_DOWNLOAD_TAGS_AUTO ; 
 scalar_t__ GIT_REMOTE_DOWNLOAD_TAGS_NONE ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_6__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_6__*) ; 
 scalar_t__ git_buf_len (TYPE_6__*) ; 
 scalar_t__ git_buf_puts (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid__cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_is_valid_name (int /*<<< orphan*/ ) ; 
 int git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_refspec__dispose (TYPE_5__*) ; 
 scalar_t__ git_refspec__parse (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ git_refspec_src_matches (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_refspec_transform (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int git_remote_write_fetchhead (TYPE_4__*,TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ git_repository_odb__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 TYPE_2__* git_vector_get (TYPE_1__*,unsigned int) ; 
 scalar_t__ git_vector_init (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int git_vector_insert (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_tips_for_spec(
		git_remote *remote,
		const git_remote_callbacks *callbacks,
		int update_fetchhead,
		git_remote_autotag_option_t tagopt,
		git_refspec *spec,
		git_vector *refs,
		const char *log_message)
{
	int error = 0, autotag;
	unsigned int i = 0;
	git_buf refname = GIT_BUF_INIT;
	git_oid old;
	git_odb *odb;
	git_remote_head *head;
	git_reference *ref;
	git_refspec tagspec;
	git_vector update_heads;

	assert(remote);

	if (git_repository_odb__weakptr(&odb, remote->repo) < 0)
		return -1;

	if (git_refspec__parse(&tagspec, GIT_REFSPEC_TAGS, true) < 0)
		return -1;

	/* Make a copy of the transport's refs */
	if (git_vector_init(&update_heads, 16, NULL) < 0)
		return -1;

	for (; i < refs->length; ++i) {
		head = git_vector_get(refs, i);
		autotag = 0;
		git_buf_clear(&refname);

		/* Ignore malformed ref names (which also saves us from tag^{} */
		if (!git_reference_is_valid_name(head->name))
			continue;

		/* If we have a tag, see if the auto-follow rules say to update it */
		if (git_refspec_src_matches(&tagspec, head->name)) {
			if (tagopt != GIT_REMOTE_DOWNLOAD_TAGS_NONE) {

				if (tagopt == GIT_REMOTE_DOWNLOAD_TAGS_AUTO)
					autotag = 1;

				git_buf_clear(&refname);
				if (git_buf_puts(&refname, head->name) < 0)
					goto on_error;
			}
		}

		/* If we didn't want to auto-follow the tag, check if the refspec matches */
		if (!autotag && git_refspec_src_matches(spec, head->name)) {
			if (spec->dst) {
				if (git_refspec_transform(&refname, spec, head->name) < 0)
					goto on_error;
			} else {
				/*
				 * no rhs mans store it in FETCH_HEAD, even if we don't
				 update anything else.
				 */
				if ((error = git_vector_insert(&update_heads, head)) < 0)
					goto on_error;

				continue;
			}
		}

		/* If we still don't have a refname, we don't want it */
		if (git_buf_len(&refname) == 0) {
			continue;
		}

		/* In autotag mode, only create tags for objects already in db */
		if (autotag && !git_odb_exists(odb, &head->oid))
			continue;

		if (!autotag && git_vector_insert(&update_heads, head) < 0)
			goto on_error;

		error = git_reference_name_to_id(&old, remote->repo, refname.ptr);
		if (error < 0 && error != GIT_ENOTFOUND)
			goto on_error;

		if (error == GIT_ENOTFOUND) {
			memset(&old, 0, GIT_OID_RAWSZ);

			if (autotag && git_vector_insert(&update_heads, head) < 0)
				goto on_error;
		}

		if (!git_oid__cmp(&old, &head->oid))
			continue;

		/* In autotag mode, don't overwrite any locally-existing tags */
		error = git_reference_create(&ref, remote->repo, refname.ptr, &head->oid, !autotag,
				log_message);

		if (error == GIT_EEXISTS)
			continue;

		if (error < 0)
			goto on_error;

		git_reference_free(ref);

		if (callbacks && callbacks->update_tips != NULL) {
			if (callbacks->update_tips(refname.ptr, &old, &head->oid, callbacks->payload) < 0)
				goto on_error;
		}
	}

	if (update_fetchhead &&
	    (error = git_remote_write_fetchhead(remote, spec, &update_heads)) < 0)
		goto on_error;

	git_vector_free(&update_heads);
	git_refspec__dispose(&tagspec);
	git_buf_dispose(&refname);
	return 0;

on_error:
	git_vector_free(&update_heads);
	git_refspec__dispose(&tagspec);
	git_buf_dispose(&refname);
	return -1;

}