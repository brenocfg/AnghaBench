#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
struct git_pack_idx_header {scalar_t__ idx_signature; int idx_version; } ;
struct TYPE_3__ {void* data; } ;
struct git_pack_file {int num_objects; int index_version; TYPE_1__ index_map; } ;
typedef  scalar_t__ git_file ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_ODB ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  PACK_IDX_SIGNATURE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__is_sizet (scalar_t__) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  git_futils_mmap_free (TYPE_1__*) ; 
 int git_futils_mmap_ro (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ git_futils_open_ro (char const*) ; 
 scalar_t__ htonl (int /*<<< orphan*/ ) ; 
 int ntohl (int) ; 
 int /*<<< orphan*/  p_close (scalar_t__) ; 
 scalar_t__ p_fstat (scalar_t__,struct stat*) ; 
 int packfile_error (char*) ; 

__attribute__((used)) static int pack_index_check(const char *path, struct git_pack_file *p)
{
	struct git_pack_idx_header *hdr;
	uint32_t version, nr, i, *index;
	void *idx_map;
	size_t idx_size;
	struct stat st;
	int error;
	/* TODO: properly open the file without access time using O_NOATIME */
	git_file fd = git_futils_open_ro(path);
	if (fd < 0)
		return fd;

	if (p_fstat(fd, &st) < 0) {
		p_close(fd);
		git_error_set(GIT_ERROR_OS, "unable to stat pack index '%s'", path);
		return -1;
	}

	if (!S_ISREG(st.st_mode) ||
		!git__is_sizet(st.st_size) ||
		(idx_size = (size_t)st.st_size) < 4 * 256 + 20 + 20)
	{
		p_close(fd);
		git_error_set(GIT_ERROR_ODB, "invalid pack index '%s'", path);
		return -1;
	}

	error = git_futils_mmap_ro(&p->index_map, fd, 0, idx_size);

	p_close(fd);

	if (error < 0)
		return error;

	hdr = idx_map = p->index_map.data;

	if (hdr->idx_signature == htonl(PACK_IDX_SIGNATURE)) {
		version = ntohl(hdr->idx_version);

		if (version < 2 || version > 2) {
			git_futils_mmap_free(&p->index_map);
			return packfile_error("unsupported index version");
		}

	} else
		version = 1;

	nr = 0;
	index = idx_map;

	if (version > 1)
		index += 2; /* skip index header */

	for (i = 0; i < 256; i++) {
		uint32_t n = ntohl(index[i]);
		if (n < nr) {
			git_futils_mmap_free(&p->index_map);
			return packfile_error("index is non-monotonic");
		}
		nr = n;
	}

	if (version == 1) {
		/*
		 * Total size:
		 * - 256 index entries 4 bytes each
		 * - 24-byte entries * nr (20-byte sha1 + 4-byte offset)
		 * - 20-byte SHA1 of the packfile
		 * - 20-byte SHA1 file checksum
		 */
		if (idx_size != 4*256 + nr * 24 + 20 + 20) {
			git_futils_mmap_free(&p->index_map);
			return packfile_error("index is corrupted");
		}
	} else if (version == 2) {
		/*
		 * Minimum size:
		 * - 8 bytes of header
		 * - 256 index entries 4 bytes each
		 * - 20-byte sha1 entry * nr
		 * - 4-byte crc entry * nr
		 * - 4-byte offset entry * nr
		 * - 20-byte SHA1 of the packfile
		 * - 20-byte SHA1 file checksum
		 * And after the 4-byte offset table might be a
		 * variable sized table containing 8-byte entries
		 * for offsets larger than 2^31.
		 */
		unsigned long min_size = 8 + 4*256 + nr*(20 + 4 + 4) + 20 + 20;
		unsigned long max_size = min_size;

		if (nr)
			max_size += (nr - 1)*8;

		if (idx_size < min_size || idx_size > max_size) {
			git_futils_mmap_free(&p->index_map);
			return packfile_error("wrong index size");
		}
	}

	p->num_objects = nr;
	p->index_version = version;
	return 0;
}