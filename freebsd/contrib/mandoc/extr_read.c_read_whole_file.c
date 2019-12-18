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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct mparse {scalar_t__ gzip; } ;
struct buf {size_t sz; scalar_t__ buf; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/ * gzFile ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_DUP ; 
 int /*<<< orphan*/  MANDOCERR_FSTAT ; 
 int /*<<< orphan*/  MANDOCERR_GZCLOSE ; 
 int /*<<< orphan*/  MANDOCERR_GZDOPEN ; 
 int /*<<< orphan*/  MANDOCERR_READ ; 
 int /*<<< orphan*/  MANDOCERR_TOOLARGE ; 
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int Z_ERRNO ; 
 int Z_OK ; 
 int /*<<< orphan*/  close (int) ; 
 int dup (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int gzclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gzdopen (int,char*) ; 
 int /*<<< orphan*/  gzerror (int /*<<< orphan*/ *,int*) ; 
 int gzread (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int read (int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  resize_buf (struct buf*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zError (int) ; 

__attribute__((used)) static int
read_whole_file(struct mparse *curp, int fd, struct buf *fb, int *with_mmap)
{
	struct stat	 st;
	gzFile		 gz;
	size_t		 off;
	ssize_t		 ssz;
	int		 gzerrnum, retval;

	if (fstat(fd, &st) == -1) {
		mandoc_msg(MANDOCERR_FSTAT, 0, 0, "%s", strerror(errno));
		return -1;
	}

	/*
	 * If we're a regular file, try just reading in the whole entry
	 * via mmap().  This is faster than reading it into blocks, and
	 * since each file is only a few bytes to begin with, I'm not
	 * concerned that this is going to tank any machines.
	 */

	if (curp->gzip == 0 && S_ISREG(st.st_mode)) {
		if (st.st_size > 0x7fffffff) {
			mandoc_msg(MANDOCERR_TOOLARGE, 0, 0, NULL);
			return -1;
		}
		*with_mmap = 1;
		fb->sz = (size_t)st.st_size;
		fb->buf = mmap(NULL, fb->sz, PROT_READ, MAP_SHARED, fd, 0);
		if (fb->buf != MAP_FAILED)
			return 0;
	}

	if (curp->gzip) {
		/*
		 * Duplicating the file descriptor is required
		 * because we will have to call gzclose(3)
		 * to free memory used internally by zlib,
		 * but that will also close the file descriptor,
		 * which this function must not do.
		 */
		if ((fd = dup(fd)) == -1) {
			mandoc_msg(MANDOCERR_DUP, 0, 0,
			    "%s", strerror(errno));
			return -1;
		}
		if ((gz = gzdopen(fd, "rb")) == NULL) {
			mandoc_msg(MANDOCERR_GZDOPEN, 0, 0,
			    "%s", strerror(errno));
			close(fd);
			return -1;
		}
	} else
		gz = NULL;

	/*
	 * If this isn't a regular file (like, say, stdin), then we must
	 * go the old way and just read things in bit by bit.
	 */

	*with_mmap = 0;
	off = 0;
	retval = -1;
	fb->sz = 0;
	fb->buf = NULL;
	for (;;) {
		if (off == fb->sz) {
			if (fb->sz == (1U << 31)) {
				mandoc_msg(MANDOCERR_TOOLARGE, 0, 0, NULL);
				break;
			}
			resize_buf(fb, 65536);
		}
		ssz = curp->gzip ?
		    gzread(gz, fb->buf + (int)off, fb->sz - off) :
		    read(fd, fb->buf + (int)off, fb->sz - off);
		if (ssz == 0) {
			fb->sz = off;
			retval = 0;
			break;
		}
		if (ssz == -1) {
			if (curp->gzip)
				(void)gzerror(gz, &gzerrnum);
			mandoc_msg(MANDOCERR_READ, 0, 0, "%s",
			    curp->gzip && gzerrnum != Z_ERRNO ?
			    zError(gzerrnum) : strerror(errno));
			break;
		}
		off += (size_t)ssz;
	}

	if (curp->gzip && (gzerrnum = gzclose(gz)) != Z_OK)
		mandoc_msg(MANDOCERR_GZCLOSE, 0, 0, "%s",
		    gzerrnum == Z_ERRNO ? strerror(errno) :
		    zError(gzerrnum));
	if (retval == -1) {
		free(fb->buf);
		fb->buf = NULL;
	}
	return retval;
}