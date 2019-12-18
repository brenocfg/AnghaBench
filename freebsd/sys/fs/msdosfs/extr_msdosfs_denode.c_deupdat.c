#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct direntry {int dummy; } ;
struct denode {int de_flag; scalar_t__ de_refcnt; } ;
struct buf {int b_flags; } ;
typedef  int /*<<< orphan*/  dir ;
struct TYPE_4__ {int v_vflag; TYPE_1__* v_mount; } ;
struct TYPE_3__ {int mnt_flag; } ;

/* Variables and functions */
 int B_CLUSTEROK ; 
 int B_DELWRI ; 
 int /*<<< orphan*/  DETIMES (struct denode*,struct timespec*,struct timespec*,struct timespec*) ; 
 TYPE_2__* DETOV (struct denode*) ; 
 int DE_ACCESS ; 
 int DE_CREATE ; 
 int /*<<< orphan*/  DE_EXTERNALIZE (struct direntry*,struct denode*) ; 
 int DE_MODIFIED ; 
 int DE_UPDATE ; 
 int EINVAL ; 
 int MNT_NOCLUSTERW ; 
 int MNT_RDONLY ; 
 int VV_ROOT ; 
 int /*<<< orphan*/  bawrite (struct buf*) ; 
 scalar_t__ bcmp (struct direntry*,struct direntry*,int) ; 
 int /*<<< orphan*/  bdwrite (struct buf*) ; 
 int /*<<< orphan*/  brelse (struct buf*) ; 
 scalar_t__ buf_dirty_count_severe () ; 
 int bwrite (struct buf*) ; 
 int readde (struct denode*,struct buf**,struct direntry**) ; 
 int /*<<< orphan*/  vfs_timestamp (struct timespec*) ; 
 scalar_t__ vm_page_count_severe () ; 

int
deupdat(struct denode *dep, int waitfor)
{
	struct direntry dir;
	struct timespec ts;
	struct buf *bp;
	struct direntry *dirp;
	int error;

	if (DETOV(dep)->v_mount->mnt_flag & MNT_RDONLY) {
		dep->de_flag &= ~(DE_UPDATE | DE_CREATE | DE_ACCESS |
		    DE_MODIFIED);
		return (0);
	}
	vfs_timestamp(&ts);
	DETIMES(dep, &ts, &ts, &ts);
	if ((dep->de_flag & DE_MODIFIED) == 0 && waitfor == 0)
		return (0);
	dep->de_flag &= ~DE_MODIFIED;
	if (DETOV(dep)->v_vflag & VV_ROOT)
		return (EINVAL);
	if (dep->de_refcnt <= 0)
		return (0);
	error = readde(dep, &bp, &dirp);
	if (error)
		return (error);
	DE_EXTERNALIZE(&dir, dep);
	if (bcmp(dirp, &dir, sizeof(dir)) == 0) {
		if (waitfor == 0 || (bp->b_flags & B_DELWRI) == 0) {
			brelse(bp);
			return (0);
		}
	} else
		*dirp = dir;
	if ((DETOV(dep)->v_mount->mnt_flag & MNT_NOCLUSTERW) == 0)
		bp->b_flags |= B_CLUSTEROK;
	if (waitfor)
		error = bwrite(bp);
	else if (vm_page_count_severe() || buf_dirty_count_severe())
		bawrite(bp);
	else
		bdwrite(bp);
	return (error);
}