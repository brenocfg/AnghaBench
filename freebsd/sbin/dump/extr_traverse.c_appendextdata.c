#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * di_extb; } ;
union dinode {TYPE_1__ dp2; } ;
struct TYPE_6__ {int fs_bsize; } ;
struct TYPE_5__ {int c_extsize; int c_count; int* c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  TP_BSIZE ; 
 int TP_NINDIR ; 
 int UFS_NXADDR ; 
 int /*<<< orphan*/  assert (int) ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* sblock ; 
 TYPE_2__ spcl ; 
 int tp_bshift ; 

__attribute__((used)) static int
appendextdata(union dinode *dp)
{
	int i, blks, tbperdb;

	/*
	 * If no extended attributes, there is nothing to do.
	 */
	if (spcl.c_extsize == 0)
		return (0);
	/*
	 * If there is not enough room at the end of this block
	 * to add the extended attributes, then rather than putting
	 * part of them here, we simply push them entirely into a
	 * new block rather than putting some here and some later.
	 */
	if (spcl.c_extsize > UFS_NXADDR * sblock->fs_bsize)
		blks = howmany(UFS_NXADDR * sblock->fs_bsize, TP_BSIZE);
	else
		blks = howmany(spcl.c_extsize, TP_BSIZE);
	if (spcl.c_count + blks > TP_NINDIR)
		return (0);
	/*
	 * Update the block map in the header to indicate the added
	 * extended attribute. They will be appended after the file
	 * data by the writeextdata() routine.
	 */
	tbperdb = sblock->fs_bsize >> tp_bshift;
	assert(spcl.c_count + blks < TP_NINDIR);
	for (i = 0; i < blks; i++)
		if (&dp->dp2.di_extb[i / tbperdb] != 0)
				spcl.c_addr[spcl.c_count + i] = 1;
			else
				spcl.c_addr[spcl.c_count + i] = 0;
	spcl.c_count += blks;
	return (blks);
}