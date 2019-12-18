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
struct mparse {int line; int filenc; int options; struct buf* primary; } ;
struct buf {int sz; scalar_t__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANDOCERR_ROFFLOOP ; 
 int MPARSE_LATIN1 ; 
 int MPARSE_UTF8 ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 int /*<<< orphan*/  mandoc_msg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* mandoc_msg_getinfilename () ; 
 int /*<<< orphan*/  mandoc_msg_setinfilename (char const*) ; 
 int /*<<< orphan*/  mparse_buf_r (struct mparse*,struct buf,size_t,int) ; 
 int /*<<< orphan*/  mparse_end (struct mparse*) ; 
 int /*<<< orphan*/  munmap (scalar_t__*,int) ; 
 int read_whole_file (struct mparse*,int,struct buf*,int*) ; 

void
mparse_readfd(struct mparse *curp, int fd, const char *filename)
{
	static int	 recursion_depth;

	struct buf	 blk;
	struct buf	*save_primary;
	const char	*save_filename;
	size_t		 offset;
	int		 save_filenc, save_lineno;
	int		 with_mmap;

	if (recursion_depth > 64) {
		mandoc_msg(MANDOCERR_ROFFLOOP, curp->line, 0, NULL);
		return;
	}
	if (read_whole_file(curp, fd, &blk, &with_mmap) == -1)
		return;

	/*
	 * Save some properties of the parent file.
	 */

	save_primary = curp->primary;
	save_filenc = curp->filenc;
	save_lineno = curp->line;
	save_filename = mandoc_msg_getinfilename();

	curp->primary = &blk;
	curp->filenc = curp->options & (MPARSE_UTF8 | MPARSE_LATIN1);
	curp->line = 1;
	mandoc_msg_setinfilename(filename);

	/* Skip an UTF-8 byte order mark. */
	if (curp->filenc & MPARSE_UTF8 && blk.sz > 2 &&
	    (unsigned char)blk.buf[0] == 0xef &&
	    (unsigned char)blk.buf[1] == 0xbb &&
	    (unsigned char)blk.buf[2] == 0xbf) {
		offset = 3;
		curp->filenc &= ~MPARSE_LATIN1;
	} else
		offset = 0;

	recursion_depth++;
	mparse_buf_r(curp, blk, offset, 1);
	if (--recursion_depth == 0)
		mparse_end(curp);

	/*
	 * Clean up and restore saved parent properties.
	 */

	if (with_mmap)
		munmap(blk.buf, blk.sz);
	else
		free(blk.buf);

	curp->primary = save_primary;
	curp->filenc = save_filenc;
	curp->line = save_lineno;
	if (save_filename != NULL)
		mandoc_msg_setinfilename(save_filename);
}