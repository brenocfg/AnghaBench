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
struct bcache_devdata {int (* dv_strategy ) (int /*<<< orphan*/ ,int,scalar_t__,size_t,scalar_t__,size_t*) ;int /*<<< orphan*/  dv_devdata; struct bcache* dv_cache; } ;
struct bcache {size_t ra; size_t bcache_nblks; scalar_t__ bcache_data; } ;
typedef  scalar_t__ daddr_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ BCACHE_LOOKUP (struct bcache*,scalar_t__) ; 
 size_t BCACHE_MINREADAHEAD ; 
 int BCACHE_READAHEAD ; 
 size_t BHASH (struct bcache*,scalar_t__) ; 
 int /*<<< orphan*/  ENODEV ; 
 int F_MASK ; 
 int F_NORA ; 
 size_t MIN (size_t,size_t) ; 
 size_t bcache_blksize ; 
 int /*<<< orphan*/  bcache_hits ; 
 int /*<<< orphan*/  bcache_insert (struct bcache*,scalar_t__) ; 
 int /*<<< orphan*/  bcache_invalidate (struct bcache*,scalar_t__) ; 
 int /*<<< orphan*/  bcache_misses ; 
 size_t bcache_rablks ; 
 int /*<<< orphan*/  bcopy (scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  errno ; 
 size_t rounddown (size_t,int) ; 
 int stub1 (int /*<<< orphan*/ ,int,scalar_t__,size_t,scalar_t__,size_t*) ; 

__attribute__((used)) static int
read_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
    struct bcache_devdata	*dd = (struct bcache_devdata *)devdata;
    struct bcache		*bc = dd->dv_cache;
    size_t			i, nblk, p_size, r_size, complete, ra;
    int				result;
    daddr_t			p_blk;
    caddr_t			p_buf;

    if (bc == NULL) {
	errno = ENODEV;
	return (-1);
    }

    if (rsize != NULL)
	*rsize = 0;

    nblk = size / bcache_blksize;
    if (nblk == 0 && size != 0)
	nblk++;
    result = 0;
    complete = 1;

    /* Satisfy any cache hits up front, break on first miss */
    for (i = 0; i < nblk; i++) {
	if (BCACHE_LOOKUP(bc, (daddr_t)(blk + i))) {
	    bcache_misses += (nblk - i);
	    complete = 0;
	    if (nblk - i > BCACHE_MINREADAHEAD && bc->ra > BCACHE_MINREADAHEAD)
		bc->ra >>= 1;	/* reduce read ahead */
	    break;
	} else {
	    bcache_hits++;
	}
    }

   if (complete) {	/* whole set was in cache, return it */
	if (bc->ra < BCACHE_READAHEAD)
		bc->ra <<= 1;	/* increase read ahead */
	bcopy(bc->bcache_data + (bcache_blksize * BHASH(bc, blk)), buf, size);
	goto done;
   }

    /*
     * Fill in any misses. From check we have i pointing to first missing
     * block, read in all remaining blocks + readahead.
     * We have space at least for nblk - i before bcache wraps.
     */
    p_blk = blk + i;
    p_buf = bc->bcache_data + (bcache_blksize * BHASH(bc, p_blk));
    r_size = bc->bcache_nblks - BHASH(bc, p_blk); /* remaining blocks */

    p_size = MIN(r_size, nblk - i);	/* read at least those blocks */

    /*
     * The read ahead size setup.
     * While the read ahead can save us IO, it also can complicate things:
     * 1. We do not want to read ahead by wrapping around the
     * bcache end - this would complicate the cache management.
     * 2. We are using bc->ra as dynamic hint for read ahead size,
     * detected cache hits will increase the read-ahead block count, and
     * misses will decrease, see the code above.
     * 3. The bcache is sized by 512B blocks, however, the underlying device
     * may have a larger sector size, and we should perform the IO by
     * taking into account these larger sector sizes. We could solve this by
     * passing the sector size to bcache_allocate(), or by using ioctl(), but
     * in this version we are using the constant, 16 blocks, and are rounding
     * read ahead block count down to multiple of 16.
     * Using the constant has two reasons, we are not entirely sure if the
     * BIOS disk interface is providing the correct value for sector size.
     * And secondly, this way we get the most conservative setup for the ra.
     *
     * The selection of multiple of 16 blocks (8KB) is quite arbitrary, however,
     * we want to cover CDs (2K) and 4K disks.
     * bcache_allocate() will always fall back to a minimum of 32 blocks.
     * Our choice of 16 read ahead blocks will always fit inside the bcache.
     */

    if ((rw & F_NORA) == F_NORA)
	ra = 0;
    else
	ra = bc->bcache_nblks - BHASH(bc, p_blk + p_size);

    if (ra != 0 && ra != bc->bcache_nblks) { /* do we have RA space? */
	ra = MIN(bc->ra, ra - 1);
	ra = rounddown(ra, 16);		/* multiple of 16 blocks */
	p_size += ra;
    }

    /* invalidate bcache */
    for (i = 0; i < p_size; i++) {
	bcache_invalidate(bc, p_blk + i);
    }

    r_size = 0;
    /*
     * with read-ahead, it may happen we are attempting to read past
     * disk end, as bcache has no information about disk size.
     * in such case we should get partial read if some blocks can be
     * read or error, if no blocks can be read.
     * in either case we should return the data in bcache and only
     * return error if there is no data.
     */
    rw &= F_MASK;
    result = dd->dv_strategy(dd->dv_devdata, rw, p_blk,
	p_size * bcache_blksize, p_buf, &r_size);

    r_size /= bcache_blksize;
    for (i = 0; i < r_size; i++)
	bcache_insert(bc, p_blk + i);

    /* update ra statistics */
    if (r_size != 0) {
	if (r_size < p_size)
	    bcache_rablks += (p_size - r_size);
	else
	    bcache_rablks += ra;
    }

    /* check how much data can we copy */
    for (i = 0; i < nblk; i++) {
	if (BCACHE_LOOKUP(bc, (daddr_t)(blk + i)))
	    break;
    }

    if (size > i * bcache_blksize)
	size = i * bcache_blksize;

    if (size != 0) {
	bcopy(bc->bcache_data + (bcache_blksize * BHASH(bc, blk)), buf, size);
	result = 0;
    }

 done:
    if ((result == 0) && (rsize != NULL))
	*rsize = size;
    return(result);
}