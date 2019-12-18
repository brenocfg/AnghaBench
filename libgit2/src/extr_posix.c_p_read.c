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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  git_file ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git__is_ssizet (size_t) ; 
 int read (int /*<<< orphan*/ ,char*,size_t) ; 

ssize_t p_read(git_file fd, void *buf, size_t cnt)
{
	char *b = buf;

	if (!git__is_ssizet(cnt)) {
#ifdef GIT_WIN32
		SetLastError(ERROR_INVALID_PARAMETER);
#endif
		errno = EINVAL;
		return -1;
	}

	while (cnt) {
		ssize_t r;
#ifdef GIT_WIN32
		r = read(fd, b, cnt > INT_MAX ? INT_MAX : (unsigned int)cnt);
#else
		r = read(fd, b, cnt);
#endif
		if (r < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;
			return -1;
		}
		if (!r)
			break;
		cnt -= r;
		b += r;
	}
	return (b - (char *)buf);
}