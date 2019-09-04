#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int posix_fallocate (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int p_fallocate(int fd, off_t offset, off_t len)
{
#ifdef __APPLE__
	fstore_t prealloc;
	struct stat st;
	size_t newsize;
	int error;

	if ((error = p_fstat(fd, &st)) < 0)
		return error;

	if (git__add_sizet_overflow(&newsize, offset, len)) {
		errno = EINVAL;
		return -1;
	}

	if (newsize < (unsigned long long)st.st_size)
		return 0;

	memset(&prealloc, 0, sizeof(prealloc));
	prealloc.fst_flags  = F_ALLOCATEALL;
	prealloc.fst_posmode = F_PEOFPOSMODE;
	prealloc.fst_offset = offset;
	prealloc.fst_length = len;

	/*
	 * fcntl will often error when the file already exists; ignore
	 * this error since ftruncate will also resize the file (although
	 * likely slower).
	 */
	fcntl(fd, F_PREALLOCATE, &prealloc);

	return ftruncate(fd, (offset + len));
#else
	return posix_fallocate(fd, offset, len);
#endif
}