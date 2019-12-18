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
struct vnode {scalar_t__ v_type; } ;
struct vattr {int va_blocksize; } ;
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct dirent {scalar_t__ d_type; scalar_t__ d_fileno; int /*<<< orphan*/  d_name; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int DEV_BSIZE ; 
 scalar_t__ DT_WHT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ VDIR ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,int /*<<< orphan*/ ) ; 
 int VOP_ISLOCKED (struct vnode*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int get_next_dirent (struct vnode*,struct dirent**,char*,int,scalar_t__*,char**,int*,int*,struct thread*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
dirent_exists(struct vnode *vp, const char *dirname, struct thread *td)
{
	char *dirbuf, *cpos;
	int error, eofflag, dirbuflen, len, found;
	off_t off;
	struct dirent *dp;
	struct vattr va;

	KASSERT(VOP_ISLOCKED(vp), ("vp %p is not locked", vp));
	KASSERT(vp->v_type == VDIR, ("vp %p is not a directory", vp));

	found = 0;

	error = VOP_GETATTR(vp, &va, td->td_ucred);
	if (error)
		return (found);

	dirbuflen = DEV_BSIZE;
	if (dirbuflen < va.va_blocksize)
		dirbuflen = va.va_blocksize;
	dirbuf = (char *)malloc(dirbuflen, M_TEMP, M_WAITOK);

	off = 0;
	len = 0;
	do {
		error = get_next_dirent(vp, &dp, dirbuf, dirbuflen, &off,
					&cpos, &len, &eofflag, td);
		if (error)
			goto out;

		if (dp->d_type != DT_WHT && dp->d_fileno != 0 &&
		    strcmp(dp->d_name, dirname) == 0) {
			found = 1;
			goto out;
		}
	} while (len > 0 || !eofflag);

out:
	free(dirbuf, M_TEMP);
	return (found);
}