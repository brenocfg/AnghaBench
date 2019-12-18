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
typedef  int /*<<< orphan*/  vdev_t ;
struct TYPE_3__ {scalar_t__ start; } ;
struct zfsdsk {TYPE_1__ dsk; } ;
typedef  int off_t ;
typedef  unsigned int daddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  rdbuf; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int READ_BUF_SIZE ; 
 TYPE_2__* dmadat ; 
 scalar_t__ drvwrite (TYPE_1__*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int
vdev_write(vdev_t *vdev, void *priv, off_t off, void *buf, size_t bytes)
{
	char *p;
	daddr_t lba;
	unsigned int nb;
	struct zfsdsk *zdsk = (struct zfsdsk *) priv;

	if ((off & (DEV_BSIZE - 1)) || (bytes & (DEV_BSIZE - 1)))
		return -1;

	p = buf;
	lba = off / DEV_BSIZE;
	lba += zdsk->dsk.start;
	while (bytes > 0) {
		nb = bytes / DEV_BSIZE;
		if (nb > READ_BUF_SIZE / DEV_BSIZE)
			nb = READ_BUF_SIZE / DEV_BSIZE;
		memcpy(dmadat->rdbuf, p, nb * DEV_BSIZE);
		if (drvwrite(&zdsk->dsk, dmadat->rdbuf, lba, nb))
			return -1;
		p += nb * DEV_BSIZE;
		lba += nb;
		bytes -= nb * DEV_BSIZE;
	}

	return 0;
}