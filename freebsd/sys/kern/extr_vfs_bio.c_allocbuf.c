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
struct buf {int b_bcount; int b_kvasize; int b_flags; int b_bufsize; int b_offset; } ;

/* Variables and functions */
 int B_CACHE ; 
 int B_MALLOC ; 
 int B_VMIO ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  bufspace_adjust (struct buf*,int) ; 
 int num_pages (int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int round_page (int) ; 
 int roundup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_nonvmio_extend (struct buf*,int) ; 
 int /*<<< orphan*/  vfs_nonvmio_truncate (struct buf*,int) ; 
 int /*<<< orphan*/  vfs_vmio_extend (struct buf*,int,int) ; 
 int /*<<< orphan*/  vfs_vmio_truncate (struct buf*,int) ; 

int
allocbuf(struct buf *bp, int size)
{
	int newbsize;

	if (bp->b_bcount == size)
		return (1);

	if (bp->b_kvasize != 0 && bp->b_kvasize < size)
		panic("allocbuf: buffer too small");

	newbsize = roundup2(size, DEV_BSIZE);
	if ((bp->b_flags & B_VMIO) == 0) {
		if ((bp->b_flags & B_MALLOC) == 0)
			newbsize = round_page(newbsize);
		/*
		 * Just get anonymous memory from the kernel.  Don't
		 * mess with B_CACHE.
		 */
		if (newbsize < bp->b_bufsize)
			vfs_nonvmio_truncate(bp, newbsize);
		else if (newbsize > bp->b_bufsize)
			vfs_nonvmio_extend(bp, newbsize);
	} else {
		int desiredpages;

		desiredpages = (size == 0) ? 0 :
		    num_pages((bp->b_offset & PAGE_MASK) + newbsize);

		if (bp->b_flags & B_MALLOC)
			panic("allocbuf: VMIO buffer can't be malloced");
		/*
		 * Set B_CACHE initially if buffer is 0 length or will become
		 * 0-length.
		 */
		if (size == 0 || bp->b_bufsize == 0)
			bp->b_flags |= B_CACHE;

		if (newbsize < bp->b_bufsize)
			vfs_vmio_truncate(bp, desiredpages);
		/* XXX This looks as if it should be newbsize > b_bufsize */
		else if (size > bp->b_bcount)
			vfs_vmio_extend(bp, desiredpages, size);
		bufspace_adjust(bp, newbsize);
	}
	bp->b_bcount = size;		/* requested buffer size. */
	return (1);
}