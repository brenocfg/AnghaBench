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
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AT_BENEATH ; 
 int AT_SYMLINK_NOFOLLOW ; 
 int AUDITVNODE1 ; 
 int /*<<< orphan*/  AUDIT_ARG_MODE (int /*<<< orphan*/ ) ; 
 int BENEATH ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_ATRIGHTS (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,int /*<<< orphan*/ *,struct thread*) ; 
 int NOFOLLOW ; 
 int /*<<< orphan*/  cap_fchmod_rights ; 
 int namei (struct nameidata*) ; 
 int setfmode (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrele (int /*<<< orphan*/ ) ; 

int
kern_fchmodat(struct thread *td, int fd, const char *path,
    enum uio_seg pathseg, mode_t mode, int flag)
{
	struct nameidata nd;
	int error, follow;

	AUDIT_ARG_MODE(mode);
	follow = (flag & AT_SYMLINK_NOFOLLOW) != 0 ? NOFOLLOW : FOLLOW;
	follow |= (flag & AT_BENEATH) != 0 ? BENEATH : 0;
	NDINIT_ATRIGHTS(&nd, LOOKUP, follow | AUDITVNODE1, pathseg, path, fd,
	    &cap_fchmod_rights, td);
	if ((error = namei(&nd)) != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	error = setfmode(td, td->td_ucred, nd.ni_vp, mode);
	vrele(nd.ni_vp);
	return (error);
}