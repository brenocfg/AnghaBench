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
struct TYPE_3__ {int fae_action; int fae_fildes; int fae_newfildes; int /*<<< orphan*/  fae_mode; int /*<<< orphan*/  fae_oflag; int /*<<< orphan*/  fae_path; } ;
typedef  TYPE_1__ posix_spawn_file_actions_entry_t ;

/* Variables and functions */
 int EBADF ; 
#define  FAE_CLOSE 130 
#define  FAE_DUP2 129 
#define  FAE_OPEN 128 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  _close (int) ; 
 int _dup2 (int,int) ; 
 int _fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 

__attribute__((used)) static int
process_file_actions_entry(posix_spawn_file_actions_entry_t *fae)
{
	int fd, saved_errno;

	switch (fae->fae_action) {
	case FAE_OPEN:
		/* Perform an open(), make it use the right fd */
		fd = _open(fae->fae_path, fae->fae_oflag, fae->fae_mode);
		if (fd < 0)
			return (errno);
		if (fd != fae->fae_fildes) {
			if (_dup2(fd, fae->fae_fildes) == -1) {
				saved_errno = errno;
				(void)_close(fd);
				return (saved_errno);
			}
			if (_close(fd) != 0) {
				if (errno == EBADF)
					return (EBADF);
			}
		}
		if (_fcntl(fae->fae_fildes, F_SETFD, 0) == -1)
			return (errno);
		break;
	case FAE_DUP2:
		/* Perform a dup2() */
		if (_dup2(fae->fae_fildes, fae->fae_newfildes) == -1)
			return (errno);
		if (_fcntl(fae->fae_newfildes, F_SETFD, 0) == -1)
			return (errno);
		break;
	case FAE_CLOSE:
		/* Perform a close(), do not fail if already closed */
		(void)_close(fae->fae_fildes);
		break;
	}
	return (0);
}