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
struct flock {int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_RDLCK ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_UNLCK ; 
 int /*<<< orphan*/  F_WRLCK ; 
#define  LOCK_EX 130 
 int LOCK_NB ; 
#define  LOCK_SH 129 
#define  LOCK_UN 128 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 

int
flock(int fd, int op)
{
	int rc = 0;

#if defined(F_SETLK) && defined(F_SETLKW)
	struct flock fl = {0};

	switch (op & (LOCK_EX|LOCK_SH|LOCK_UN)) {
	case LOCK_EX:
		fl.l_type = F_WRLCK;
		break;

	case LOCK_SH:
		fl.l_type = F_RDLCK;
		break;

	case LOCK_UN:
		fl.l_type = F_UNLCK;
		break;

	default:
		errno = EINVAL;
		return -1;
	}

	fl.l_whence = SEEK_SET;
	rc = fcntl(fd, op & LOCK_NB ? F_SETLK : F_SETLKW, &fl);

	if (rc && (errno == EAGAIN))
		errno = EWOULDBLOCK;
#else
	rc = -1;
	errno = ENOSYS;
#endif

	return rc;
}