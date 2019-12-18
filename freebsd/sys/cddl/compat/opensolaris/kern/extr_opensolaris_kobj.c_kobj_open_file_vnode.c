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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct nameidata {void* ni_vp; } ;

/* Variables and functions */
 int FREAD ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,struct thread*) ; 
 int O_NOFOLLOW ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  VOP_UNLOCK (void*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  pwd_ensure_dirs () ; 
 int vn_open_cred (struct nameidata*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
kobj_open_file_vnode(const char *file)
{
	struct thread *td = curthread;
	struct nameidata nd;
	int error, flags;

	pwd_ensure_dirs();

	flags = FREAD | O_NOFOLLOW;
	NDINIT(&nd, LOOKUP, 0, UIO_SYSSPACE, file, td);
	error = vn_open_cred(&nd, &flags, 0, 0, curthread->td_ucred, NULL);
	if (error != 0)
		return (NULL);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	/* We just unlock so we hold a reference. */
	VOP_UNLOCK(nd.ni_vp, 0);
	return (nd.ni_vp);
}