#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint32_t ;
struct ufs2_dinode {int dummy; } ;
struct ufs1_dinode {int dummy; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_2__ {scalar_t__ fs_magic; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ FS_UFS1_MAGIC ; 
 int IFDIR ; 
 int IFMT ; 
 scalar_t__ UFS_ROOTINO ; 
 int VISIT_EXT ; 
 int VISIT_INDIR ; 
 int /*<<< orphan*/  blk_free_visit ; 
 int /*<<< orphan*/  bzero (union dinode*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_gen ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 int /*<<< orphan*/  err_suj (char*) ; 
 TYPE_1__* fs ; 
 int /*<<< orphan*/  ino_dirty (scalar_t__) ; 
 int /*<<< orphan*/  ino_free (scalar_t__,int) ; 
 int /*<<< orphan*/  ino_free_children ; 
 int /*<<< orphan*/  ino_visit (union dinode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ino_reclaim(union dinode *ip, ino_t ino, int mode)
{
	uint32_t gen;

	if (ino == UFS_ROOTINO)
		err_suj("Attempting to free UFS_ROOTINO\n");
	if (debug)
		printf("Truncating and freeing ino %ju, nlink %d, mode %o\n",
		    (uintmax_t)ino, DIP(ip, di_nlink), DIP(ip, di_mode));

	/* We are freeing an inode or directory. */
	if ((DIP(ip, di_mode) & IFMT) == IFDIR)
		ino_visit(ip, ino, ino_free_children, 0);
	DIP_SET(ip, di_nlink, 0);
	ino_visit(ip, ino, blk_free_visit, VISIT_EXT | VISIT_INDIR);
	/* Here we have to clear the inode and release any blocks it holds. */
	gen = DIP(ip, di_gen);
	if (fs->fs_magic == FS_UFS1_MAGIC)
		bzero(ip, sizeof(struct ufs1_dinode));
	else
		bzero(ip, sizeof(struct ufs2_dinode));
	DIP_SET(ip, di_gen, gen);
	ino_dirty(ino);
	ino_free(ino, mode);
	return;
}