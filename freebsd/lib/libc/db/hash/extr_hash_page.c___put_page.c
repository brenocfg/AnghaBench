#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int ssize_t ;
typedef  int off_t ;
struct TYPE_4__ {int BSIZE; int fp; scalar_t__ LORDER; int BSHIFT; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int BUCKET_TO_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ BYTE_ORDER ; 
 int /*<<< orphan*/  EFTYPE ; 
 int MAX_BSIZE ; 
 int /*<<< orphan*/  M_16_SWAP (int) ; 
 int /*<<< orphan*/  M_32_SWAP (int) ; 
 int OADDR_TO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ open_temp (TYPE_1__*) ; 
 int pwrite (int,char*,int,int) ; 

int
__put_page(HTAB *hashp, char *p, u_int32_t bucket, int is_bucket, int is_bitmap)
{
	int fd, page, size;
	ssize_t wsize;
	char pbuf[MAX_BSIZE];

	size = hashp->BSIZE;
	if ((hashp->fp == -1) && open_temp(hashp))
		return (-1);
	fd = hashp->fp;

	if (hashp->LORDER != BYTE_ORDER) {
		int i, max;

		memcpy(pbuf, p, size);
		if (is_bitmap) {
			max = hashp->BSIZE >> 2;	/* divide by 4 */
			for (i = 0; i < max; i++)
				M_32_SWAP(((int *)pbuf)[i]);
		} else {
			uint16_t *bp = (uint16_t *)(void *)pbuf;
			max = bp[0] + 2;
			for (i = 0; i <= max; i++)
				M_16_SWAP(bp[i]);
		}
		p = pbuf;
	}
	if (is_bucket)
		page = BUCKET_TO_PAGE(bucket);
	else
		page = OADDR_TO_PAGE(bucket);
	if ((wsize = pwrite(fd, p, size, (off_t)page << hashp->BSHIFT)) == -1)
		/* Errno is set */
		return (-1);
	if (wsize != size) {
		errno = EFTYPE;
		return (-1);
	}
	return (0);
}