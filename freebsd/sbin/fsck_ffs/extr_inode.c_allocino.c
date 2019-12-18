#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union dinode {int dummy; } dinode ;
struct TYPE_7__ {int /*<<< orphan*/  cs_ndir; int /*<<< orphan*/  cs_nifree; } ;
struct cg {TYPE_2__ cg_cs; } ;
struct TYPE_6__ {struct cg* b_cg; } ;
struct bufarea {TYPE_1__ b_un; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_9__ {scalar_t__ ino_state; int /*<<< orphan*/  ino_type; } ;
struct TYPE_8__ {scalar_t__ fs_ipg; int fs_fsize; } ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ DSTATE ; 
 scalar_t__ FSTATE ; 
#define  IFDIR 130 
#define  IFLNK 129 
 int IFMT ; 
#define  IFREG 128 
 int /*<<< orphan*/  IFTODT (int) ; 
 scalar_t__ UFS_ROOTINO ; 
 scalar_t__ USTATE ; 
 int allocblk (long) ; 
 int btodb (int) ; 
 int /*<<< orphan*/  cg_inosused (struct cg*) ; 
 int /*<<< orphan*/  cgdirty (struct bufarea*) ; 
 struct bufarea* cglookup (int) ; 
 int /*<<< orphan*/  check_cgmagic (int,struct bufarea*) ; 
 int /*<<< orphan*/  di_atime ; 
 int /*<<< orphan*/  di_atimensec ; 
 int /*<<< orphan*/  di_blocks ; 
 int /*<<< orphan*/  di_ctime ; 
 int /*<<< orphan*/  di_ctimensec ; 
 int /*<<< orphan*/ * di_db ; 
 int /*<<< orphan*/  di_flags ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_mtime ; 
 int /*<<< orphan*/  di_mtimensec ; 
 int /*<<< orphan*/  di_size ; 
 union dinode* ginode (scalar_t__) ; 
 int ino_to_cg (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  inodirty (union dinode*) ; 
 TYPE_4__* inoinfo (scalar_t__) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  n_files ; 
 TYPE_3__ sblock ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ ,scalar_t__) ; 
 int time (int /*<<< orphan*/ *) ; 

ino_t
allocino(ino_t request, int type)
{
	ino_t ino;
	union dinode *dp;
	struct bufarea *cgbp;
	struct cg *cgp;
	int cg;

	if (request == 0)
		request = UFS_ROOTINO;
	else if (inoinfo(request)->ino_state != USTATE)
		return (0);
	for (ino = request; ino < maxino; ino++)
		if (inoinfo(ino)->ino_state == USTATE)
			break;
	if (ino == maxino)
		return (0);
	cg = ino_to_cg(&sblock, ino);
	cgbp = cglookup(cg);
	cgp = cgbp->b_un.b_cg;
	if (!check_cgmagic(cg, cgbp))
		return (0);
	setbit(cg_inosused(cgp), ino % sblock.fs_ipg);
	cgp->cg_cs.cs_nifree--;
	switch (type & IFMT) {
	case IFDIR:
		inoinfo(ino)->ino_state = DSTATE;
		cgp->cg_cs.cs_ndir++;
		break;
	case IFREG:
	case IFLNK:
		inoinfo(ino)->ino_state = FSTATE;
		break;
	default:
		return (0);
	}
	cgdirty(cgbp);
	dp = ginode(ino);
	DIP_SET(dp, di_db[0], allocblk((long)1));
	if (DIP(dp, di_db[0]) == 0) {
		inoinfo(ino)->ino_state = USTATE;
		return (0);
	}
	DIP_SET(dp, di_mode, type);
	DIP_SET(dp, di_flags, 0);
	DIP_SET(dp, di_atime, time(NULL));
	DIP_SET(dp, di_ctime, DIP(dp, di_atime));
	DIP_SET(dp, di_mtime, DIP(dp, di_ctime));
	DIP_SET(dp, di_mtimensec, 0);
	DIP_SET(dp, di_ctimensec, 0);
	DIP_SET(dp, di_atimensec, 0);
	DIP_SET(dp, di_size, sblock.fs_fsize);
	DIP_SET(dp, di_blocks, btodb(sblock.fs_fsize));
	n_files++;
	inodirty(dp);
	inoinfo(ino)->ino_type = IFTODT(type);
	return (ino);
}