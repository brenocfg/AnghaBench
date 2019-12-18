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

/* Variables and functions */
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  F_GETFD ; 
 int O_NOCTTY ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int const) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int open (char*,int) ; 

extern void
tuklib_open_stdxxx(int err_status)
{
#ifdef TUKLIB_DOSLIKE
	// Do nothing, just silence warnings.
	(void)err_status;

#else
	for (int i = 0; i <= 2; ++i) {
		// We use fcntl() to check if the file descriptor is open.
		if (fcntl(i, F_GETFD) == -1 && errno == EBADF) {
			// With stdin, we could use /dev/full so that
			// writing to stdin would fail. However, /dev/full
			// is Linux specific, and if the program tries to
			// write to stdin, there's already a problem anyway.
			const int fd = open("/dev/null", O_NOCTTY
					| (i == 0 ? O_WRONLY : O_RDONLY));

			if (fd != i) {
				if (fd != -1)
					(void)close(fd);

				// Something went wrong. Exit with the
				// exit status we were given. Don't try
				// to print an error message, since stderr
				// may very well be non-existent. This
				// error should be extremely rare.
				exit(err_status);
			}
		}
	}
#endif

	return;
}