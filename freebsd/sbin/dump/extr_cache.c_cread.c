#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ssize_t ;
typedef  size_t off_t ;
struct TYPE_5__ {scalar_t__ fs_bsize; } ;
struct TYPE_4__ {size_t b_Offset; void* b_Data; struct TYPE_4__* b_HNext; } ;
typedef  TYPE_1__ Block ;

/* Variables and functions */
 TYPE_1__** BlockHash ; 
 int BlockSize ; 
 int /*<<< orphan*/ * DataBase ; 
 size_t HSize ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 scalar_t__ cachesize ; 
 int /*<<< orphan*/  cinit () ; 
 size_t pread (int,void*,size_t,size_t) ; 
 TYPE_2__* sblock ; 

ssize_t
cread(int fd, void *buf, size_t nbytes, off_t offset)
{
	Block *blk;
	Block **pblk;
	Block **ppblk;
	int hi;
	int n;
	off_t mask;

	/*
	 * If the cache is disabled, or we do not yet know the filesystem
	 * block size, then revert to pread.  Otherwise initialize the
	 * cache as necessary and continue.
	 */
	if (cachesize <= 0 || sblock->fs_bsize == 0)
		return(pread(fd, buf, nbytes, offset));
	if (DataBase == NULL)
		cinit();

	/*
	 * If the request crosses a cache block boundary, or the
	 * request is larger or equal to the cache block size,
	 * revert to pread().  Full-block-reads are typically
	 * one-time calls and caching would be detrimental.
	 */
	mask = ~(off_t)(BlockSize - 1);
	if (nbytes >= BlockSize ||
	    ((offset ^ (offset + nbytes - 1)) & mask) != 0) {
		return(pread(fd, buf, nbytes, offset));
	}

	/*
	 * Obtain and access the cache block.  Cache a successful
	 * result.  If an error occurs, revert to pread() (this might
	 * occur near the end of the media).
	 */
	hi = (offset / BlockSize) % HSize;
	pblk = &BlockHash[hi];
	ppblk = NULL;
	while ((blk = *pblk) != NULL) {
		if (((blk->b_Offset ^ offset) & mask) == 0)
			break;
		ppblk = pblk;
		pblk = &blk->b_HNext;
	}
	if (blk == NULL) {
		blk = *ppblk;
		pblk = ppblk;
		blk->b_Offset = offset & mask;
		n = pread(fd, blk->b_Data, BlockSize, blk->b_Offset);
		if (n != BlockSize) {
			blk->b_Offset = (off_t)-1;
			blk = NULL;
		}
	}
	if (blk) {
		bcopy(blk->b_Data + (offset - blk->b_Offset), buf, nbytes);
		*pblk = blk->b_HNext;
		blk->b_HNext = BlockHash[hi];
		BlockHash[hi] = blk;
		return(nbytes);
	} else {
		return(pread(fd, buf, nbytes, offset));
	}
}