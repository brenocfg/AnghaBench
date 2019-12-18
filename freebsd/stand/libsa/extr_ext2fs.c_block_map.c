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
struct open_file {int /*<<< orphan*/  f_devdata; TYPE_2__* f_dev; scalar_t__ f_fsdata; } ;
struct TYPE_3__ {size_t* di_db; size_t* di_ib; } ;
struct file {size_t* f_nindir; size_t* f_blkno; char** f_blk; scalar_t__* f_blksize; struct ext2fs* f_fs; TYPE_1__ f_di; } ;
struct ext2fs {scalar_t__ fs_bsize; } ;
typedef  size_t int32_t ;
typedef  size_t daddr_t ;
struct TYPE_4__ {int (* dv_strategy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*) ;} ;

/* Variables and functions */
 int EFBIG ; 
 int EIO ; 
 size_t EXT2_NDADDR ; 
 int EXT2_NIADDR ; 
 int /*<<< orphan*/  F_READ ; 
 int /*<<< orphan*/  fsb_to_db (struct ext2fs*,size_t) ; 
 char* malloc (scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,scalar_t__*) ; 
 int /*<<< orphan*/  twiddle (int) ; 

__attribute__((used)) static int
block_map(struct open_file *f, daddr_t file_block, daddr_t *disk_block_p)
{
	struct file *fp = (struct file *)f->f_fsdata;
	struct ext2fs *fs = fp->f_fs;
	daddr_t ind_block_num;
	int32_t *ind_p;
	int idx, level;
	int error;

	/*
	 * Index structure of an inode:
	 *
	 * di_db[0..EXT2_NDADDR-1] hold block numbers for blocks
	 *			0..EXT2_NDADDR-1
	 *
	 * di_ib[0]		index block 0 is the single indirect block
	 *			holds block numbers for blocks
	 *			EXT2_NDADDR .. EXT2_NDADDR + NINDIR(fs)-1
	 *
	 * di_ib[1]		index block 1 is the double indirect block
	 *			holds block numbers for INDEX blocks for blocks
	 *			EXT2_NDADDR + NINDIR(fs) ..
	 *			EXT2_NDADDR + NINDIR(fs) + NINDIR(fs)**2 - 1
	 *
	 * di_ib[2]		index block 2 is the triple indirect block
	 *			holds block numbers for double-indirect
	 *			blocks for blocks
	 *			EXT2_NDADDR + NINDIR(fs) + NINDIR(fs)**2 ..
	 *			EXT2_NDADDR + NINDIR(fs) + NINDIR(fs)**2
	 *				+ NINDIR(fs)**3 - 1
	 */

	if (file_block < EXT2_NDADDR) {
		/* Direct block. */
		*disk_block_p = fp->f_di.di_db[file_block];
		return (0);
	}

	file_block -= EXT2_NDADDR;

	/*
	 * nindir[0] = NINDIR
	 * nindir[1] = NINDIR**2
	 * nindir[2] = NINDIR**3
	 *	etc
	 */
	for (level = 0; level < EXT2_NIADDR; level++) {
		if (file_block < fp->f_nindir[level])
			break;
		file_block -= fp->f_nindir[level];
	}
	if (level == EXT2_NIADDR) {
		/* Block number too high */
		return (EFBIG);
	}

	ind_block_num = fp->f_di.di_ib[level];

	for (; level >= 0; level--) {
		if (ind_block_num == 0) {
			*disk_block_p = 0;	/* missing */
			return (0);
		}

		if (fp->f_blkno[level] != ind_block_num) {
			if (fp->f_blk[level] == (char *)0)
				fp->f_blk[level] =
					malloc(fs->fs_bsize);
			twiddle(1);
			error = (f->f_dev->dv_strategy)(f->f_devdata, F_READ,
			    fsb_to_db(fp->f_fs, ind_block_num), fs->fs_bsize,
			    fp->f_blk[level], &fp->f_blksize[level]);
			if (error)
				return (error);
			if (fp->f_blksize[level] != fs->fs_bsize)
				return (EIO);
			fp->f_blkno[level] = ind_block_num;
		}

		ind_p = (int32_t *)fp->f_blk[level];

		if (level > 0) {
			idx = file_block / fp->f_nindir[level - 1];
			file_block %= fp->f_nindir[level - 1];
		} else {
			idx = file_block;
		}
		ind_block_num = ind_p[idx];
	}

	*disk_block_p = ind_block_num;

	return (0);
}