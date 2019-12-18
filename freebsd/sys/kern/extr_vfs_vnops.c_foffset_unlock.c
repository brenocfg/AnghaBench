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
struct mtx {int dummy; } ;
struct file {int f_vnread_flags; void* f_nextoff; void* f_offset; } ;
typedef  void* off_t ;

/* Variables and functions */
 int FOFFSET_LOCKED ; 
 int FOFFSET_LOCK_WAITING ; 
 int FOF_NEXTOFF ; 
 int FOF_NOLOCK ; 
 int FOF_NOUPDATE ; 
 int FOF_OFFSET ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 struct mtx* mtx_pool_find (int /*<<< orphan*/ ,struct file*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 
 int /*<<< orphan*/  mtxpool_sleep ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
foffset_unlock(struct file *fp, off_t val, int flags)
{
	struct mtx *mtxp;

	KASSERT((flags & FOF_OFFSET) == 0, ("FOF_OFFSET passed"));

#if OFF_MAX <= LONG_MAX
	if ((flags & FOF_NOLOCK) != 0) {
		if ((flags & FOF_NOUPDATE) == 0)
			fp->f_offset = val;
		if ((flags & FOF_NEXTOFF) != 0)
			fp->f_nextoff = val;
		return;
	}
#endif

	mtxp = mtx_pool_find(mtxpool_sleep, fp);
	mtx_lock(mtxp);
	if ((flags & FOF_NOUPDATE) == 0)
		fp->f_offset = val;
	if ((flags & FOF_NEXTOFF) != 0)
		fp->f_nextoff = val;
	if ((flags & FOF_NOLOCK) == 0) {
		KASSERT((fp->f_vnread_flags & FOFFSET_LOCKED) != 0,
		    ("Lost FOFFSET_LOCKED"));
		if (fp->f_vnread_flags & FOFFSET_LOCK_WAITING)
			wakeup(&fp->f_vnread_flags);
		fp->f_vnread_flags = 0;
	}
	mtx_unlock(mtxp);
}