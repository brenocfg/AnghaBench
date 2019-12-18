#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t git_off_t ;
struct TYPE_10__ {scalar_t__ data; } ;
typedef  TYPE_3__ git_map ;
struct TYPE_11__ {TYPE_2__* pack; } ;
typedef  TYPE_4__ git_indexer ;
typedef  int /*<<< orphan*/  git_file ;
struct TYPE_8__ {int /*<<< orphan*/  fd; } ;
struct TYPE_9__ {TYPE_1__ mwf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAP_SHARED ; 
 int /*<<< orphan*/  GIT_PROT_WRITE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git__mmap_alignment (size_t*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,void const*,size_t) ; 
 int p_mmap (TYPE_3__*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  p_munmap (TYPE_3__*) ; 

__attribute__((used)) static int write_at(git_indexer *idx, const void *data, git_off_t offset, size_t size)
{
	git_file fd = idx->pack->mwf.fd;
	size_t mmap_alignment;
	size_t page_offset;
	git_off_t page_start;
	unsigned char *map_data;
	git_map map;
	int error;

	assert(data && size);

	if ((error = git__mmap_alignment(&mmap_alignment)) < 0)
		return error;

	/* the offset needs to be at the mmap boundary for the platform */
	page_offset = offset % mmap_alignment;
	page_start = offset - page_offset;

	if ((error = p_mmap(&map, page_offset + size, GIT_PROT_WRITE, GIT_MAP_SHARED, fd, page_start)) < 0)
		return error;

	map_data = (unsigned char *)map.data;
	memcpy(map_data + page_offset, data, size);
	p_munmap(&map);

	return 0;
}