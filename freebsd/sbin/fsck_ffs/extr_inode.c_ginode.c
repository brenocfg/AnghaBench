#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct ufs2_dinode {int dummy; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_9__ {int /*<<< orphan*/ * b_dinode2; int /*<<< orphan*/ * b_dinode1; } ;
struct TYPE_11__ {TYPE_1__ b_un; int /*<<< orphan*/  b_flags; } ;
struct TYPE_10__ {scalar_t__ fs_magic; int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_INODES ; 
 int /*<<< orphan*/  B_INUSE ; 
 int /*<<< orphan*/  EEXIT ; 
 scalar_t__ FS_UFS1_MAGIC ; 
 scalar_t__ INOPB (TYPE_2__*) ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_update_dinode_ckhash (TYPE_2__*,struct ufs2_dinode*) ; 
 scalar_t__ ffs_verify_dinode_ckhash (TYPE_2__*,struct ufs2_dinode*) ; 
 TYPE_3__* getdatablk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ino_to_fsba (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 scalar_t__ maxino ; 
 TYPE_3__* pbp ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  prtinode (scalar_t__,union dinode*) ; 
 int /*<<< orphan*/  pwarn (char*) ; 
 scalar_t__ reply (char*) ; 
 scalar_t__ rounddown (scalar_t__,scalar_t__) ; 
 TYPE_2__ sblock ; 
 scalar_t__ startinum ; 

union dinode *
ginode(ino_t inumber)
{
	ufs2_daddr_t iblk;
	union dinode *dp;

	if (inumber < UFS_ROOTINO || inumber > maxino)
		errx(EEXIT, "bad inode number %ju to ginode",
		    (uintmax_t)inumber);
	if (startinum == 0 ||
	    inumber < startinum || inumber >= startinum + INOPB(&sblock)) {
		iblk = ino_to_fsba(&sblock, inumber);
		if (pbp != NULL)
			pbp->b_flags &= ~B_INUSE;
		pbp = getdatablk(iblk, sblock.fs_bsize, BT_INODES);
		startinum = rounddown(inumber, INOPB(&sblock));
	}
	if (sblock.fs_magic == FS_UFS1_MAGIC)
		return ((union dinode *)
		    &pbp->b_un.b_dinode1[inumber % INOPB(&sblock)]);
	dp = (union dinode *)&pbp->b_un.b_dinode2[inumber % INOPB(&sblock)];
	if (ffs_verify_dinode_ckhash(&sblock, (struct ufs2_dinode *)dp) != 0) {
		pwarn("INODE CHECK-HASH FAILED");
		prtinode(inumber, dp);
		if (preen || reply("FIX") != 0) {
			if (preen)
				printf(" (FIXED)\n");
			ffs_update_dinode_ckhash(&sblock,
			    (struct ufs2_dinode *)dp);
			inodirty(dp);
		}
	}
	return (dp);
}