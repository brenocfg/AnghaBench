#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int u_int16_t ;
typedef  int off_t ;
struct TYPE_3__ {int fp; int BSIZE; int BSHIFT; scalar_t__ LORDER; } ;
typedef  TYPE_1__ HTAB ;

/* Variables and functions */
 int BUCKET_TO_PAGE (int /*<<< orphan*/ ) ; 
 scalar_t__ BYTE_ORDER ; 
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  M_16_SWAP (int) ; 
 int /*<<< orphan*/  M_32_SWAP (int) ; 
 int OADDR_TO_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_INIT (char*) ; 
 int /*<<< orphan*/  errno ; 
 int pread (int,char*,int,int) ; 

int
__get_page(HTAB *hashp, char *p, u_int32_t bucket, int is_bucket, int is_disk,
    int is_bitmap)
{
	int fd, page, size, rsize;
	u_int16_t *bp;

	fd = hashp->fp;
	size = hashp->BSIZE;

	if ((fd == -1) || !is_disk) {
		PAGE_INIT(p);
		return (0);
	}
	if (is_bucket)
		page = BUCKET_TO_PAGE(bucket);
	else
		page = OADDR_TO_PAGE(bucket);
	if ((rsize = pread(fd, p, size, (off_t)page << hashp->BSHIFT)) == -1)
		return (-1);
	bp = (u_int16_t *)p;
	if (!rsize)
		bp[0] = 0;	/* We hit the EOF, so initialize a new page */
	else
		if (rsize != size) {
			errno = EFTYPE;
			return (-1);
		}
	if (!is_bitmap && !bp[0]) {
		PAGE_INIT(p);
	} else
		if (hashp->LORDER != BYTE_ORDER) {
			int i, max;

			if (is_bitmap) {
				max = hashp->BSIZE >> 2; /* divide by 4 */
				for (i = 0; i < max; i++)
					M_32_SWAP(((int *)p)[i]);
			} else {
				M_16_SWAP(bp[0]);
				max = bp[0] + 2;
				for (i = 1; i <= max; i++)
					M_16_SWAP(bp[i]);
			}
		}
	return (0);
}