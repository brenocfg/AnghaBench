#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  free; int /*<<< orphan*/  commit; int /*<<< orphan*/  append; int /*<<< orphan*/ * backend; } ;
struct pack_writepack {TYPE_1__ parent; int /*<<< orphan*/  indexer; } ;
struct pack_backend {int /*<<< orphan*/  pack_folder; } ;
struct git_odb_writepack {int dummy; } ;
typedef  struct git_odb_writepack git_odb_writepack ;
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_indexer_progress_cb ;
struct TYPE_6__ {void* progress_cb_payload; int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_2__ git_indexer_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (struct pack_writepack*) ; 
 TYPE_2__ GIT_INDEXER_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 struct pack_writepack* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (struct pack_writepack*) ; 
 scalar_t__ git_indexer_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  pack_backend__writepack_append ; 
 int /*<<< orphan*/  pack_backend__writepack_commit ; 
 int /*<<< orphan*/  pack_backend__writepack_free ; 

__attribute__((used)) static int pack_backend__writepack(struct git_odb_writepack **out,
	git_odb_backend *_backend,
        git_odb *odb,
	git_indexer_progress_cb progress_cb,
	void *progress_payload)
{
	git_indexer_options opts = GIT_INDEXER_OPTIONS_INIT;
	struct pack_backend *backend;
	struct pack_writepack *writepack;

	assert(out && _backend);

	*out = NULL;

	opts.progress_cb = progress_cb;
	opts.progress_cb_payload = progress_payload;

	backend = (struct pack_backend *)_backend;

	writepack = git__calloc(1, sizeof(struct pack_writepack));
	GIT_ERROR_CHECK_ALLOC(writepack);

	if (git_indexer_new(&writepack->indexer,
		backend->pack_folder, 0, odb, &opts) < 0) {
		git__free(writepack);
		return -1;
	}

	writepack->parent.backend = _backend;
	writepack->parent.append = pack_backend__writepack_append;
	writepack->parent.commit = pack_backend__writepack_commit;
	writepack->parent.free = pack_backend__writepack_free;

	*out = (git_odb_writepack *)writepack;

	return 0;
}