#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mapinfo {int maplen; int mapoff; int maxoff; int /*<<< orphan*/  fd; int /*<<< orphan*/ * start; } ;
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int TAILMAPLEN ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ munmap (int /*<<< orphan*/ *,int) ; 

int
maparound(struct mapinfo *mip, off_t offset)
{

	if (mip->start != NULL && munmap(mip->start, mip->maplen) != 0)
		return (1);

	mip->mapoff = offset & ~((off_t)TAILMAPLEN - 1);
	mip->maplen = TAILMAPLEN;
	if ((off_t)mip->maplen > mip->maxoff - mip->mapoff)
		mip->maplen = mip->maxoff - mip->mapoff;
	if (mip->maplen <= 0)
		abort();
	if ((mip->start = mmap(NULL, mip->maplen, PROT_READ, MAP_SHARED,
	     mip->fd, mip->mapoff)) == MAP_FAILED)
		return (1);

	return (0);
}