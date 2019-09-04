#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_6__ {size_t LowPart; scalar_t__ HighPart; } ;
struct TYPE_7__ {scalar_t__ QuadPart; TYPE_1__ u; } ;
typedef  TYPE_2__ LARGE_INTEGER ;
typedef  scalar_t__ HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  GetFileSizeEx (scalar_t__,TYPE_2__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetEndOfFile (scalar_t__) ; 
 int /*<<< orphan*/  SetFilePointerEx (scalar_t__,TYPE_2__,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _get_osfhandle (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ git__add_sizet_overflow (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_errno () ; 

int p_fallocate(int fd, off_t offset, off_t len)
{
	HANDLE fh = (HANDLE)_get_osfhandle(fd);
	LARGE_INTEGER zero, position, oldsize, newsize;
	size_t size;

	if (fh == INVALID_HANDLE_VALUE) {
		errno = EBADF;
		return -1;
	}

	if (offset < 0 || len <= 0) {
		errno = EINVAL;
		return -1;
	}

	if (git__add_sizet_overflow(&size, offset, len)) {
		errno = EINVAL;
		return -1;
	}

	zero.u.LowPart = 0;
	zero.u.HighPart = 0;

	newsize.u.LowPart = (size & 0xffffffff);

#if (SIZE_MAX > UINT32_MAX)
	newsize.u.HighPart = size >> 32;
#else
	newsize.u.HighPart = 0;
#endif

	if (!GetFileSizeEx(fh, &oldsize)) {
		set_errno();
		return -1;
	}

	/* POSIX emulation: attempting to shrink the file is ignored */
	if (oldsize.QuadPart >= newsize.QuadPart)
		return 0;

	if (!SetFilePointerEx(fh, zero, &position, FILE_CURRENT) ||
	    !SetFilePointerEx(fh, newsize, NULL, FILE_BEGIN) ||
	    !SetEndOfFile(fh) ||
	    !SetFilePointerEx(fh, position, 0, FILE_BEGIN)) {
		set_errno();
		return -1;
	}

	return 0;
}