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
typedef  union dinode {int dummy; } dinode ;
struct inoinfo {scalar_t__ i_dotdot; scalar_t__ i_parent; } ;
struct dirtemplate {scalar_t__ dotdot_ino; scalar_t__ dot_ino; } ;
struct TYPE_4__ {char* b_buf; } ;
struct bufarea {TYPE_1__ b_un; scalar_t__ b_errs; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_6__ {int ino_linkcnt; scalar_t__ ino_state; } ;
struct TYPE_5__ {size_t fs_fsize; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 size_t DIRBLKSIZ ; 
 scalar_t__ DSTATE ; 
 int IFDIR ; 
 int /*<<< orphan*/  INO_IS_DVALID (scalar_t__) ; 
 scalar_t__ UFS_ROOTINO ; 
 scalar_t__ allocino (scalar_t__,int) ; 
 int /*<<< orphan*/  cacheino (union dinode*,scalar_t__) ; 
 int /*<<< orphan*/ * di_db ; 
 int /*<<< orphan*/  di_nlink ; 
 struct dirtemplate dirhead ; 
 int /*<<< orphan*/  dirty (struct bufarea*) ; 
 struct dirtemplate emptydir ; 
 int /*<<< orphan*/  freeino (scalar_t__) ; 
 struct bufarea* getdirblk (int,size_t) ; 
 struct inoinfo* getinoinfo (scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 TYPE_3__* inoinfo (scalar_t__) ; 
 int /*<<< orphan*/  memmove (char*,struct dirtemplate*,int) ; 
 TYPE_2__ sblock ; 

ino_t
allocdir(ino_t parent, ino_t request, int mode)
{
	ino_t ino;
	char *cp;
	union dinode *dp;
	struct bufarea *bp;
	struct inoinfo *inp;
	struct dirtemplate *dirp;

	ino = allocino(request, IFDIR|mode);
	dirp = &dirhead;
	dirp->dot_ino = ino;
	dirp->dotdot_ino = parent;
	dp = ginode(ino);
	bp = getdirblk(DIP(dp, di_db[0]), sblock.fs_fsize);
	if (bp->b_errs) {
		freeino(ino);
		return (0);
	}
	memmove(bp->b_un.b_buf, dirp, sizeof(struct dirtemplate));
	for (cp = &bp->b_un.b_buf[DIRBLKSIZ];
	     cp < &bp->b_un.b_buf[sblock.fs_fsize];
	     cp += DIRBLKSIZ)
		memmove(cp, &emptydir, sizeof emptydir);
	dirty(bp);
	DIP_SET(dp, di_nlink, 2);
	inodirty(dp);
	if (ino == UFS_ROOTINO) {
		inoinfo(ino)->ino_linkcnt = DIP(dp, di_nlink);
		cacheino(dp, ino);
		return(ino);
	}
	if (!INO_IS_DVALID(parent)) {
		freeino(ino);
		return (0);
	}
	cacheino(dp, ino);
	inp = getinoinfo(ino);
	inp->i_parent = parent;
	inp->i_dotdot = parent;
	inoinfo(ino)->ino_state = inoinfo(parent)->ino_state;
	if (inoinfo(ino)->ino_state == DSTATE) {
		inoinfo(ino)->ino_linkcnt = DIP(dp, di_nlink);
		inoinfo(parent)->ino_linkcnt++;
	}
	dp = ginode(parent);
	DIP_SET(dp, di_nlink, DIP(dp, di_nlink) + 1);
	inodirty(dp);
	return (ino);
}