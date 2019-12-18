#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fpos_t ;
struct TYPE_5__ {int _flags; int _file; int /*<<< orphan*/  _flags2; int /*<<< orphan*/  _close; int /*<<< orphan*/  _seek; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; struct TYPE_5__* _cookie; } ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int /*<<< orphan*/  EMFILE ; 
 int O_APPEND ; 
 int /*<<< orphan*/  SEEK_END ; 
 int SHRT_MAX ; 
 int /*<<< orphan*/  __S2OAP ; 
 int /*<<< orphan*/  __sclose ; 
 int __sflags (char const*,int*) ; 
 TYPE_1__* __sfp () ; 
 int /*<<< orphan*/  __sread ; 
 int /*<<< orphan*/  __sseek ; 
 int /*<<< orphan*/  __swrite ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sseek (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

FILE *
fopen(const char * __restrict file, const char * __restrict mode)
{
	FILE *fp;
	int f;
	int flags, oflags;

	if ((flags = __sflags(mode, &oflags)) == 0)
		return (NULL);
	if ((fp = __sfp()) == NULL)
		return (NULL);
	if ((f = _open(file, oflags, DEFFILEMODE)) < 0) {
		fp->_flags = 0;			/* release */
		return (NULL);
	}
	/*
	 * File descriptors are a full int, but _file is only a short.
	 * If we get a valid file descriptor that is greater than
	 * SHRT_MAX, then the fd will get sign-extended into an
	 * invalid file descriptor.  Handle this case by failing the
	 * open.
	 */
	if (f > SHRT_MAX) {
		fp->_flags = 0;			/* release */
		_close(f);
		errno = EMFILE;
		return (NULL);
	}
	fp->_file = f;
	fp->_flags = flags;
	fp->_cookie = fp;
	fp->_read = __sread;
	fp->_write = __swrite;
	fp->_seek = __sseek;
	fp->_close = __sclose;
	/*
	 * When opening in append mode, even though we use O_APPEND,
	 * we need to seek to the end so that ftell() gets the right
	 * answer.  If the user then alters the seek pointer, or
	 * the file extends, this will fail, but there is not much
	 * we can do about this.  (We could set __SAPP and check in
	 * fseek and ftell.)
	 */
	if (oflags & O_APPEND) {
		fp->_flags2 |= __S2OAP;
		(void)_sseek(fp, (fpos_t)0, SEEK_END);
	}
	return (fp);
}