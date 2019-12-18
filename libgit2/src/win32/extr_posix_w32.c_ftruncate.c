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
typedef  scalar_t__ git_off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFBIG ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ INT32_MAX ; 
 int _chsize (int,long) ; 
 scalar_t__ _chsize_s (int,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 

int p_ftruncate(int fd, git_off_t size)
{
	if (size < 0) {
		errno = EINVAL;
		return -1;
	}

#if !defined(__MINGW32__) || defined(MINGW_HAS_SECURE_API)
	return ((_chsize_s(fd, size) == 0) ? 0 : -1);
#else
	/* TODO MINGW32 Find a replacement for _chsize() that handles big files. */
	if (size > INT32_MAX) {
		errno = EFBIG;
		return -1;
	}
	return _chsize(fd, (long)size);
#endif
}