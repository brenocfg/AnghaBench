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
struct promise_raid_conf {int disk_offset; int disk_sectors; scalar_t__ disk_sectors_high; scalar_t__ disk_offset_high; } ;
typedef  int off_t ;

/* Variables and functions */
 int MIN (int,int) ; 

__attribute__((used)) static int
promise_meta_unused_range(struct promise_raid_conf **metaarr, int nsd,
    off_t sectors, off_t *off, off_t *size)
{
	off_t coff, csize, tmp;
	int i, j;

	sectors -= 131072;
	*off = 0;
	*size = 0;
	coff = 0;
	csize = sectors;
	i = 0;
	while (1) {
		for (j = 0; j < nsd; j++) {
			tmp = ((off_t)metaarr[j]->disk_offset_high << 32) +
			    metaarr[j]->disk_offset;
			if (tmp >= coff)
				csize = MIN(csize, tmp - coff);
		}
		if (csize > *size) {
			*off = coff;
			*size = csize;
		}
		if (i >= nsd)
			break;
		coff = ((off_t)metaarr[i]->disk_offset_high << 32) +
		     metaarr[i]->disk_offset +
		    ((off_t)metaarr[i]->disk_sectors_high << 32) +
		     metaarr[i]->disk_sectors;
		csize = sectors - coff;
		i++;
	}
	return ((*size > 0) ? 1 : 0);
}