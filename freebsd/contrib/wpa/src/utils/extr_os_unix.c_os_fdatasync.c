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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  F_FULLFSYNC ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fdatasync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fsync (int /*<<< orphan*/ ) ; 

int os_fdatasync(FILE *stream)
{
	if (!fflush(stream)) {
#ifdef __linux__
		return fdatasync(fileno(stream));
#else /* !__linux__ */
#ifdef F_FULLFSYNC
		/* OS X does not implement fdatasync(). */
		return fcntl(fileno(stream), F_FULLFSYNC);
#else /* F_FULLFSYNC */
		return fsync(fileno(stream));
#endif /* F_FULLFSYNC */
#endif /* __linux__ */
	}

	return -1;
}