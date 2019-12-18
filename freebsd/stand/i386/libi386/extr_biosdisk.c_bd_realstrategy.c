#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint64_t ;
struct TYPE_8__ {TYPE_1__* d_dev; } ;
struct disk_devdesc {size_t d_offset; TYPE_5__ dd; } ;
typedef  size_t daddr_t ;
typedef  char* caddr_t ;
struct TYPE_7__ {int bd_flags; size_t bd_sectorsize; size_t bd_sectors; } ;
typedef  TYPE_2__ bdinfo_t ;
struct TYPE_6__ {scalar_t__ dv_type; } ;

/* Variables and functions */
 int BD_NO_MEDIA ; 
 int /*<<< orphan*/  BD_RD ; 
 int /*<<< orphan*/  BD_WR ; 
 size_t BIOSDISK_SECSIZE ; 
 size_t BIO_BUFFER_SIZE ; 
 scalar_t__ DEVT_DISK ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int EIO ; 
 int EROFS ; 
 int F_MASK ; 
#define  F_READ 129 
#define  F_WRITE 128 
 size_t INT_MAX ; 
 char* PTOV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_IO_BUFFER ; 
 size_t V86_IO_BUFFER_SIZE ; 
 int /*<<< orphan*/  bcopy (char*,char*,size_t) ; 
 TYPE_2__* bd_get_bdinfo (TYPE_5__*) ; 
 int bd_io (struct disk_devdesc*,TYPE_2__*,size_t,int,char*,int /*<<< orphan*/ ) ; 
 char* bio_alloc (size_t) ; 
 int /*<<< orphan*/  bio_free (char*,size_t) ; 
 scalar_t__ disk_ioctl (struct disk_devdesc*,int /*<<< orphan*/ ,size_t*) ; 
 void* min (size_t,size_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,size_t,size_t) ; 

__attribute__((used)) static int
bd_realstrategy(void *devdata, int rw, daddr_t dblk, size_t size,
    char *buf, size_t *rsize)
{
	struct disk_devdesc *dev = (struct disk_devdesc *)devdata;
	bdinfo_t *bd;
	uint64_t disk_blocks, offset, d_offset;
	size_t blks, blkoff, bsize, bio_size, rest;
	caddr_t bbuf = NULL;
	int rc;

	bd = bd_get_bdinfo(&dev->dd);
	if (bd == NULL || (bd->bd_flags & BD_NO_MEDIA) == BD_NO_MEDIA)
		return (EIO);

	/*
	 * First make sure the IO size is a multiple of 512 bytes. While we do
	 * process partial reads below, the strategy mechanism is built
	 * assuming IO is a multiple of 512B blocks. If the request is not
	 * a multiple of 512B blocks, it has to be some sort of bug.
	 */
	if (size == 0 || (size % BIOSDISK_SECSIZE) != 0) {
		printf("bd_strategy: %d bytes I/O not multiple of %d\n",
		    size, BIOSDISK_SECSIZE);
		return (EIO);
	}

	DPRINTF("open_disk %p", dev);

	offset = dblk * BIOSDISK_SECSIZE;
	dblk = offset / bd->bd_sectorsize;
	blkoff = offset % bd->bd_sectorsize;

	/*
	 * Check the value of the size argument. We do have quite small
	 * heap (64MB), but we do not know good upper limit, so we check against
	 * INT_MAX here. This will also protect us against possible overflows
	 * while translating block count to bytes.
	 */
	if (size > INT_MAX) {
		DPRINTF("too large I/O: %zu bytes", size);
		return (EIO);
	}

	blks = size / bd->bd_sectorsize;
	if (blks == 0 || (size % bd->bd_sectorsize) != 0)
		blks++;

	if (dblk > dblk + blks)
		return (EIO);

	if (rsize)
		*rsize = 0;

	/*
	 * Get disk blocks, this value is either for whole disk or for
	 * partition.
	 */
	d_offset = 0;
	disk_blocks = 0;
	if (dev->dd.d_dev->dv_type == DEVT_DISK) {
		if (disk_ioctl(dev, DIOCGMEDIASIZE, &disk_blocks) == 0) {
			/* DIOCGMEDIASIZE does return bytes. */
			disk_blocks /= bd->bd_sectorsize;
		}
		d_offset = dev->d_offset;
	}
	if (disk_blocks == 0)
		disk_blocks = bd->bd_sectors - d_offset;

	/* Validate source block address. */
	if (dblk < d_offset || dblk >= d_offset + disk_blocks)
		return (EIO);

	/*
	 * Truncate if we are crossing disk or partition end.
	 */
	if (dblk + blks >= d_offset + disk_blocks) {
		blks = d_offset + disk_blocks - dblk;
		size = blks * bd->bd_sectorsize;
		DPRINTF("short I/O %d", blks);
	}

	bio_size = min(BIO_BUFFER_SIZE, size);
	while (bio_size > bd->bd_sectorsize) {
		bbuf = bio_alloc(bio_size);
		if (bbuf != NULL)
			break;
		bio_size -= bd->bd_sectorsize;
	}
	if (bbuf == NULL) {
		bio_size = V86_IO_BUFFER_SIZE;
		if (bio_size / bd->bd_sectorsize == 0)
			panic("BUG: Real mode buffer is too small");

		/* Use alternate 4k buffer */
		bbuf = PTOV(V86_IO_BUFFER);
	}
	rest = size;
	rc = 0;
	while (blks > 0) {
		int x = min(blks, bio_size / bd->bd_sectorsize);

		switch (rw & F_MASK) {
		case F_READ:
			DPRINTF("read %d from %lld to %p", x, dblk, buf);
			bsize = bd->bd_sectorsize * x - blkoff;
			if (rest < bsize)
				bsize = rest;

			if ((rc = bd_io(dev, bd, dblk, x, bbuf, BD_RD)) != 0) {
				rc = EIO;
				goto error;
			}

			bcopy(bbuf + blkoff, buf, bsize);
			break;
		case F_WRITE :
			DPRINTF("write %d from %lld to %p", x, dblk, buf);
			if (blkoff != 0) {
				/*
				 * We got offset to sector, read 1 sector to
				 * bbuf.
				 */
				x = 1;
				bsize = bd->bd_sectorsize - blkoff;
				bsize = min(bsize, rest);
				rc = bd_io(dev, bd, dblk, x, bbuf, BD_RD);
			} else if (rest < bd->bd_sectorsize) {
				/*
				 * The remaining block is not full
				 * sector. Read 1 sector to bbuf.
				 */
				x = 1;
				bsize = rest;
				rc = bd_io(dev, bd, dblk, x, bbuf, BD_RD);
			} else {
				/* We can write full sector(s). */
				bsize = bd->bd_sectorsize * x;
			}
			/*
			 * Put your Data In, Put your Data out,
			 * Put your Data In, and shake it all about
			 */
			bcopy(buf, bbuf + blkoff, bsize);
			if ((rc = bd_io(dev, bd, dblk, x, bbuf, BD_WR)) != 0) {
				rc = EIO;
				goto error;
			}

			break;
		default:
			/* DO NOTHING */
			rc = EROFS;
			goto error;
		}

		blkoff = 0;
		buf += bsize;
		rest -= bsize;
		blks -= x;
		dblk += x;
	}

	if (rsize != NULL)
		*rsize = size;
error:
	if (bbuf != PTOV(V86_IO_BUFFER))
		bio_free(bbuf, bio_size);
	return (rc);
}