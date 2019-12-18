#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mkuz_blk_info {unsigned int offset; scalar_t__ len; scalar_t__ blkno; int /*<<< orphan*/  digest; } ;
struct mkuz_blkcache_itm {struct mkuz_blk_info hit; struct mkuz_blkcache_itm* next; } ;
struct mkuz_blk {struct mkuz_blk_info info; } ;
struct TYPE_2__ {struct mkuz_blkcache_itm* first; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2J (scalar_t__) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ blkcache ; 
 unsigned char digest_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mkuz_blkcache_itm* malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct mkuz_blkcache_itm*,char,int) ; 
 int /*<<< orphan*/  stderr ; 
 int verify_match (int,struct mkuz_blk const*,struct mkuz_blkcache_itm*) ; 
 int /*<<< orphan*/  warn (char*) ; 

struct mkuz_blk_info *
mkuz_blkcache_regblock(int fd, const struct mkuz_blk *bp)
{
    struct mkuz_blkcache_itm *bcep;
    int rval;
    unsigned char h;

#if defined(MKUZ_DEBUG)
    assert((unsigned)lseek(fd, 0, SEEK_CUR) == bp->info.offset);
#endif
    h = digest_fold(bp->info.digest);
    if (blkcache.first[h].hit.len == 0) {
        bcep = &blkcache.first[h];
    } else {
        for (bcep = &blkcache.first[h]; bcep != NULL; bcep = bcep->next) {
            if (bcep->hit.len != bp->info.len)
                continue;
            if (memcmp(bp->info.digest, bcep->hit.digest,
              sizeof(bp->info.digest)) == 0) {
                break;
            }
        }
        if (bcep != NULL) {
            rval = verify_match(fd, bp, bcep);
            if (rval == 1) {
#if defined(MKUZ_DEBUG)
                fprintf(stderr, "cache hit %jd, %jd, %jd, %jd\n",
                  I2J(bcep->hit.blkno), I2J(bcep->hit.offset),
                  I2J(bp->info.offset), I2J(bp->info.len));
#endif
                return (&bcep->hit);
            }
            if (rval == 0) {
#if defined(MKUZ_DEBUG)
                fprintf(stderr, "block MD5 collision, you should try lottery, "
                  "man!\n");
#endif
                return (NULL);
            }
            warn("verify_match");
            return (NULL);
        }
        bcep = malloc(sizeof(struct mkuz_blkcache_itm));
        if (bcep == NULL)
            return (NULL);
        memset(bcep, '\0', sizeof(struct mkuz_blkcache_itm));
        bcep->next = blkcache.first[h].next;
        blkcache.first[h].next = bcep;
    }
    bcep->hit = bp->info;
    return (NULL);
}