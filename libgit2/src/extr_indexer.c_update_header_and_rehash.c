#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct git_pack_header {int dummy; } ;
typedef  scalar_t__ git_off_t ;
struct TYPE_13__ {scalar_t__ size; } ;
typedef  TYPE_2__ git_mwindow_file ;
typedef  int /*<<< orphan*/  git_mwindow ;
struct TYPE_14__ {scalar_t__ local_objects; scalar_t__ total_objects; } ;
typedef  TYPE_3__ git_indexer_progress ;
struct TYPE_16__ {int /*<<< orphan*/  hdr_entries; } ;
struct TYPE_15__ {scalar_t__ inbuf_len; TYPE_6__ hdr; int /*<<< orphan*/  trailer; TYPE_1__* pack; } ;
typedef  TYPE_4__ git_indexer ;
struct TYPE_12__ {TYPE_2__ mwf; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_hash_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_mwindow_close (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_mwindow_free_all (TYPE_2__*) ; 
 void* git_mwindow_open (TYPE_2__*,int /*<<< orphan*/ **,scalar_t__,size_t,unsigned int*) ; 
 int /*<<< orphan*/  hash_partially (TYPE_4__*,void*,unsigned int) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 scalar_t__ write_at (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int update_header_and_rehash(git_indexer *idx, git_indexer_progress *stats)
{
	void *ptr;
	size_t chunk = 1024*1024;
	git_off_t hashed = 0;
	git_mwindow *w = NULL;
	git_mwindow_file *mwf;
	unsigned int left;

	mwf = &idx->pack->mwf;

	git_hash_init(&idx->trailer);


	/* Update the header to include the numer of local objects we injected */
	idx->hdr.hdr_entries = htonl(stats->total_objects + stats->local_objects);
	if (write_at(idx, &idx->hdr, 0, sizeof(struct git_pack_header)) < 0)
		return -1;

	/*
	 * We now use the same technique as before to determine the
	 * hash. We keep reading up to the end and let
	 * hash_partially() keep the existing trailer out of the
	 * calculation.
	 */
	git_mwindow_free_all(mwf);
	idx->inbuf_len = 0;
	while (hashed < mwf->size) {
		ptr = git_mwindow_open(mwf, &w, hashed, chunk, &left);
		if (ptr == NULL)
			return -1;

		hash_partially(idx, ptr, left);
		hashed += left;

		git_mwindow_close(&w);
	}

	return 0;
}