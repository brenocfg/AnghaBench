#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int _flags; int _file; int /*<<< orphan*/  _close; int /*<<< orphan*/  _seek; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; struct TYPE_4__* _cookie; int /*<<< orphan*/  _flags2; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMFILE ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_CLOEXEC ; 
 int O_EXEC ; 
 int O_RDWR ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  __S2OAP ; 
 int __SAPP ; 
 int /*<<< orphan*/  __sclose ; 
 int __sflags (char const*,int*) ; 
 TYPE_1__* __sfp () ; 
 int /*<<< orphan*/  __sread ; 
 int /*<<< orphan*/  __sseek ; 
 int /*<<< orphan*/  __swrite ; 
 int _fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

FILE *
fdopen(int fd, const char *mode)
{
	FILE *fp;
	int flags, oflags, fdflags, tmp;

	/*
	 * File descriptors are a full int, but _file is only a short.
	 * If we get a valid file descriptor that is greater than
	 * SHRT_MAX, then the fd will get sign-extended into an
	 * invalid file descriptor.  Handle this case by failing the
	 * open.
	 */
	if (fd > SHRT_MAX) {
		errno = EMFILE;
		return (NULL);
	}

	if ((flags = __sflags(mode, &oflags)) == 0)
		return (NULL);

	/* Make sure the mode the user wants is a subset of the actual mode. */
	if ((fdflags = _fcntl(fd, F_GETFL, 0)) < 0)
		return (NULL);
	/* Work around incorrect O_ACCMODE. */
	tmp = fdflags & (O_ACCMODE | O_EXEC);
	if (tmp != O_RDWR && (tmp != (oflags & O_ACCMODE))) {
		errno = EINVAL;
		return (NULL);
	}

	if ((fp = __sfp()) == NULL)
		return (NULL);

	if ((oflags & O_CLOEXEC) && _fcntl(fd, F_SETFD, FD_CLOEXEC) == -1) {
		fp->_flags = 0;
		return (NULL);
	}

	fp->_flags = flags;
	/*
	 * If opened for appending, but underlying descriptor does not have
	 * O_APPEND bit set, assert __SAPP so that __swrite() caller
	 * will _sseek() to the end before write.
	 */
	if (fdflags & O_APPEND)
		fp->_flags2 |= __S2OAP;
	else if (oflags & O_APPEND)
		fp->_flags |= __SAPP;
	fp->_file = fd;
	fp->_cookie = fp;
	fp->_read = __sread;
	fp->_write = __swrite;
	fp->_seek = __sseek;
	fp->_close = __sclose;
	return (fp);
}