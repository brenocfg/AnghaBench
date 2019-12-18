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
struct TYPE_3__ {int start; int size; } ;
struct zfsdsk {TYPE_1__ dsk; int /*<<< orphan*/ * gdev; } ;
typedef  int off_t ;
typedef  int daddr_t ;
struct TYPE_4__ {scalar_t__ rdbuf; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int /*<<< orphan*/  DEV_GELIBOOT_BSIZE ; 
 int READ_BUF_SIZE ; 
 TYPE_2__* dmadat ; 
 scalar_t__ drvread (TYPE_1__*,scalar_t__,int,unsigned int) ; 
 scalar_t__ geli_read (int /*<<< orphan*/ *,int,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int,int) ; 
 int rounddown2 (int,int /*<<< orphan*/ ) ; 
 int roundup2 (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vdev_read(void *xvdev, void *priv, off_t off, void *buf, size_t bytes)
{
	char *p;
	daddr_t lba, alignlba;
	off_t diff;
	unsigned int nb, alignnb;
	struct zfsdsk *zdsk = (struct zfsdsk *) priv;

	if ((off & (DEV_BSIZE - 1)) || (bytes & (DEV_BSIZE - 1)))
		return -1;

	p = buf;
	lba = off / DEV_BSIZE;
	lba += zdsk->dsk.start;
	/*
	 * Align reads to 4k else 4k sector GELIs will not decrypt.
	 * Round LBA down to nearest multiple of DEV_GELIBOOT_BSIZE bytes.
	 */
	alignlba = rounddown2(off, DEV_GELIBOOT_BSIZE) / DEV_BSIZE;
	/*
	 * The read must be aligned to DEV_GELIBOOT_BSIZE bytes relative to the
	 * start of the GELI partition, not the start of the actual disk.
	 */
	alignlba += zdsk->dsk.start;
	diff = (lba - alignlba) * DEV_BSIZE;

	while (bytes > 0) {
		nb = bytes / DEV_BSIZE;
		/*
		 * Ensure that the read size plus the leading offset does not
		 * exceed the size of the read buffer.
		 */
		if (nb > (READ_BUF_SIZE - diff) / DEV_BSIZE)
			nb = (READ_BUF_SIZE - diff) / DEV_BSIZE;
		/*
		 * Round the number of blocks to read up to the nearest multiple
		 * of DEV_GELIBOOT_BSIZE.
		 */
		alignnb = roundup2(nb * DEV_BSIZE + diff, DEV_GELIBOOT_BSIZE)
		    / DEV_BSIZE;

		if (zdsk->dsk.size > 0 && alignlba + alignnb >
		    zdsk->dsk.size + zdsk->dsk.start) {
			printf("Shortening read at %lld from %d to %lld\n",
			    alignlba, alignnb,
			    (zdsk->dsk.size + zdsk->dsk.start) - alignlba);
			alignnb = (zdsk->dsk.size + zdsk->dsk.start) - alignlba;
		}

		if (drvread(&zdsk->dsk, dmadat->rdbuf, alignlba, alignnb))
			return -1;
#ifdef LOADER_GELI_SUPPORT
		/* decrypt */
		if (zdsk->gdev != NULL) {
			if (geli_read(zdsk->gdev, ((alignlba - zdsk->dsk.start) *
			    DEV_BSIZE), dmadat->rdbuf, alignnb * DEV_BSIZE))
				return (-1);
		}
#endif
		memcpy(p, dmadat->rdbuf + diff, nb * DEV_BSIZE);
		p += nb * DEV_BSIZE;
		lba += nb;
		alignlba += alignnb;
		bytes -= nb * DEV_BSIZE;
		/* Don't need the leading offset after the first block. */
		diff = 0;
	}

	return 0;
}