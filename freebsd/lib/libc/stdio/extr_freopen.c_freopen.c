#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  fpos_t ;
struct TYPE_21__ {scalar_t__ _size; } ;
struct TYPE_20__ {scalar_t__ _size; } ;
struct TYPE_19__ {scalar_t__ _size; int /*<<< orphan*/ * _base; } ;
struct TYPE_22__ {int _flags; int _file; int /*<<< orphan*/  _flags2; int /*<<< orphan*/  (* _close ) (TYPE_4__*) ;int /*<<< orphan*/  _seek; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; struct TYPE_22__* _cookie; int /*<<< orphan*/  _mbstate; scalar_t__ _orientation; TYPE_3__ _lb; TYPE_2__ _ub; scalar_t__ _lbfsize; TYPE_1__ _bf; int /*<<< orphan*/ * _p; scalar_t__ _r; scalar_t__ _w; } ;
typedef  TYPE_4__ FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int EBADF ; 
 int EINVAL ; 
 int EMFILE ; 
 int ENFILE ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (TYPE_4__*) ; 
 int /*<<< orphan*/  FREELB (TYPE_4__*) ; 
 int /*<<< orphan*/  FREEUB (TYPE_4__*) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 int /*<<< orphan*/  F_DUP2FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ HASLB (TYPE_4__*) ; 
 scalar_t__ HASUB (TYPE_4__*) ; 
 int O_ACCMODE ; 
 int O_APPEND ; 
 int O_CLOEXEC ; 
 int O_EXEC ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SHRT_MAX ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  __S2OAP ; 
 int __SEOF ; 
 int __SMBF ; 
 int __SWR ; 
 int /*<<< orphan*/  __sclose (TYPE_4__*) ; 
 int /*<<< orphan*/  __sdidinit ; 
 int __sflags (char const*,int*) ; 
 int /*<<< orphan*/  __sflush (TYPE_4__*) ; 
 int /*<<< orphan*/  __sinit () ; 
 int /*<<< orphan*/  __sread ; 
 int /*<<< orphan*/  __sseek ; 
 int /*<<< orphan*/  __swrite ; 
 int /*<<< orphan*/  _close (int) ; 
 scalar_t__ _dup2 (int,int) ; 
 scalar_t__ _fcntl (int,int /*<<< orphan*/ ,...) ; 
 int _open (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sseek (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  fclose (TYPE_4__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ftruncate (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 

FILE *
freopen(const char * __restrict file, const char * __restrict mode,
    FILE * __restrict fp)
{
	int f;
	int dflags, flags, isopen, oflags, sverrno, wantfd;

	if ((flags = __sflags(mode, &oflags)) == 0) {
		sverrno = errno;
		(void) fclose(fp);
		errno = sverrno;
		return (NULL);
	}

	FLOCKFILE_CANCELSAFE(fp);

	if (!__sdidinit)
		__sinit();

	/*
	 * If the filename is a NULL pointer, the caller is asking us to
	 * re-open the same file with a different mode. We allow this only
	 * if the modes are compatible.
	 */
	if (file == NULL) {
		/* See comment below regarding freopen() of closed files. */
		if (fp->_flags == 0) {
			errno = EINVAL;
			fp = NULL;
			goto end;
		}
		if ((dflags = _fcntl(fp->_file, F_GETFL)) < 0) {
			sverrno = errno;
			fclose(fp);
			errno = sverrno;
			fp = NULL;
			goto end;
		}
		/* Work around incorrect O_ACCMODE. */
		if ((dflags & O_ACCMODE) != O_RDWR &&
		    (dflags & (O_ACCMODE | O_EXEC)) != (oflags & O_ACCMODE)) {
			fclose(fp);
			errno = EBADF;
			fp = NULL;
			goto end;
		}
		if (fp->_flags & __SWR)
			(void) __sflush(fp);
		if ((oflags ^ dflags) & O_APPEND) {
			dflags &= ~O_APPEND;
			dflags |= oflags & O_APPEND;
			if (_fcntl(fp->_file, F_SETFL, dflags) < 0) {
				sverrno = errno;
				fclose(fp);
				errno = sverrno;
				fp = NULL;
				goto end;
			}
		}
		if (oflags & O_TRUNC)
			(void) ftruncate(fp->_file, (off_t)0);
		if (!(oflags & O_APPEND))
			(void) _sseek(fp, (fpos_t)0, SEEK_SET);
		if (oflags & O_CLOEXEC)
			(void) _fcntl(fp->_file, F_SETFD, FD_CLOEXEC);
		f = fp->_file;
		isopen = 0;
		wantfd = -1;
		goto finish;
	}

	/*
	 * There are actually programs that depend on being able to "freopen"
	 * descriptors that weren't originally open.  Keep this from breaking.
	 * Remember whether the stream was open to begin with, and which file
	 * descriptor (if any) was associated with it.  If it was attached to
	 * a descriptor, defer closing it; freopen("/dev/stdin", "r", stdin)
	 * should work.  This is unnecessary if it was not a Unix file.
	 */
	if (fp->_flags == 0) {
		fp->_flags = __SEOF;	/* hold on to it */
		isopen = 0;
		wantfd = -1;
	} else {
		/* flush the stream; ANSI doesn't require this. */
		if (fp->_flags & __SWR)
			(void) __sflush(fp);
		/* if close is NULL, closing is a no-op, hence pointless */
		isopen = fp->_close != NULL;
		if ((wantfd = fp->_file) < 0 && isopen) {
			(void) (*fp->_close)(fp->_cookie);
			isopen = 0;
		}
	}

	/* Get a new descriptor to refer to the new file. */
	f = _open(file, oflags, DEFFILEMODE);
	/* If out of fd's close the old one and try again. */
	if (f < 0 && isopen && wantfd > STDERR_FILENO &&
	    (errno == ENFILE || errno == EMFILE)) {
		(void) (*fp->_close)(fp->_cookie);
		isopen = 0;
		wantfd = -1;
		f = _open(file, oflags, DEFFILEMODE);
	}
	sverrno = errno;

finish:
	/*
	 * Finish closing fp.  Even if the open succeeded above, we cannot
	 * keep fp->_base: it may be the wrong size.  This loses the effect
	 * of any setbuffer calls, but stdio has always done this before.
	 *
	 * Leave the existing file descriptor open until dup2() is called
	 * below to avoid races where a concurrent open() in another thread
	 * could claim the existing descriptor.
	 */
	if (fp->_flags & __SMBF)
		free((char *)fp->_bf._base);
	fp->_w = 0;
	fp->_r = 0;
	fp->_p = NULL;
	fp->_bf._base = NULL;
	fp->_bf._size = 0;
	fp->_lbfsize = 0;
	if (HASUB(fp))
		FREEUB(fp);
	fp->_ub._size = 0;
	if (HASLB(fp))
		FREELB(fp);
	fp->_lb._size = 0;
	fp->_orientation = 0;
	memset(&fp->_mbstate, 0, sizeof(mbstate_t));
	fp->_flags2 = 0;

	if (f < 0) {			/* did not get it after all */
		if (isopen)
			(void) (*fp->_close)(fp->_cookie);
		fp->_flags = 0;		/* set it free */
		errno = sverrno;	/* restore in case _close clobbered */
		fp = NULL;
		goto end;
	}

	/*
	 * If reopening something that was open before on a real file, try
	 * to maintain the descriptor.  Various C library routines (perror)
	 * assume stderr is always fd STDERR_FILENO, even if being freopen'd.
	 */
	if (wantfd >= 0) {
		if ((oflags & O_CLOEXEC ? _fcntl(f, F_DUP2FD_CLOEXEC, wantfd) :
		    _dup2(f, wantfd)) >= 0) {
			(void)_close(f);
			f = wantfd;
		} else
			(void)_close(fp->_file);
	}

	/*
	 * File descriptors are a full int, but _file is only a short.
	 * If we get a valid file descriptor that is greater than
	 * SHRT_MAX, then the fd will get sign-extended into an
	 * invalid file descriptor.  Handle this case by failing the
	 * open.
	 */
	if (f > SHRT_MAX) {
		fp->_flags = 0;		/* set it free */
		errno = EMFILE;
		fp = NULL;
		goto end;
	}

	fp->_flags = flags;
	fp->_file = f;
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
		(void) _sseek(fp, (fpos_t)0, SEEK_END);
	}
end:
	FUNLOCKFILE_CANCELSAFE();
	return (fp);
}