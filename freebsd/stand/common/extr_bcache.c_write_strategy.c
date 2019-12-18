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
struct bcache_devdata {int (* dv_strategy ) (int /*<<< orphan*/ ,int,size_t,size_t,char*,size_t*) ;int /*<<< orphan*/  dv_devdata; struct bcache* dv_cache; } ;
struct bcache {int dummy; } ;
typedef  size_t daddr_t ;

/* Variables and functions */
 size_t bcache_blksize ; 
 int /*<<< orphan*/  bcache_invalidate (struct bcache*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int,size_t,size_t,char*,size_t*) ; 

__attribute__((used)) static int
write_strategy(void *devdata, int rw, daddr_t blk, size_t size,
    char *buf, size_t *rsize)
{
    struct bcache_devdata	*dd = (struct bcache_devdata *)devdata;
    struct bcache		*bc = dd->dv_cache;
    daddr_t			i, nblk;

    nblk = size / bcache_blksize;

    /* Invalidate the blocks being written */
    for (i = 0; i < nblk; i++) {
	bcache_invalidate(bc, blk + i);
    }

    /* Write the blocks */
    return (dd->dv_strategy(dd->dv_devdata, rw, blk, size, buf, rsize));
}