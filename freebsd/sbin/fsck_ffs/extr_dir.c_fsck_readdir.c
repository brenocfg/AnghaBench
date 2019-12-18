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
struct inodesc {long id_numfrags; scalar_t__ id_filesize; long id_loc; scalar_t__ id_fix; int /*<<< orphan*/  id_blkno; } ;
struct direct {long d_reclen; } ;
struct TYPE_3__ {scalar_t__ b_buf; } ;
struct bufarea {TYPE_1__ b_un; } ;
struct TYPE_4__ {long fs_fsize; } ;

/* Variables and functions */
 long DIRBLKSIZ ; 
 scalar_t__ IGNORE ; 
 scalar_t__ dircheck (struct inodesc*,struct bufarea*,struct direct*) ; 
 int /*<<< orphan*/  dirty (struct bufarea*) ; 
 scalar_t__ dofix (struct inodesc*,char*) ; 
 struct bufarea* getdirblk (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  memset (struct direct*,int /*<<< orphan*/ ,long) ; 
 TYPE_2__ sblock ; 

__attribute__((used)) static struct direct *
fsck_readdir(struct inodesc *idesc)
{
	struct direct *dp, *ndp;
	struct bufarea *bp;
	long size, blksiz, subsume_ndp;

	subsume_ndp = 0;
	blksiz = idesc->id_numfrags * sblock.fs_fsize;
	if (idesc->id_filesize <= 0 || idesc->id_loc >= blksiz)
		return (NULL);
	bp = getdirblk(idesc->id_blkno, blksiz);
	dp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
	/*
	 * Only need to check current entry if it is the first in the
	 * the block, as later entries will have been checked in the
	 * previous call to this function.
	 */
	if (idesc->id_loc % DIRBLKSIZ != 0 || dircheck(idesc, bp, dp) != 0) {
		/*
		 * Current entry is good, update to point at next.
		 */
		idesc->id_loc += dp->d_reclen;
		idesc->id_filesize -= dp->d_reclen;
		/*
		 * If at end of directory block, just return this entry.
		 */
		if (idesc->id_filesize <= 0 || idesc->id_loc >= blksiz ||
		    idesc->id_loc % DIRBLKSIZ == 0)
			return (dp);
		/*
		 * If the next entry good, return this entry.
		 */
		ndp = (struct direct *)(bp->b_un.b_buf + idesc->id_loc);
		if (dircheck(idesc, bp, ndp) != 0)
			return (dp);
		/*
		 * The next entry is bad, so subsume it and the remainder
		 * of this directory block into this entry.
		 */
		subsume_ndp = 1;
	}
	/*
	 * Current or next entry is bad. Zap current entry or
	 * subsume next entry into current entry as appropriate.
	 */
	size = DIRBLKSIZ - (idesc->id_loc % DIRBLKSIZ);
	idesc->id_loc += size;
	idesc->id_filesize -= size;
	if (idesc->id_fix == IGNORE)
		return (NULL);
	if (subsume_ndp) {
		memset(ndp, 0, size);
		dp->d_reclen += size;
	} else {
		memset(dp, 0, size);
		dp->d_reclen = size;
	}
	if (dofix(idesc, "DIRECTORY CORRUPTED"))
		dirty(bp);
	return (dp);
}