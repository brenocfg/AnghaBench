#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  offset; } ;
struct mkuz_blkcache_itm {TYPE_1__ hit; } ;
struct TYPE_4__ {unsigned int len; int /*<<< orphan*/  offset; } ;
struct mkuz_blk {TYPE_2__ info; int /*<<< orphan*/  data; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* malloc (unsigned int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void*,unsigned int) ; 
 scalar_t__ read (int,void*,unsigned int) ; 

__attribute__((used)) static int
verify_match(int fd, const struct mkuz_blk *cbp, struct mkuz_blkcache_itm *bcep)
{
    void *vbuf;
    ssize_t rlen;
    int rval;

    rval = -1;
    vbuf = malloc(cbp->info.len);
    if (vbuf == NULL) {
        goto e0;
    }
    if (lseek(fd, bcep->hit.offset, SEEK_SET) < 0) {
        goto e1;
    }
    rlen = read(fd, vbuf, cbp->info.len);
    if (rlen < 0 || (unsigned)rlen != cbp->info.len) {
        goto e2;
    }
    rval = (memcmp(cbp->data, vbuf, cbp->info.len) == 0) ? 1 : 0;
e2:
    lseek(fd, cbp->info.offset, SEEK_SET);
e1:
    free(vbuf);
e0:
    return (rval);
}