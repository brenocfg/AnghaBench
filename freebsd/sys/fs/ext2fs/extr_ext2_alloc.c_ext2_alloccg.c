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
typedef  int uint64_t ;
struct m_ext2fs {int e2fs_fmod; TYPE_1__* e2fs; int /*<<< orphan*/ * e2fs_gd; int /*<<< orphan*/  e2fs_fbcount; int /*<<< orphan*/  e2fs_fsmnt; scalar_t__ e2fs_bsize; } ;
struct inode {int /*<<< orphan*/  i_devvp; struct ext2mount* i_ump; struct m_ext2fs* i_e2fs; } ;
struct ext2mount {int dummy; } ;
struct buf {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int daddr_t ;
struct TYPE_2__ {int e2fs_fpg; int e2fs_first_dblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXT2F_ROCOMPAT_GDT_CSUM ; 
 int /*<<< orphan*/  EXT2F_ROCOMPAT_METADATA_CKSUM ; 
 scalar_t__ EXT2_HAS_RO_COMPAT_FEATURE (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXT2_LOCK (struct ext2mount*) ; 
 int /*<<< orphan*/  EXT2_UNLOCK (struct ext2mount*) ; 
 int NBBY ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct buf**) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 int dtog (struct m_ext2fs*,int) ; 
 int dtogd (struct m_ext2fs*,int) ; 
 int /*<<< orphan*/  e2fs_gd_get_b_bitmap (int /*<<< orphan*/ *) ; 
 scalar_t__ e2fs_gd_get_nbfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e2fs_gd_set_nbfree (int /*<<< orphan*/ *,scalar_t__) ; 
 int ext2_b_bitmap_validate (struct m_ext2fs*,struct buf*,int) ; 
 int ext2_cg_block_bitmap_init (struct m_ext2fs*,int,struct buf*) ; 
 int /*<<< orphan*/  ext2_clusteracct (struct m_ext2fs*,char*,int,int,int) ; 
 int /*<<< orphan*/  ext2_gd_b_bitmap_csum_set (struct m_ext2fs*,int,struct buf*) ; 
 int ext2_gd_b_bitmap_csum_verify (struct m_ext2fs*,int,struct buf*) ; 
 int ext2_mapsearch (struct m_ext2fs*,char*,int) ; 
 int ffs (char) ; 
 int fls (char) ; 
 int /*<<< orphan*/  fsbtodb (struct m_ext2fs*,int /*<<< orphan*/ ) ; 
 int howmany (int,int) ; 
 scalar_t__ isclr (char*,int) ; 
 scalar_t__ isset (char*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setbit (char*,int) ; 

__attribute__((used)) static daddr_t
ext2_alloccg(struct inode *ip, int cg, daddr_t bpref, int size)
{
	struct m_ext2fs *fs;
	struct buf *bp;
	struct ext2mount *ump;
	daddr_t bno, runstart, runlen;
	int bit, loc, end, error, start;
	char *bbp;
	/* XXX ondisk32 */
	fs = ip->i_e2fs;
	ump = ip->i_ump;
	if (e2fs_gd_get_nbfree(&fs->e2fs_gd[cg]) == 0)
		return (0);

	EXT2_UNLOCK(ump);
	error = bread(ip->i_devvp, fsbtodb(fs,
	    e2fs_gd_get_b_bitmap(&fs->e2fs_gd[cg])),
	    (int)fs->e2fs_bsize, NOCRED, &bp);
	if (error)
		goto fail;

	if (EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_GDT_CSUM) ||
	    EXT2_HAS_RO_COMPAT_FEATURE(fs, EXT2F_ROCOMPAT_METADATA_CKSUM)) {
		error = ext2_cg_block_bitmap_init(fs, cg, bp);
		if (error)
			goto fail;

		ext2_gd_b_bitmap_csum_set(fs, cg, bp);
	}
	error = ext2_gd_b_bitmap_csum_verify(fs, cg, bp);
	if (error)
		goto fail;

	error = ext2_b_bitmap_validate(fs,bp, cg);
	if (error)
		goto fail;

	/*
	 * Check, that another thread did not not allocate the last block in this
	 * group while we were waiting for the buffer.
	 */
	if (e2fs_gd_get_nbfree(&fs->e2fs_gd[cg]) == 0)
		goto fail;

	bbp = (char *)bp->b_data;

	if (dtog(fs, bpref) != cg)
		bpref = 0;
	if (bpref != 0) {
		bpref = dtogd(fs, bpref);
		/*
		 * if the requested block is available, use it
		 */
		if (isclr(bbp, bpref)) {
			bno = bpref;
			goto gotit;
		}
	}
	/*
	 * no blocks in the requested cylinder, so take next
	 * available one in this cylinder group.
	 * first try to get 8 contigous blocks, then fall back to a single
	 * block.
	 */
	if (bpref)
		start = dtogd(fs, bpref) / NBBY;
	else
		start = 0;
	end = howmany(fs->e2fs->e2fs_fpg, NBBY) - start;
retry:
	runlen = 0;
	runstart = 0;
	for (loc = start; loc < end; loc++) {
		if (bbp[loc] == (char)0xff) {
			runlen = 0;
			continue;
		}

		/* Start of a run, find the number of high clear bits. */
		if (runlen == 0) {
			bit = fls(bbp[loc]);
			runlen = NBBY - bit;
			runstart = loc * NBBY + bit;
		} else if (bbp[loc] == 0) {
			/* Continue a run. */
			runlen += NBBY;
		} else {
			/*
			 * Finish the current run.  If it isn't long
			 * enough, start a new one.
			 */
			bit = ffs(bbp[loc]) - 1;
			runlen += bit;
			if (runlen >= 8) {
				bno = runstart;
				goto gotit;
			}

			/* Run was too short, start a new one. */
			bit = fls(bbp[loc]);
			runlen = NBBY - bit;
			runstart = loc * NBBY + bit;
		}

		/* If the current run is long enough, use it. */
		if (runlen >= 8) {
			bno = runstart;
			goto gotit;
		}
	}
	if (start != 0) {
		end = start;
		start = 0;
		goto retry;
	}
	bno = ext2_mapsearch(fs, bbp, bpref);
	if (bno < 0)
		goto fail;

gotit:
#ifdef INVARIANTS
	if (isset(bbp, bno)) {
		printf("ext2fs_alloccgblk: cg=%d bno=%jd fs=%s\n",
		    cg, (intmax_t)bno, fs->e2fs_fsmnt);
		panic("ext2fs_alloccg: dup alloc");
	}
#endif
	setbit(bbp, bno);
	EXT2_LOCK(ump);
	ext2_clusteracct(fs, bbp, cg, bno, -1);
	fs->e2fs_fbcount--;
	e2fs_gd_set_nbfree(&fs->e2fs_gd[cg],
	    e2fs_gd_get_nbfree(&fs->e2fs_gd[cg]) - 1);
	fs->e2fs_fmod = 1;
	EXT2_UNLOCK(ump);
	ext2_gd_b_bitmap_csum_set(fs, cg, bp);
	bdwrite(bp);
	return (((uint64_t)cg) * fs->e2fs->e2fs_fpg + fs->e2fs->e2fs_first_dblock + bno);

fail:
	brelse(bp);
	EXT2_LOCK(ump);
	return (0);
}