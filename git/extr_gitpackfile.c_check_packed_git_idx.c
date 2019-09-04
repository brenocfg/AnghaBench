#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_size; } ;
struct packed_git {int dummy; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  close (int) ; 
 int error (char*,char const*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int git_open (char const*) ; 
 int load_idx (char const*,unsigned int const,void*,size_t,struct packed_git*) ; 
 int /*<<< orphan*/  munmap (void*,size_t) ; 
 TYPE_1__* the_hash_algo ; 
 void* xmmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 size_t xsize_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_packed_git_idx(const char *path, struct packed_git *p)
{
	void *idx_map;
	size_t idx_size;
	int fd = git_open(path), ret;
	struct stat st;
	const unsigned int hashsz = the_hash_algo->rawsz;

	if (fd < 0)
		return -1;
	if (fstat(fd, &st)) {
		close(fd);
		return -1;
	}
	idx_size = xsize_t(st.st_size);
	if (idx_size < 4 * 256 + hashsz + hashsz) {
		close(fd);
		return error("index file %s is too small", path);
	}
	idx_map = xmmap(NULL, idx_size, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	ret = load_idx(path, hashsz, idx_map, idx_size, p);

	if (ret)
		munmap(idx_map, idx_size);

	return ret;
}