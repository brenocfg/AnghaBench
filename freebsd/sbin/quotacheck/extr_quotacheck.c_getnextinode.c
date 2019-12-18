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
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct ufs2_dinode {int dummy; } ;
struct ufs1_dinode {int dummy; } ;
typedef  scalar_t__ ino_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_4__ {scalar_t__ fs_magic; } ;

/* Variables and functions */
 scalar_t__ FS_UFS1_MAGIC ; 
 int /*<<< orphan*/  blkread (int /*<<< orphan*/ ,scalar_t__,long) ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ fullcnt ; 
 int /*<<< orphan*/  ino_to_fsba (TYPE_1__*,scalar_t__) ; 
 long inobufsize ; 
 scalar_t__ inodebuf ; 
 scalar_t__ lastinum ; 
 scalar_t__ lastvalidinum ; 
 int /*<<< orphan*/  nextino ; 
 scalar_t__ partialcnt ; 
 long partialsize ; 
 int readcnt ; 
 int readpercg ; 
 TYPE_1__ sblock ; 

union dinode *
getnextinode(ino_t inumber)
{
	long size;
	ufs2_daddr_t dblk;
	union dinode *dp;
	static caddr_t nextinop;

	if (inumber != nextino++ || inumber > lastvalidinum)
		errx(1, "bad inode number %ju to nextinode",
		    (uintmax_t)inumber);
	if (inumber >= lastinum) {
		readcnt++;
		dblk = fsbtodb(&sblock, ino_to_fsba(&sblock, lastinum));
		if (readcnt % readpercg == 0) {
			size = partialsize;
			lastinum += partialcnt;
		} else {
			size = inobufsize;
			lastinum += fullcnt;
		}
		/*
		 * If blkread returns an error, it will already have zeroed
		 * out the buffer, so we do not need to do so here.
		 */
		blkread(dblk, inodebuf, size);
		nextinop = inodebuf;
	}
	dp = (union dinode *)nextinop;
	if (sblock.fs_magic == FS_UFS1_MAGIC)
		nextinop += sizeof(struct ufs1_dinode);
	else
		nextinop += sizeof(struct ufs2_dinode);
	return (dp);
}