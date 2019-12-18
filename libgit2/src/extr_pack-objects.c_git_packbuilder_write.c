#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pack_write_context {int /*<<< orphan*/ * stats; int /*<<< orphan*/ * indexer; } ;
struct TYPE_7__ {int /*<<< orphan*/  pack_oid; int /*<<< orphan*/  repo; int /*<<< orphan*/  odb; } ;
typedef  TYPE_1__ git_packbuilder ;
typedef  int /*<<< orphan*/  git_indexer_progress_cb ;
typedef  int /*<<< orphan*/  git_indexer_progress ;
struct TYPE_8__ {void* progress_cb_payload; int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_2__ git_indexer_options ;
typedef  int /*<<< orphan*/  git_indexer ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_FSYNCOBJECTFILES ; 
 TYPE_2__ GIT_INDEXER_OPTIONS_INIT ; 
 int /*<<< orphan*/  PREPARE_PACK ; 
 int /*<<< orphan*/  git_indexer__set_fsync (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_indexer_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_indexer_hash (int /*<<< orphan*/ *) ; 
 scalar_t__ git_indexer_new (int /*<<< orphan*/ **,char const*,unsigned int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_packbuilder_foreach (TYPE_1__*,int /*<<< orphan*/ ,struct pack_write_context*) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cb ; 

int git_packbuilder_write(
	git_packbuilder *pb,
	const char *path,
	unsigned int mode,
	git_indexer_progress_cb progress_cb,
	void *progress_cb_payload)
{
	git_indexer_options opts = GIT_INDEXER_OPTIONS_INIT;
	git_indexer *indexer;
	git_indexer_progress stats;
	struct pack_write_context ctx;
	int t;

	PREPARE_PACK;

	opts.progress_cb = progress_cb;
	opts.progress_cb_payload = progress_cb_payload;

	if (git_indexer_new(
		&indexer, path, mode, pb->odb, &opts) < 0)
		return -1;

	if (!git_repository__configmap_lookup(&t, pb->repo, GIT_CONFIGMAP_FSYNCOBJECTFILES) && t)
		git_indexer__set_fsync(indexer, 1);

	ctx.indexer = indexer;
	ctx.stats = &stats;

	if (git_packbuilder_foreach(pb, write_cb, &ctx) < 0 ||
		git_indexer_commit(indexer, &stats) < 0) {
		git_indexer_free(indexer);
		return -1;
	}

	git_oid_cpy(&pb->pack_oid, git_indexer_hash(indexer));

	git_indexer_free(indexer);
	return 0;
}