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
struct udf_mnt {int im_flags; struct udf_mnt* s_table; int /*<<< orphan*/  im_dev; int /*<<< orphan*/  im_devvp; int /*<<< orphan*/  im_cp; scalar_t__ im_l2d; scalar_t__ im_d2l; } ;
struct mount {int /*<<< orphan*/  mnt_flag; int /*<<< orphan*/ * mnt_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* close ) (scalar_t__) ;} ;

/* Variables and functions */
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_LOCAL ; 
 int /*<<< orphan*/  M_UDFMOUNT ; 
 int UDFMNT_KICONV ; 
 struct udf_mnt* VFSTOUDFFS (struct mount*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  dev_rel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct udf_mnt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_vfs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 TYPE_1__* udf_iconv ; 
 int vflush (struct mount*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
udf_unmount(struct mount *mp, int mntflags)
{
	struct udf_mnt *udfmp;
	int error, flags = 0;

	udfmp = VFSTOUDFFS(mp);

	if (mntflags & MNT_FORCE)
		flags |= FORCECLOSE;

	if ((error = vflush(mp, 0, flags, curthread)))
		return (error);

	if (udfmp->im_flags & UDFMNT_KICONV && udf_iconv) {
		if (udfmp->im_d2l)
			udf_iconv->close(udfmp->im_d2l);
#if 0
		if (udfmp->im_l2d)
			udf_iconv->close(udfmp->im_l2d);
#endif
	}

	g_topology_lock();
	g_vfs_close(udfmp->im_cp);
	g_topology_unlock();
	vrele(udfmp->im_devvp);
	dev_rel(udfmp->im_dev);

	if (udfmp->s_table != NULL)
		free(udfmp->s_table, M_UDFMOUNT);

	free(udfmp, M_UDFMOUNT);

	mp->mnt_data = NULL;
	MNT_ILOCK(mp);
	mp->mnt_flag &= ~MNT_LOCAL;
	MNT_IUNLOCK(mp);

	return (0);
}