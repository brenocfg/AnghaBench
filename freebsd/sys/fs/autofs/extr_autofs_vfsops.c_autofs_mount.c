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
struct mount {int mnt_flag; int /*<<< orphan*/  mnt_kern_flag; struct autofs_mount* mnt_data; int /*<<< orphan*/  mnt_optnew; } ;
struct autofs_mount {int am_last_fileno; int /*<<< orphan*/  am_root; int /*<<< orphan*/  am_lock; int /*<<< orphan*/  am_prefix; int /*<<< orphan*/  am_options; int /*<<< orphan*/  am_mountpoint; int /*<<< orphan*/  am_from; struct mount* am_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_XLOCK (struct autofs_mount*) ; 
 int /*<<< orphan*/  AUTOFS_XUNLOCK (struct autofs_mount*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MNTK_LOOKUP_SHARED ; 
 int /*<<< orphan*/  MNT_ILOCK (struct mount*) ; 
 int /*<<< orphan*/  MNT_IUNLOCK (struct mount*) ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VFSTOAUTOFS (struct mount*) ; 
 int /*<<< orphan*/  autofs_flush (int /*<<< orphan*/ ) ; 
 int autofs_node_new (int /*<<< orphan*/ *,struct autofs_mount*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  autofs_opts ; 
 int /*<<< orphan*/  free (struct autofs_mount*,int /*<<< orphan*/ ) ; 
 struct autofs_mount* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vfs_filteropt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_getnewfsid (struct mount*) ; 
 scalar_t__ vfs_getopt (int /*<<< orphan*/ ,char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfs_mountedfrom (struct mount*,char*) ; 

__attribute__((used)) static int
autofs_mount(struct mount *mp)
{
	struct autofs_mount *amp;
	char *from, *fspath, *options, *prefix;
	int error;

	if (vfs_filteropt(mp->mnt_optnew, autofs_opts))
		return (EINVAL);

	if (mp->mnt_flag & MNT_UPDATE) {
		autofs_flush(VFSTOAUTOFS(mp));
		return (0);
	}

	if (vfs_getopt(mp->mnt_optnew, "from", (void **)&from, NULL))
		return (EINVAL);

	if (vfs_getopt(mp->mnt_optnew, "fspath", (void **)&fspath, NULL))
		return (EINVAL);

	if (vfs_getopt(mp->mnt_optnew, "master_options", (void **)&options, NULL))
		return (EINVAL);

	if (vfs_getopt(mp->mnt_optnew, "master_prefix", (void **)&prefix, NULL))
		return (EINVAL);

	amp = malloc(sizeof(*amp), M_AUTOFS, M_WAITOK | M_ZERO);
	mp->mnt_data = amp;
	amp->am_mp = mp;
	strlcpy(amp->am_from, from, sizeof(amp->am_from));
	strlcpy(amp->am_mountpoint, fspath, sizeof(amp->am_mountpoint));
	strlcpy(amp->am_options, options, sizeof(amp->am_options));
	strlcpy(amp->am_prefix, prefix, sizeof(amp->am_prefix));
	sx_init(&amp->am_lock, "autofslk");
	amp->am_last_fileno = 1;

	vfs_getnewfsid(mp);

	MNT_ILOCK(mp);
	mp->mnt_kern_flag |= MNTK_LOOKUP_SHARED;
	MNT_IUNLOCK(mp);

	AUTOFS_XLOCK(amp);
	error = autofs_node_new(NULL, amp, ".", -1, &amp->am_root);
	if (error != 0) {
		AUTOFS_XUNLOCK(amp);
		free(amp, M_AUTOFS);
		return (error);
	}
	AUTOFS_XUNLOCK(amp);

	vfs_mountedfrom(mp, from);

	return (0);
}