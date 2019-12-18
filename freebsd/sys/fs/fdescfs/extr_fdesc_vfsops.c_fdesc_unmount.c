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
struct mount {struct fdescmount* mnt_data; } ;
struct fdescmount {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMNT_UNMOUNTF ; 
 int FORCECLOSE ; 
 int MNT_FORCE ; 
 int /*<<< orphan*/  M_FDESCMNT ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fdesc_hashmtx ; 
 int /*<<< orphan*/  free (struct fdescmount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int vflush (struct mount*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
fdesc_unmount(struct mount *mp, int mntflags)
{
	struct fdescmount *fmp;
	int error, flags;

	flags = 0;
	fmp = mp->mnt_data;
	if (mntflags & MNT_FORCE) {
		/* The hash mutex protects the private mount flags. */
		mtx_lock(&fdesc_hashmtx);
		fmp->flags |= FMNT_UNMOUNTF;
		mtx_unlock(&fdesc_hashmtx);
		flags |= FORCECLOSE;
	}

	/*
	 * Clear out buffer cache.  I don't think we
	 * ever get anything cached at this level at the
	 * moment, but who knows...
	 *
	 * There is 1 extra root vnode reference corresponding
	 * to f_root.
	 */
	if ((error = vflush(mp, 1, flags, curthread)) != 0)
		return (error);

	/*
	 * Finally, throw away the fdescmount structure.
	 */
	mp->mnt_data = NULL;
	free(fmp, M_FDESCMNT);
	return (0);
}