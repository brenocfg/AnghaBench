#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_12__ ;

/* Type definitions */
struct TYPE_21__ {void* curpos; } ;
typedef  TYPE_1__ git_packfile_stream ;
typedef  void* git_off_t ;
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  git_mwindow ;
struct TYPE_22__ {int /*<<< orphan*/  received_objects; int /*<<< orphan*/  indexed_objects; } ;
typedef  TYPE_2__ git_indexer_progress ;
struct TYPE_23__ {int have_stream; int have_delta; void* off; TYPE_14__* pack; scalar_t__ entry_type; int /*<<< orphan*/  hash_ctx; int /*<<< orphan*/  entry_data; void* entry_start; TYPE_1__ stream; } ;
typedef  TYPE_3__ git_indexer ;
struct TYPE_19__ {scalar_t__ size; } ;
struct TYPE_20__ {TYPE_12__ mwf; } ;

/* Variables and functions */
 int GIT_EBUFS ; 
 scalar_t__ GIT_OBJECT_OFS_DELTA ; 
 scalar_t__ GIT_OBJECT_REF_DELTA ; 
 int advance_delta_offset (TYPE_3__*,scalar_t__) ; 
 int do_progress_callback (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mwindow_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_packfile_stream_dispose (TYPE_1__*) ; 
 int git_packfile_stream_open (TYPE_1__*,TYPE_14__*,void*) ; 
 int git_packfile_unpack_header (size_t*,scalar_t__*,TYPE_12__*,int /*<<< orphan*/ **,void**) ; 
 int hash_header (int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 int hash_object_stream (TYPE_3__*,TYPE_1__*) ; 
 int read_object_stream (TYPE_3__*,TYPE_1__*) ; 
 int store_delta (TYPE_3__*) ; 
 int store_object (TYPE_3__*) ; 

__attribute__((used)) static int read_stream_object(git_indexer *idx, git_indexer_progress *stats)
{
	git_packfile_stream *stream = &idx->stream;
	git_off_t entry_start = idx->off;
	size_t entry_size;
	git_object_t type;
	git_mwindow *w = NULL;
	int error;

	if (idx->pack->mwf.size <= idx->off + 20)
		return GIT_EBUFS;

	if (!idx->have_stream) {
		error = git_packfile_unpack_header(&entry_size, &type, &idx->pack->mwf, &w, &idx->off);
		if (error == GIT_EBUFS) {
			idx->off = entry_start;
			return error;
		}
		if (error < 0)
			return error;

		git_mwindow_close(&w);
		idx->entry_start = entry_start;
		git_hash_init(&idx->hash_ctx);
		git_buf_clear(&idx->entry_data);

		if (type == GIT_OBJECT_REF_DELTA || type == GIT_OBJECT_OFS_DELTA) {
			error = advance_delta_offset(idx, type);
			if (error == GIT_EBUFS) {
				idx->off = entry_start;
				return error;
			}
			if (error < 0)
				return error;

			idx->have_delta = 1;
		} else {
			idx->have_delta = 0;

			error = hash_header(&idx->hash_ctx, entry_size, type);
			if (error < 0)
				return error;
		}

		idx->have_stream = 1;
		idx->entry_type = type;

		error = git_packfile_stream_open(stream, idx->pack, idx->off);
		if (error < 0)
			return error;
	}

	if (idx->have_delta) {
		error = read_object_stream(idx, stream);
	} else {
		error = hash_object_stream(idx, stream);
	}

	idx->off = stream->curpos;
	if (error == GIT_EBUFS)
		return error;

	/* We want to free the stream reasorces no matter what here */
	idx->have_stream = 0;
	git_packfile_stream_dispose(stream);

	if (error < 0)
		return error;

	if (idx->have_delta) {
		error = store_delta(idx);
	} else {
		error = store_object(idx);
	}

	if (error < 0)
		return error;

	if (!idx->have_delta) {
		stats->indexed_objects++;
	}
	stats->received_objects++;

	if ((error = do_progress_callback(idx, stats)) != 0)
		return error;

	return 0;
}