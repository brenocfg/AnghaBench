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
struct open_file {int /*<<< orphan*/  f_devdata; TYPE_1__* f_dev; scalar_t__ f_fsdata; } ;
struct file {size_t f_off; scalar_t__ f_bno; scalar_t__ f_buf_blkno; char* f_buf; size_t f_size; } ;
typedef  scalar_t__ daddr_t ;
struct TYPE_2__ {int (* dv_strategy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,size_t*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F_READ ; 
 size_t ISO_DEFAULT_BLOCK_SIZE ; 
 int /*<<< orphan*/  cdb2devb (scalar_t__) ; 
 char* malloc (size_t) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char*,size_t*) ; 
 int /*<<< orphan*/  twiddle (int) ; 

__attribute__((used)) static int
buf_read_file(struct open_file *f, char **buf_p, size_t *size_p)
{
	struct file *fp = (struct file *)f->f_fsdata;
	daddr_t blkno, blkoff;
	int rc = 0;
	size_t read;

	blkno = fp->f_off / ISO_DEFAULT_BLOCK_SIZE + fp->f_bno;
	blkoff = fp->f_off % ISO_DEFAULT_BLOCK_SIZE;

	if (blkno != fp->f_buf_blkno) {
		if (fp->f_buf == (char *)0)
			fp->f_buf = malloc(ISO_DEFAULT_BLOCK_SIZE);

		twiddle(16);
		rc = f->f_dev->dv_strategy(f->f_devdata, F_READ,
		    cdb2devb(blkno), ISO_DEFAULT_BLOCK_SIZE,
		    fp->f_buf, &read);
		if (rc)
			return (rc);
		if (read != ISO_DEFAULT_BLOCK_SIZE)
			return (EIO);

		fp->f_buf_blkno = blkno;
	}

	*buf_p = fp->f_buf + blkoff;
	*size_p = ISO_DEFAULT_BLOCK_SIZE - blkoff;

	if (*size_p > fp->f_size - fp->f_off)
		*size_p = fp->f_size - fp->f_off;
	return (rc);
}