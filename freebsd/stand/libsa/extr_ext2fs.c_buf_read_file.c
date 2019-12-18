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
struct open_file {int /*<<< orphan*/  f_devdata; TYPE_1__* f_dev; scalar_t__ f_fsdata; } ;
struct TYPE_4__ {size_t di_size; } ;
struct file {size_t f_seekp; scalar_t__ f_buf_blkno; char* f_buf; size_t f_buf_size; TYPE_2__ f_di; struct ext2fs* f_fs; } ;
struct ext2fs {int /*<<< orphan*/  fs_bsize; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_3__ {int (* dv_strategy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  F_READ ; 
 long blkoff (struct ext2fs*,size_t) ; 
 int block_map (struct open_file*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 size_t dblksize (struct ext2fs*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  fsb_to_db (struct ext2fs*,scalar_t__) ; 
 scalar_t__ lblkno (struct ext2fs*,size_t) ; 
 char* malloc (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,size_t*) ; 
 int /*<<< orphan*/  twiddle (int) ; 

__attribute__((used)) static int
buf_read_file(struct open_file *f, char **buf_p, size_t *size_p)
{
	struct file *fp = (struct file *)f->f_fsdata;
	struct ext2fs *fs = fp->f_fs;
	long off;
	daddr_t file_block;
	daddr_t	disk_block;
	size_t block_size;
	int error = 0;

	off = blkoff(fs, fp->f_seekp);
	file_block = lblkno(fs, fp->f_seekp);
	block_size = dblksize(fs, &fp->f_di, file_block);

	if (file_block != fp->f_buf_blkno) {
		error = block_map(f, file_block, &disk_block);
		if (error)
			goto done;

		if (fp->f_buf == (char *)0)
			fp->f_buf = malloc(fs->fs_bsize);

		if (disk_block == 0) {
			bzero(fp->f_buf, block_size);
			fp->f_buf_size = block_size;
		} else {
			twiddle(4);
			error = (f->f_dev->dv_strategy)(f->f_devdata, F_READ,
			    fsb_to_db(fs, disk_block), block_size,
			    fp->f_buf, &fp->f_buf_size);
			if (error)
				goto done;
		}
		fp->f_buf_blkno = file_block;
	}

	/*
	 * Return address of byte in buffer corresponding to
	 * offset, and size of remainder of buffer after that
	 * byte.
	 */
	*buf_p = fp->f_buf + off;
	*size_p = block_size - off;

	/*
	 * But truncate buffer at end of file.
	 */
	if (*size_p > fp->f_di.di_size - fp->f_seekp)
		*size_p = fp->f_di.di_size - fp->f_seekp;
done:
	return (error);
}