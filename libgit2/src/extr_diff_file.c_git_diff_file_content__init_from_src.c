#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_11__ {size_t buflen; scalar_t__ buf; scalar_t__ blob; } ;
typedef  TYPE_2__ git_diff_file_content_src ;
struct TYPE_10__ {size_t len; char* data; } ;
struct TYPE_12__ {TYPE_1__ map; TYPE_4__* file; int /*<<< orphan*/  flags; int /*<<< orphan*/  blob; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_3__ git_diff_file_content ;
struct TYPE_13__ {size_t size; void* id_abbrev; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; int /*<<< orphan*/  flags; } ;
typedef  TYPE_4__ git_diff_file ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_FLAG_VALID_ID ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__FREE_BLOB ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__LOADED ; 
 int /*<<< orphan*/  GIT_DIFF_FLAG__NO_DATA ; 
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 void* GIT_OID_HEXSZ ; 
 int diff_file_content_init_common (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_blob_dup (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_id (scalar_t__) ; 
 scalar_t__ git_blob_rawcontent (scalar_t__) ; 
 size_t git_blob_rawsize (scalar_t__) ; 
 int /*<<< orphan*/  git_odb_hash (int /*<<< orphan*/ *,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

int git_diff_file_content__init_from_src(
	git_diff_file_content *fc,
	git_repository *repo,
	const git_diff_options *opts,
	const git_diff_file_content_src *src,
	git_diff_file *as_file)
{
	memset(fc, 0, sizeof(*fc));
	fc->repo = repo;
	fc->file = as_file;

	if (!src->blob && !src->buf) {
		fc->flags |= GIT_DIFF_FLAG__NO_DATA;
	} else {
		fc->flags |= GIT_DIFF_FLAG__LOADED;
		fc->file->flags |= GIT_DIFF_FLAG_VALID_ID;
		fc->file->mode = GIT_FILEMODE_BLOB;

		if (src->blob) {
			git_blob_dup((git_blob **)&fc->blob, (git_blob *) src->blob);
			fc->file->size = git_blob_rawsize(src->blob);
			git_oid_cpy(&fc->file->id, git_blob_id(src->blob));
			fc->file->id_abbrev = GIT_OID_HEXSZ;

			fc->map.len  = (size_t)fc->file->size;
			fc->map.data = (char *)git_blob_rawcontent(src->blob);

			fc->flags |= GIT_DIFF_FLAG__FREE_BLOB;
		} else {
			fc->file->size = src->buflen;
			git_odb_hash(&fc->file->id, src->buf, src->buflen, GIT_OBJECT_BLOB);
			fc->file->id_abbrev = GIT_OID_HEXSZ;

			fc->map.len  = src->buflen;
			fc->map.data = (char *)src->buf;
		}
	}

	return diff_file_content_init_common(fc, opts);
}