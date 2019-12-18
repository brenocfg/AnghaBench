#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t ufs_lbn_t ;
typedef  scalar_t__ ufs2_daddr_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ino_t ;
struct TYPE_10__ {int fs_frag; int fs_fsize; scalar_t__ fs_maxsymlinklen; } ;

/* Variables and functions */
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,scalar_t__) ; 
 int IFBLK ; 
 int IFCHR ; 
 scalar_t__ IFDIR ; 
 int IFLNK ; 
 scalar_t__ IFMT ; 
 size_t NINDIR (TYPE_1__*) ; 
 size_t UFS_NDADDR ; 
 size_t UFS_NIADDR ; 
 int VISIT_EXT ; 
 int VISIT_INDIR ; 
 int /*<<< orphan*/  blk_free (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ blkoff (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  blkroundup (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  dblk_dirty (scalar_t__) ; 
 int /*<<< orphan*/ * dblk_read (scalar_t__,long) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_blocks ; 
 int /*<<< orphan*/ * di_db ; 
 int /*<<< orphan*/ * di_ib ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_size ; 
 int /*<<< orphan*/  err_suj (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* fs ; 
 scalar_t__ fsbtodb (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  indir_trunc (scalar_t__,size_t,scalar_t__,size_t) ; 
 scalar_t__ ino_blkatoff (union dinode*,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  ino_dirty (scalar_t__) ; 
 union dinode* ino_read (scalar_t__) ; 
 scalar_t__ ino_visit (union dinode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 size_t lblkno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lblktosize (TYPE_1__*,int) ; 
 int /*<<< orphan*/  null_visit ; 
 scalar_t__ numfrags (TYPE_1__*,long) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 void* sblksize (TYPE_1__*,scalar_t__,int) ; 
 int visitlbn ; 

__attribute__((used)) static void
ino_trunc(ino_t ino, off_t size)
{
	union dinode *ip;
	ufs2_daddr_t bn;
	uint64_t totalfrags;
	ufs_lbn_t nextlbn;
	ufs_lbn_t lastlbn;
	ufs_lbn_t tmpval;
	ufs_lbn_t lbn;
	ufs_lbn_t i;
	int frags;
	off_t cursize;
	off_t off;
	int mode;

	ip = ino_read(ino);
	mode = DIP(ip, di_mode) & IFMT;
	cursize = DIP(ip, di_size);
	if (debug)
		printf("Truncating ino %ju, mode %o to size %jd from size %jd\n",
		    (uintmax_t)ino, mode, size, cursize);

	/* Skip datablocks for short links and devices. */
	if (mode == 0 || mode == IFBLK || mode == IFCHR ||
	    (mode == IFLNK && cursize < fs->fs_maxsymlinklen))
		return;
	/* Don't extend. */
	if (size > cursize)
		size = cursize;
	lastlbn = lblkno(fs, blkroundup(fs, size));
	for (i = lastlbn; i < UFS_NDADDR; i++) {
		if (DIP(ip, di_db[i]) == 0)
			continue;
		frags = sblksize(fs, cursize, i);
		frags = numfrags(fs, frags);
		blk_free(DIP(ip, di_db[i]), 0, frags);
		DIP_SET(ip, di_db[i], 0);
	}
	/*
	 * Follow indirect blocks, freeing anything required.
	 */
	for (i = 0, tmpval = NINDIR(fs), lbn = UFS_NDADDR; i < UFS_NIADDR; i++,
	    lbn = nextlbn) {
		nextlbn = lbn + tmpval;
		tmpval *= NINDIR(fs);
		/* If we're not freeing any in this indirect range skip it. */
		if (lastlbn >= nextlbn)
			continue;
		if (DIP(ip, di_ib[i]) == 0)
			continue;
		indir_trunc(ino, -lbn - i, DIP(ip, di_ib[i]), lastlbn);
		/* If we freed everything in this indirect free the indir. */
		if (lastlbn > lbn)
			continue;
		blk_free(DIP(ip, di_ib[i]), 0, fs->fs_frag);
		DIP_SET(ip, di_ib[i], 0);
	}
	ino_dirty(ino);
	/*
	 * Now that we've freed any whole blocks that exceed the desired
	 * truncation size, figure out how many blocks remain and what the
	 * last populated lbn is.  We will set the size to this last lbn
	 * rather than worrying about allocating the final lbn as the kernel
	 * would've done.  This is consistent with normal fsck behavior.
	 */
	visitlbn = 0;
	totalfrags = ino_visit(ip, ino, null_visit, VISIT_INDIR | VISIT_EXT);
	if (size > lblktosize(fs, visitlbn + 1))
		size = lblktosize(fs, visitlbn + 1);
	/*
	 * If we're truncating direct blocks we have to adjust frags
	 * accordingly.
	 */
	if (visitlbn < UFS_NDADDR && totalfrags) {
		long oldspace, newspace;

		bn = DIP(ip, di_db[visitlbn]);
		if (bn == 0)
			err_suj("Bad blk at ino %ju lbn %jd\n",
			    (uintmax_t)ino, visitlbn);
		oldspace = sblksize(fs, cursize, visitlbn);
		newspace = sblksize(fs, size, visitlbn);
		if (oldspace != newspace) {
			bn += numfrags(fs, newspace);
			frags = numfrags(fs, oldspace - newspace);
			blk_free(bn, 0, frags);
			totalfrags -= frags;
		}
	}
	DIP_SET(ip, di_blocks, fsbtodb(fs, totalfrags));
	DIP_SET(ip, di_size, size);
	/*
	 * If we've truncated into the middle of a block or frag we have
	 * to zero it here.  Otherwise the file could extend into
	 * uninitialized space later.
	 */
	off = blkoff(fs, size);
	if (off && DIP(ip, di_mode) != IFDIR) {
		uint8_t *buf;
		long clrsize;

		bn = ino_blkatoff(ip, ino, visitlbn, &frags);
		if (bn == 0)
			err_suj("Block missing from ino %ju at lbn %jd\n",
			    (uintmax_t)ino, visitlbn);
		clrsize = frags * fs->fs_fsize;
		buf = dblk_read(bn, clrsize);
		clrsize -= off;
		buf += off;
		bzero(buf, clrsize);
		dblk_dirty(bn);
	}
	return;
}